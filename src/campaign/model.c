#include "model.h"
#include "campaign_data.h"
#include <string.h>

typedef char pr_u16_check[sizeof(uint16_t)==2?1:-1];
typedef char pr_u32_check[sizeof(uint32_t)==4?1:-1];
typedef char pr_state_budget[sizeof(PrState)<=4096?1:-1];
typedef char pr_flag_budget[PR_FLAG_COUNT<=32?1:-1];

int pr_flag(const PrState *s,enum PrFlag flag)
{ return flag<PR_FLAG_COUNT && flag>=0 && (s->flags&((uint32_t)1<<flag))!=0; }
void pr_set_flag(PrState *s,enum PrFlag flag,int value)
{
    if(flag<0 || flag>=PR_FLAG_COUNT)return;
    if(value)s->flags|=(uint32_t)1<<flag;
    else s->flags&=~((uint32_t)1<<flag);
}
int pr_done(const PrState *s,unsigned quest)
{ return quest>=1 && quest<=PR_QUESTS && s->quest[quest-1].status==PR_DONE; }

static enum PrResult journal(PrHero *hero,uint16_t entry)
{
    unsigned i;
    if(!entry)return PR_OK;
    for(i=0;i<hero->journal_count;++i)if(hero->journal[i]==entry)return PR_OK;
    if(hero->journal_count==PR_JOURNAL)return PR_FULL;
    hero->journal[hero->journal_count++]=entry;
    return PR_OK;
}
void pr_finish(PrState *s,unsigned quest,unsigned witnesses)
{
    unsigned hero;
    if(quest<1 || quest>PR_QUESTS || pr_done(s,quest))return;
    s->quest[quest-1].status=PR_DONE;
    s->quest[quest-1].substep=pr_quest_steps[quest];
    for(hero=0;hero<PR_HEROES;++hero)if(witnesses&(1u<<hero))
        journal(&s->hero[hero],(uint16_t)(1024+hero*PR_QUESTS+quest));
}
enum PrResult pr_learn(PrState *s,unsigned hero,unsigned fact,enum PrConfidence confidence,uint16_t entry)
{
    PrHero *person;
    enum PrResult result;
    if(hero>=PR_HEROES || fact>=PR_FACTS || confidence<=PR_UNLEARNED || confidence>PR_KNOWN)return PR_INVALID;
    person=&s->hero[hero];
    result=journal(person,entry);
    if(result!=PR_OK)return result;
    person->knowledge[fact/32]|=(uint32_t)1<<(fact%32);
    if(confidence>person->confidence[fact])person->confidence[fact]=(uint8_t)confidence;
    return PR_OK;
}
int pr_knows(const PrState *s,unsigned hero,unsigned fact)
{ return hero<PR_HEROES && fact<PR_FACTS && (s->hero[hero].knowledge[fact/32]&((uint32_t)1<<(fact%32)))!=0; }

int pr_item_owner(const PrState *s,unsigned item)
{
    unsigned depth;
    if(item<1 || item>PR_ITEMS)return -1;
    for(depth=0;depth<PR_ITEMS;++depth) {
        unsigned pos=s->world.item_position[item];
        if(pos==PR_INVENTORY_M || pos==PR_WORN_M)return PR_M;
        if(pos==PR_INVENTORY_K || pos==PR_WORN_K)return PR_K;
        if(pos<=PR_CONTAINER_BASE || pos>PR_CONTAINER_BASE+PR_ITEMS)return -1;
        item=pos-PR_CONTAINER_BASE;
    }
    return -1;
}
int pr_has_item(const PrState *s,unsigned hero,unsigned item)
{ return hero<PR_HEROES && pr_item_owner(s,item)==(int)hero; }
enum PrResult pr_place_item(PrState *s,unsigned item,unsigned position)
{
    unsigned parent=position,depth=0;
    if(item<1 || item>PR_ITEMS || position>PR_CONTAINER_BASE+PR_ITEMS)return PR_INVALID;
    if(position>PR_SCENES && position<PR_INVENTORY_M)return PR_INVALID;
    if(position>PR_FLOREK && position<=PR_CONTAINER_BASE)return PR_INVALID;
    while(parent>PR_CONTAINER_BASE) {
        parent-=PR_CONTAINER_BASE;
        if(parent>PR_ITEMS || parent==item || ++depth>=PR_ITEMS)return PR_INVALID;
        parent=s->world.item_position[parent];
    }
    s->world.item_position[item]=(uint16_t)position;
    return PR_OK;
}

void pr_new_game(PrGame *g)
{
    static const uint8_t items[]={4,5,6,7,8,9,10,11,12,13,14,16,17,18,24,25,31,32,41};
    static const uint8_t places[]={7,7,3,3,3,27,25,25,13,13,13,15,15,15,33,33,15,15,7};
    unsigned i;
    memset(g,0,sizeof(*g));
    g->current.schema_version=g->current.content_version=1;
    g->current.phase=PR_A;g->current.active=PR_M;
    g->current.hero[PR_M].location=g->current.hero[PR_M].last_safe_location=1;
    g->current.hero[PR_K].location=g->current.hero[PR_K].last_safe_location=3;
    for(i=0;i<sizeof(items);++i)g->current.world.item_position[items[i]]=places[i];
}

enum PrResult pr_queue_message(PrState *s,unsigned item,unsigned sender,unsigned recipient,unsigned route,unsigned phase)
{
    unsigned i;
    PrMessage *message=0;
    if(item<1 || item>PR_ITEMS || sender>=PR_HEROES || recipient>=PR_HEROES || sender==recipient ||
       route>PR_ROUTE_IZYDOR || phase>PR_F || pr_item_owner(s,item)!=(int)sender)return PR_INVALID;
    for(i=0;i<PR_MESSAGES;++i) {
        if(s->messages[i].state!=PR_MSG_UNUSED && s->messages[i].item==item)return PR_DENIED;
        if(s->messages[i].state==PR_MSG_UNUSED && !message)message=&s->messages[i];
    }
    if(!message)return PR_FULL;
    message->item=item;message->sender=sender;message->recipient=recipient;
    message->route=route;message->phase=phase;message->state=PR_MSG_WAITING;
    s->world.item_position[item]=route==PR_ROUTE_ROOM?13:PR_COURIER;
    return PR_OK;
}
void pr_deliver_messages(PrState *s)
{
    unsigned i;
    for(i=0;i<PR_MESSAGES;++i) {
        PrMessage *m=&s->messages[i];
        if(m->state!=PR_MSG_WAITING || s->phase<m->phase)continue;
        if(m->route==PR_ROUTE_NEIGHBOUR_IZYDOR_FLOREK) {
            /* Never deliver back into a crisis that has already begun. */
            if(s->phase==PR_D && s->crisis_substep==0) {
                s->world.item_position[m->item]=PR_FLOREK;m->state=PR_MSG_DELIVERED;
            }
        } else if(m->route==PR_ROUTE_ROOM) {
            if(s->phase==PR_D && s->crisis_substep==0)m->state=PR_MSG_DELIVERED;
        } else if(s->phase==PR_F && s->active==m->recipient) {
            s->world.item_position[m->item]=PR_INVENTORY_M+m->recipient;m->state=PR_MSG_DELIVERED;
        }
    }
}
enum PrResult pr_read_message(PrState *s,unsigned item,unsigned hero)
{
    unsigned i;
    if(hero>=PR_HEROES || s->active!=hero)return PR_DENIED;
    for(i=0;i<PR_MESSAGES;++i) {
        PrMessage *m=&s->messages[i];
        if(m->item==item && m->recipient==hero && m->state>=PR_MSG_DELIVERED) {
            if(m->state==PR_MSG_READ)return PR_OK;
            if(m->route==PR_ROUTE_ROOM) {
                if(s->hero[hero].location!=13)return PR_DENIED;
                s->world.item_position[item]=PR_INVENTORY_M+hero;
            }
            if(!pr_has_item(s,hero,item))return PR_DENIED;
            m->state=PR_MSG_READ;
            /* Reading makes its contents known, not automatically believed. */
            if(item==43)pr_learn(s,hero,PR_FACT_MESSAGE_WAITING,PR_HEARD,2043);
            if(item==45)pr_learn(s,hero,PR_FACT_FUTURE_LETTER,PR_KNOWN,2045);
            return PR_OK;
        }
    }
    return PR_DENIED;
}

enum PrResult pr_switch_hero(PrState *s)
{
    if(s->locks || s->player_dead || s->ending)return PR_DENIED;
    s->active=s->active==PR_M?PR_K:PR_M;
    pr_deliver_messages(s);
    return PR_OK;
}
enum PrResult pr_advance_phase(PrState *s,int confirm)
{
    unsigned phase=s->phase;
    if(s->locks || s->player_dead || s->ending)return PR_DENIED;
    if(phase==PR_A && pr_done(s,5) && pr_done(s,8)) {
        s->phase=PR_B;s->hero[PR_M].location=9;s->hero[PR_K].location=30;
    } else if(phase==PR_B && pr_done(s,13) && pr_done(s,15)) {
        s->phase=PR_C;s->hero[PR_M].location=11;s->hero[PR_K].location=33;
    } else if(phase==PR_C && pr_done(s,19) && pr_done(s,24)) {
        if(!confirm)return PR_CONFIRMATION;
        s->phase=PR_D;s->hero[PR_M].location=13;s->hero[PR_K].location=8;
    } else if(phase==PR_E && pr_done(s,33))s->phase=PR_F;
    else return PR_WAITING;
    s->hero[PR_M].last_safe_location=s->hero[PR_M].location;
    s->hero[PR_K].last_safe_location=s->hero[PR_K].location;
    s->phase_confirmed[0]=s->phase_confirmed[1]=0;
    pr_deliver_messages(s);
    return PR_OK;
}

enum PrEnding pr_ending(const PrState *s)
{
    int pair;
    if(s->krystyna_alive==PR_UNKNOWN || s->book_marriage==PR_UNKNOWN)return PR_NO_ENDING;
    if(!pr_flag(s,PR_HAUNTING_RESOLVED))return PR_E04;
    if(s->krystyna_alive==PR_NO)return PR_E01;
    pair=s->book_marriage==PR_NO && s->m_future==PR_RECONNECT && s->k_future==PR_RECONNECT;
    return pair?PR_E02:PR_E03;
}
int pr_can_finish(const PrState *s)
{
    return s->phase==PR_F && pr_done(s,35) && pr_done(s,39) && s->m_future!=PR_UNSET &&
        s->k_future!=PR_UNSET && s->coast_legacy && s->klara_seen && pr_ending(s)!=PR_NO_ENDING;
}
void pr_snapshot(PrGame *g)
{ g->safe_snapshot=g->current;g->safe_snapshot.locks&=~PR_MODAL;g->has_safe_snapshot=1; }
enum PrResult pr_undo(PrGame *g)
{
    if(!g->has_safe_snapshot)return PR_DENIED;
    g->current=g->safe_snapshot;
    return PR_OK;
}
