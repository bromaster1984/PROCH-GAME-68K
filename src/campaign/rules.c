#include "rules_internal.h"

int pr_action_done(const PrState *s,unsigned q,unsigned bit)
{ return q>=1 && q<=PR_QUESTS && bit<32 && (s->quest[q-1].actions&PR_BIT(bit))!=0; }
void pr_mark_action(PrState *s,unsigned q,unsigned bit)
{
    s->quest[q-1].actions|=PR_BIT(bit);
    if(!pr_done(s,q))s->quest[q-1].status=PR_ACTIVE;
}
void pr_story_move(PrState *s,unsigned scene)
{ s->hero[s->active].location=s->hero[s->active].last_safe_location=(uint8_t)scene; }
PrFeedback pr_reply(unsigned result,unsigned text,unsigned presentation,unsigned target)
{
    PrFeedback f;
    f.result=result;f.text=text;f.presentation=presentation;f.target=target;
    return f;
}
static unsigned open_index(unsigned target)
{
    if(target>=PR_ITEM(1) && target<=PR_ITEM(PR_ITEMS))return 360+target-PR_ITEM(0);
    return target<352?target:512;
}
int pr_container_is_open(const PrState *s,unsigned target)
{
    unsigned i=open_index(target);
    return i<512 && (s->world.container_open[i/8]&(1u<<(i%8)))!=0;
}
static void set_open(PrState *s,unsigned target,int open)
{
    unsigned i=open_index(target);
    if(i>=512)return;
    if(open)s->world.container_open[i/8]|=1u<<(i%8);
    else s->world.container_open[i/8]&=~(1u<<(i%8));
}
int pr_target_here(const PrState *s,unsigned target)
{
    unsigned actor=s->active,scene=s->hero[actor].location,item;
    if(target>=PR_ITEM(1) && target<=PR_ITEM(PR_ITEMS)) {
        unsigned pos;
        item=target-PR_ITEM(0);pos=s->world.item_position[item];
        return pr_has_item(s,actor,item) || pos==scene ||
            (pos>PR_CONTAINER_BASE && pos<=PR_CONTAINER_BASE+PR_ITEMS &&
             pr_target_here(s,PR_ITEM(pos-PR_CONTAINER_BASE)) &&
             pr_container_is_open(s,PR_ITEM(pos-PR_CONTAINER_BASE)));
    }
    if(target<352)return target/8==scene && target%8<3;
    switch(target) {
    case PR_VALVE:case PR_COMPRESSOR_BODY:
        return scene==7 && pr_action_done(s,4,1);
    case PR_FACTORY_GATE:case PR_TAVERN_APPROACH:return scene==9;
    case PR_OPENED_ENVELOPE:return scene==26 && pr_action_done(s,8,3);
    case PR_DEPARTURE:return scene==3 || scene==25;
    case PR_LETTER_DESK:return scene==25;
    default:return 0;
    }
}
unsigned pr_topics(const PrState *s,unsigned target,PrTopic *out,unsigned capacity)
{
    if(s->active>=PR_HEROES || !pr_target_here(s,target) || s->player_dead || s->ending)return 0;
    return s->phase==PR_A?pr_topics_a(s,target,out,capacity):0;
}
static int valid_choice(const PrState *s,PrAction a)
{
    PrTopic topics[8];
    unsigned i,n=pr_topics(s,a.source,topics,8);
    for(i=0;i<n && i<8;++i)if(topics[i].id==a.target)return 1;
    return 0;
}
static int is_container(unsigned target)
{
    return target==PR_HOTSPOT(3,1) || target==PR_HOTSPOT(7,3) ||
        target==PR_HOTSPOT(25,1) || target==PR_ITEM(8) || target==PR_HOTSPOT(3,3);
}
PrFeedback pr_act(PrGame *g,PrAction a)
{
    PrState *s=&g->current;
    PrFeedback f;
    if(s->active>=PR_HEROES || s->player_dead || s->ending || (s->locks&~PR_MODAL))
        return pr_reply(PR_DENIED,PR_TEXT_BLOCKED,PR_LOG,0);
    if(a.verb==PR_SWITCH)
        return pr_reply(pr_switch_hero(s),s->locks?PR_TEXT_CLOSE_FIRST:PR_TEXT_SWITCHED,PR_LOG,0);
    if(a.verb==PR_GO && (s->locks&PR_MODAL))
        return pr_reply(PR_DENIED,PR_TEXT_CLOSE_FIRST,PR_LOG,0);
    if(a.verb==PR_HIT)return pr_reply(PR_DENIED,PR_TEXT_VIOLENCE,PR_LOG,0);
    if(a.verb==PR_EAT)return pr_reply(PR_DENIED,PR_TEXT_INEDIBLE,PR_LOG,0);
    if(a.verb>PR_SWITCH)return pr_reply(PR_INVALID,PR_TEXT_NO_EFFECT,PR_LOG,0);
    if(a.verb==PR_USE && !pr_has_item(s,s->active,a.source))
        return pr_reply(PR_DENIED,PR_TEXT_NOT_MINE,PR_LOG,0);
    if(a.verb==PR_CHOOSE) {
        if(!valid_choice(s,a))return pr_reply(PR_DENIED,PR_TEXT_NO_KNOWLEDGE,PR_LOG,0);
    } else if(a.verb!=PR_GO && !pr_target_here(s,a.target))
        return pr_reply(PR_DENIED,PR_TEXT_TOO_FAR,PR_LOG,0);
    if(a.verb==PR_TALK) {
        if(pr_topics(s,a.target,0,0))return pr_reply(PR_OK,PR_TEXT_CHOOSE_TOPIC,PR_DIALOG,a.target);
        return pr_reply(PR_DENIED,PR_TEXT_NO_KNOWLEDGE,PR_LOG,0);
    }
    if(a.verb==PR_CLOSE && is_container(a.target)) {
        set_open(s,a.target,0);
        return pr_reply(PR_OK,PR_TEXT_CLOSED,PR_LOG,0);
    }
    f=s->phase==PR_A?pr_rules_a(s,a):pr_reply(PR_DENIED,PR_TEXT_NO_EFFECT,PR_LOG,0);
    if(f.result==PR_OK) {
        if(a.verb==PR_OPEN && is_container(a.target)) {
            set_open(s,a.target,1);
            f.presentation=PR_CONTAINER;f.target=a.target;
        }
        if(s->phase==PR_A)pr_refresh_a(s);
        pr_advance_phase(s,0);
    }
    return f;
}
