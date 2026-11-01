#include "rules_internal.h"

#define H(s,n) PR_HOTSPOT(s,n)
#define C(q,n) PR_CHOICE(q,n)
#define HAS(q,n) pr_action_done(s,q,n)
#define MARK(q,n) pr_mark_action(s,q,n)
#define SAY(t) pr_reply(PR_OK,PR_TEXT_##t,PR_LOG,0)
#define DENY(t) pr_reply(PR_DENIED,PR_TEXT_##t,PR_LOG,0)

/* Micro-actions persist independently from the editorial step number. */
static unsigned prefix(const PrState *s,unsigned q,const uint32_t *m,unsigned count)
{
    unsigned i;
    for(i=0;i<count;++i)if((s->quest[q-1].actions&m[i])!=m[i])break;
    return i;
}
void pr_refresh_a(PrState *s)
{
    static const uint32_t q1[]={1,3,7,15},q2[]={1,3,7},q3[]={1,3,7,15};
    static const uint32_t q4[]={1,7,15,63,511,4095};
    static const uint32_t q5[]={1,3,31},q6[]={1,7,31,63};
    static const uint32_t q7[]={1,3,7,15,31},q8[]={1,7,31,63,255,511};
    const uint32_t *steps[]={q1,q2,q3,q4,q5,q6,q7,q8};
    unsigned q;
    /* A pickup may precede the first conversation. Never clear its evidence. */
    if(pr_has_item(s,PR_M,4) && pr_has_item(s,PR_M,5))MARK(4,4);
    if(pr_has_item(s,PR_K,10) && pr_has_item(s,PR_K,11))MARK(8,0);
    for(q=1;q<=8;++q)if(!pr_done(s,q)) {
        unsigned count=pr_quest_steps[q];
        s->quest[q-1].substep=(uint8_t)prefix(s,q,steps[q-1],count);
        if(s->quest[q-1].substep==count)pr_finish(s,q,q<=5?1:2);
    }
}

unsigned pr_topics_a(const PrState *s,unsigned target,PrTopic *out,unsigned capacity)
{
    unsigned n=0,actor=s->active;
#define ADD(q,i,label) do { if(out && n<capacity) {out[n].id=C(q,i);out[n].text=PR_TEXT_##label;} ++n; } while(0)
    if(actor==PR_M) {
        if(target==H(1,1)) {
            ADD(1,1,Q01_ASK);
            if(HAS(1,0) && HAS(1,1))ADD(1,2,Q01_ACCEPT);
        }
        if(target==H(2,1) && HAS(1,2))ADD(1,3,Q01_MARIAN);
        if(target==H(4,1) && pr_done(s,1) && HAS(2,0)) {
            ADD(2,1,Q02_ASK);
            if(HAS(2,1))ADD(2,2,Q02_ADDRESS);
        }
        if(target==H(6,1) && HAS(3,1))ADD(3,1,Q03_SEAT);
        if(target==H(6,2) && HAS(3,2))ADD(3,2,Q03_STOP);
        if(target==H(7,1) && pr_done(s,3)) {
            ADD(4,1,Q04_PERMISSION);
            if(HAS(4,0) && HAS(4,1) && HAS(4,2))ADD(4,2,Q04_OFF);
            if(HAS(4,8))ADD(4,3,Q04_TEST);
        }
        if(target==H(8,1) && HAS(5,0))ADD(5,1,Q05_DESTINATION);
    } else {
        if(target==PR_DEPARTURE && s->hero[PR_K].location==3)ADD(6,1,Q06_LEAVE);
        if(target==H(26,1) && pr_done(s,6)) {
            ADD(7,1,Q07_PARK);
            if(HAS(8,5))ADD(8,2,Q08_ASK);
        }
        if(target==H(27,1) && pr_done(s,6))ADD(7,2,Q07_WATER);
        if(target==H(29,1) && HAS(7,2))ADD(7,3,Q07_LIFT);
        if(target==PR_LETTER_DESK && pr_done(s,7) && HAS(8,1))ADD(8,1,Q08_RECIPIENT);
        if(target==PR_DEPARTURE && s->hero[PR_K].location==25 && HAS(8,7))ADD(8,3,Q08_SOPOT);
    }
#undef ADD
    return n;
}

static PrFeedback choose(PrState *s,PrAction a)
{
    switch(a.target) {
    case C(1,1):
        MARK(1,0);pr_learn(s,PR_M,PR_FACT_TASK,PR_KNOWN,PR_FACT_TASK);return SAY(Q01_REPLY);
    case C(1,2):
        if(HAS(1,2))return SAY(ALREADY);
        MARK(1,2);pr_place_item(s,1,PR_INVENTORY_M);pr_place_item(s,2,PR_INVENTORY_M);
        return SAY(Q01_DOCUMENTS);
    case C(1,3):
        if(HAS(1,3))return SAY(Q01_MARIAN_REPLY);
        MARK(1,3);pr_place_item(s,3,PR_INVENTORY_M);
        pr_learn(s,PR_M,PR_FACT_BROOCH,PR_KNOWN,PR_FACT_BROOCH);return SAY(Q01_MARIAN_REPLY);
    case C(2,1):MARK(2,1);return SAY(Q02_REPLY);
    case C(2,2):MARK(2,2);pr_set_flag(s,PR_ADDRESS_LEFT,1);return SAY(Q02_SAVED);
    case C(3,1):MARK(3,2);pr_set_flag(s,PR_KRYSTYNA_SAW_KINDNESS,1);return SAY(Q03_SEAT_REPLY);
    case C(3,2):MARK(3,3);return SAY(Q03_STOP_REPLY);
    case C(4,1):MARK(4,0);return SAY(Q04_PERMISSION_REPLY);
    case C(4,2):
        if(HAS(4,9))return SAY(ALREADY);
        MARK(4,3);return SAY(Q04_SAFE);
    case C(4,3):
        if(HAS(4,9))return SAY(Q04_WORKS);
        MARK(4,9);return SAY(Q04_WORKS);
    case C(5,1):MARK(5,1);pr_story_move(s,9);return SAY(Q05_REPLY);
    case C(6,1):
        if(!HAS(6,0) || s->world.item_position[6]!=PR_CONTAINER_BASE+8 ||
           s->world.item_position[7]!=PR_CONTAINER_BASE+8)return DENY(Q06_PACK_FIRST);
        pr_place_item(s,8,PR_INVENTORY_K);MARK(6,5);pr_story_move(s,25);return SAY(Q06_ARRIVED);
    case C(7,1):MARK(7,0);return SAY(Q07_PARK_REPLY);
    case C(7,2):
        if(!HAS(7,1)) {pr_place_item(s,9,PR_INVENTORY_K);MARK(7,1);}
        pr_learn(s,PR_K,PR_FACT_SERVANT_LUIZA,PR_KNOWN,PR_FACT_SERVANT_LUIZA);
        return SAY(Q07_WATER_REPLY);
    case C(7,3):
        MARK(7,3);pr_learn(s,PR_K,PR_FACT_SEROCZYN_DEPENDENCE,PR_KNOWN,PR_FACT_SEROCZYN_DEPENDENCE);
        return SAY(Q07_LIFT_REPLY);
    case C(8,1):MARK(8,2);return SAY(Q08_WRITTEN);
    case C(8,2):
        MARK(8,6);MARK(8,7);pr_set_flag(s,PR_INTERCEPTED_LETTER,1);
        pr_learn(s,PR_K,PR_FACT_MAIL_CONTROL,PR_KNOWN,PR_FACT_MAIL_CONTROL);
        return SAY(Q08_IRENA_REPLY);
    case C(8,3):MARK(8,8);return SAY(Q08_READY);
    default:return DENY(NO_EFFECT);
    }
}

static PrFeedback look(PrState *s,unsigned target)
{
    switch(target) {
    case H(1,2):case PR_ITEM(1):
        MARK(1,1);return pr_reply(PR_OK,PR_TEXT_Q01_CONTRACT,PR_DOCUMENT,target);
    case H(3,2):case PR_ITEM(6):
        MARK(6,0);pr_learn(s,PR_K,PR_FACT_MOTHER_PHOTO,PR_KNOWN,PR_FACT_MOTHER_PHOTO);
        return SAY(Q06_PHOTO);
    case PR_ITEM(7):return SAY(Q06_DOCUMENT);
    case H(5,2):
        MARK(3,0);pr_learn(s,PR_M,PR_FACT_TRAIN_ROUTE,PR_KNOWN,PR_FACT_TRAIN_ROUTE);
        return SAY(Q03_ROUTE);
    case H(7,2):MARK(4,1);return pr_reply(PR_OK,PR_TEXT_Q04_COMPRESSOR,PR_DOCUMENT,target);
    case PR_VALVE:
        MARK(4,2);pr_learn(s,PR_M,PR_FACT_TRAIN_VALVE,PR_KNOWN,PR_FACT_TRAIN_VALVE);
        return SAY(Q04_VALVE);
    case PR_ITEM(41):return s->world.item_state[41]>=2?SAY(Q04_CLEAN):SAY(Q04_DIRTY);
    case H(9,3):MARK(5,2);return SAY(Q05_BRIDGE);
    case PR_FACTORY_GATE:MARK(5,3);return SAY(Q05_GATE);
    case PR_OPENED_ENVELOPE:
        if(!HAS(8,4))return DENY(Q08_WAIT);
        MARK(8,5);return SAY(Q08_OPENED);
    case H(26,2):
        if(HAS(8,4)) {MARK(8,5);return SAY(Q08_OPENED);}
        return SAY(Q08_POST_TABLE);
    default:return SAY(OBSERVED);
    }
}

static PrFeedback take(PrState *s,unsigned item)
{
    unsigned actor=s->active,scene=s->hero[actor].location;
    if(item<1 || item>PR_ITEMS)return DENY(NO_EFFECT);
    if(pr_has_item(s,actor,item))return SAY(ALREADY);
    if(s->world.item_position[item]!=scene)return DENY(NOT_MINE);
    if(item==4 || item==5) {
        if(actor!=PR_M || !HAS(4,0) || !HAS(4,3))return DENY(Q04_PERMISSION_REPLY);
        if(HAS(4,10))return SAY(ALREADY);
        if(!pr_container_is_open(s,H(7,3)))return DENY(OPEN_FIRST);
    } else if(item==6 || item==7) {
        if(actor!=PR_K)return DENY(NOT_MINE);
        if(!pr_container_is_open(s,H(3,1)))return DENY(OPEN_FIRST);
        MARK(6,item==6?1:2);
    } else if(item==8) {
        if(actor!=PR_K)return DENY(NOT_MINE);
    } else if(item==10 || item==11) {
        if(actor!=PR_K)return DENY(NOT_MINE);
        if(!pr_container_is_open(s,H(25,1)))return DENY(OPEN_FIRST);
    } else return DENY(NOT_MINE);
    pr_place_item(s,item,PR_INVENTORY_M+actor);return SAY(TAKEN);
}

static PrFeedback use(PrState *s,unsigned item,unsigned target)
{
    if(item==1 && target==H(4,1) && pr_done(s,1)) {MARK(2,0);return SAY(Q02_SHOWN);}
    if(item==2 && target==H(5,3)) {
        if(!pr_done(s,1) || !HAS(3,0))return DENY(Q03_ROUTE_FIRST);
        MARK(3,1);pr_story_move(s,6);return SAY(Q03_BOARDED);
    }
    if(item==1 && target==H(8,1) && pr_done(s,4)) {MARK(5,0);return SAY(Q05_SHOWN);}
    if((item==6 || item==7) && (target==PR_ITEM(8) || target==H(3,3))) {
        pr_place_item(s,item,PR_CONTAINER_BASE+8);MARK(6,item==6?3:4);return SAY(Q06_PACKED);
    }
    if(item==9 && target==H(28,2)) {
        if(!HAS(7,0))return DENY(Q07_PARK_FIRST);
        MARK(7,2);pr_place_item(s,9,27);return SAY(Q07_GARDENER);
    }
    if((item==10 && target==PR_ITEM(11)) || (item==11 && target==PR_ITEM(10))) {
        if(!pr_done(s,7))return DENY(Q08_TRY_ESCAPE);
        if(s->hero[PR_K].location!=25)return DENY(Q08_WRITE_ROOM);
        MARK(8,1);return pr_reply(PR_OK,PR_TEXT_Q08_ADDRESS_PROMPT,PR_DIALOG,PR_LETTER_DESK);
    }
    if(item==10 && target==H(26,2)) {
        if(!HAS(8,2))return DENY(Q08_ADDRESS_FIRST);
        if(HAS(8,3))return SAY(ALREADY);
        MARK(8,3);return SAY(Q08_POSTED);
    }
    if(item==4 && target==PR_VALVE) {
        if(!HAS(4,0) || !HAS(4,3))return DENY(Q04_STOP_HAND);
        if(HAS(4,9))return SAY(ALREADY);
        if(!HAS(4,5)) {
            if(!HAS(4,2))return DENY(Q04_EXAMINE_FIRST);
            pr_place_item(s,41,PR_INVENTORY_M);s->world.item_state[41]=1;MARK(4,5);
            return SAY(Q04_REMOVED);
        }
        if(HAS(4,7)) {MARK(4,8);return SAY(Q04_CLOSED);}
        return DENY(Q04_INSERT_FIRST);
    }
    if(item==5 && target==PR_ITEM(41)) {
        if(!pr_has_item(s,PR_M,41) || !HAS(4,5))return DENY(Q04_REMOVE_FIRST);
        s->world.item_state[41]=2;MARK(4,6);return SAY(Q04_CLEAN);
    }
    if(item==41 && (target==PR_COMPRESSOR_BODY || target==H(7,2))) {
        if(!HAS(4,6))return DENY(Q04_CLEAN_FIRST);
        pr_place_item(s,41,7);s->world.item_state[41]=3;MARK(4,7);return SAY(Q04_INSERTED);
    }
    if((item==4 || item==5) && target==H(7,3)) {
        if(!HAS(4,9))return DENY(Q04_TEST_FIRST);
        pr_place_item(s,item,7);
        if(s->world.item_position[4]==7 && s->world.item_position[5]==7)MARK(4,10);
        return SAY(Q04_RETURNED);
    }
    return DENY(NO_EFFECT);
}

static PrFeedback go(PrState *s,unsigned scene)
{
    unsigned actor=s->active,from=s->hero[actor].location;
    if(actor==PR_M) {
        if(scene==PR_TAVERN_APPROACH && from==9) {
            if(!HAS(5,2) || !HAS(5,3))return DENY(Q05_LOOK_FIRST);
            MARK(5,4);return SAY(Q05_ARRIVED);
        }
        if(from==6 && scene==8 && pr_done(s,4)) {pr_story_move(s,8);return SAY(Q05_STATION);}
        if(scene==6 && from==7) {
            if(HAS(4,9) && !HAS(4,10))return DENY(Q04_RETURN_FIRST);
            if(HAS(4,10)) {MARK(4,11);pr_set_flag(s,PR_TRAIN_REPAIRED,1);}
        }
        if((from==2 && scene==4 && !pr_done(s,1)) || (scene==7 && !pr_done(s,3)) ||
           (from==5 && scene==6) || (from==6 && scene==5) ||
           (from==8 && scene==9) || (from==9 && scene!=9))return DENY(BLOCKED);
    } else {
        if(from==26 && scene==28 && !HAS(7,0))return DENY(Q07_PARK_FIRST);
        if(from==28 && scene==29 && !HAS(7,2))return DENY(Q07_GATE_FIRST);
        /* K cannot leave Warsaw by following M's route. */
        if(from==2 && scene==4)return DENY(Q06_DEPARTURE_ONLY);
    }
    if(pr_move_local(s,scene)!=PR_OK)return DENY(BLOCKED);
    if(actor==PR_K) {
        if(from==29 && scene==28 && HAS(7,3)) {MARK(7,4);return SAY(Q07_RETURNED);}
        if(scene==25 && HAS(8,3))MARK(8,4);
    }
    return SAY(MOVED);
}

PrFeedback pr_rules_a(PrState *s,PrAction a)
{
    if(a.verb==PR_CHOOSE)return choose(s,a);
    if(a.verb==PR_LOOK)return look(s,a.target);
    if(a.verb==PR_TAKE && a.target>PR_ITEM(0) && a.target<=PR_ITEM(PR_ITEMS))return take(s,a.target-PR_ITEM(0));
    if(a.verb==PR_USE)return use(s,a.source,a.target);
    if(a.verb==PR_GO)return go(s,a.target);
    if(a.verb==PR_OPEN) {
        if(a.target==H(3,1) || a.target==H(3,3) || a.target==PR_ITEM(8) || a.target==H(25,1))return SAY(CONTENTS);
        if(a.target==H(7,3))return HAS(4,0) && HAS(4,3)?SAY(CONTENTS):DENY(Q04_PERMISSION_REPLY);
    }
    return DENY(NO_EFFECT);
}
