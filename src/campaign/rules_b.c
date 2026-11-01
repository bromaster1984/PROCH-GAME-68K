#include "rules_internal.h"

#define H(s,n) PR_HOTSPOT(s,n)
#define C(q,n) PR_CHOICE(q,n)
#define HAS(q,n) pr_action_done(s,q,n)
#define MARK(q,n) pr_mark_action(s,q,n)
#define SAY(t) pr_reply(PR_OK,PR_TEXT_##t,PR_LOG,0)
#define DENY(t) pr_reply(PR_DENIED,PR_TEXT_##t,PR_LOG,0)

void pr_refresh_b(PrState *s)
{
    static const uint32_t q9[]={1,3,15,63,127},q10[]={1,3,7,15};
    static const uint32_t q11[]={1,3,7,15,31},q12[]={1,7,63,127,1023};
    static const uint32_t q13[]={1,3,7,31},q14[]={1,3,7,15},q15[]={3,7,15,31};
    const uint32_t *masks[]={q9,q10,q11,q12,q13,q14,q15};
    unsigned q,i;
    if(pr_has_item(s,PR_M,12))MARK(9,1);
    if(pr_has_item(s,PR_M,13))MARK(9,4);
    if(pr_has_item(s,PR_M,16) && pr_has_item(s,PR_M,17) && pr_has_item(s,PR_M,18))MARK(12,0);
    if(pr_has_item(s,PR_M,19))MARK(12,9);
    for(q=9;q<=15;++q)if(!pr_done(s,q)) {
        for(i=0;i<pr_quest_steps[q];++i)
            if((s->quest[q-1].actions&masks[q-9][i])!=masks[q-9][i])break;
        s->quest[q-1].substep=i;
        if(i==pr_quest_steps[q])pr_finish(s,q,q<=13?1:2);
    }
}
unsigned pr_topics_b(const PrState *s,unsigned target,PrTopic *out,unsigned capacity)
{
    unsigned n=0;
#define ADD(q,i,label) do {if(out && n<capacity) {out[n].id=C(q,i);out[n].text=PR_TEXT_##label;}++n;}while(0)
    if(s->active==PR_M) {
        if(target==H(11,1)) {
            ADD(9,1,Q09_ROOM);
            if(HAS(9,4) && HAS(9,5))ADD(9,2,Q09_BIKE);
        }
        if(target==H(10,1) && pr_done(s,9)) {
            ADD(10,1,Q10_ASK);
            if(HAS(10,0))ADD(10,2,Q10_EMPATHY);
            if(HAS(10,2))ADD(10,3,Q10_HONEST);
        }
        if(target==H(16,1) && pr_done(s,10)) {
            ADD(11,1,Q11_CHILD);
            if(HAS(11,0))ADD(11,2,Q11_NAME);
        }
        if(target==H(16,2) && HAS(11,1))ADD(11,3,Q11_MOTHER);
        if(target==H(16,3) && HAS(11,2))ADD(11,4,Q11_WORKER);
        if(target==H(13,3) && HAS(12,3) && HAS(12,4) && HAS(12,5))ADD(12,1,Q12_REST);
        if(target==H(12,3) && (s->locks&PR_SHADOW) && HAS(13,1) &&
           pr_knows(s,PR_M,PR_FACT_GRETA_NAME))ADD(13,1,Q13_GRETA);
    } else {
        if(target==H(30,1) && !HAS(14,0)) {ADD(14,1,Q14_CONTINUE);ADD(14,2,Q14_SKIP);}
        if(target==H(30,2) && HAS(14,0)) {
            ADD(14,3,Q14_PACK);
            if(HAS(14,1)) {ADD(14,4,Q14_EARLY);ADD(14,5,Q14_STAY);}
        }
        if(target==H(32,3) && HAS(15,2))ADD(15,1,Q15_NORTH);
        if(target==H(33,1) && HAS(15,3))ADD(15,2,Q15_TRUTH);
    }
#undef ADD
    return n;
}
static PrFeedback choose(PrState *s,unsigned target)
{
    switch(target) {
    case C(9,1):MARK(9,0);return SAY(Q09_REPLY);
    case C(9,2):MARK(9,6);return SAY(Q09_BIKE_REPLY);
    case C(10,1):MARK(10,0);return SAY(Q10_REPLY);
    case C(10,2):MARK(10,1);return SAY(Q10_EMPATHY_REPLY);
    case C(10,3):MARK(10,3);pr_set_flag(s,PR_TAVERN_TRUST,1);return SAY(Q10_TRUST);
    case C(11,1):MARK(11,0);return SAY(Q11_CHILD_REPLY);
    case C(11,2):
        MARK(11,1);pr_learn(s,PR_M,PR_FACT_GRETA_NAME,PR_HEARD,PR_FACT_GRETA_NAME);
        return SAY(Q11_NAME_REPLY);
    case C(11,3):MARK(11,2);return SAY(Q11_PERMISSION);
    case C(11,4):
        if(!HAS(11,4))pr_place_item(s,15,PR_INVENTORY_M);
        MARK(11,3);MARK(11,4);
        pr_learn(s,PR_M,PR_FACT_WORKER_STATEMENT,PR_HEARD,PR_FACT_WORKER_STATEMENT);
        return SAY(Q11_WORKER_REPLY);
    case C(12,1):
        if(HAS(12,6))return SAY(ALREADY);
        MARK(12,6);pr_place_item(s,19,13);return SAY(Q12_MORNING);
    case C(13,1):MARK(13,2);return SAY(Q13_REPLY);
    case C(14,1):case C(14,2):
        MARK(14,0);pr_learn(s,PR_K,PR_FACT_IRENA_ATTACK,PR_KNOWN,PR_FACT_IRENA_ATTACK);
        return pr_reply(PR_OK,target==C(14,2)?PR_TEXT_Q14_SHORT:PR_TEXT_Q14_SCENE,PR_CUTSCENE,0);
    case C(14,3):
        pr_place_item(s,8,PR_INVENTORY_K);pr_place_item(s,7,PR_CONTAINER_BASE+8);MARK(14,1);
        pr_learn(s,PR_K,PR_FACT_ADAM_HELP,PR_KNOWN,PR_FACT_ADAM_HELP);return SAY(Q14_PACKED);
    case C(14,4):case C(14,5):
        s->escape_variant=target==C(14,4)?PR_ESCAPE_EARLY:PR_ESCAPE_CONFRONTATION;
        MARK(14,2);return target==C(14,4)?SAY(Q14_EARLY_REPLY):SAY(Q14_CONFRONTATION);
    case C(15,1):MARK(15,3);pr_story_move(s,33);return pr_reply(PR_OK,PR_TEXT_Q15_RESCUE,PR_CUTSCENE,0);
    case C(15,2):MARK(15,4);return SAY(Q15_REPLY);
    default:return DENY(NO_EFFECT);
    }
}
static PrFeedback look(PrState *s,unsigned target)
{
    if(s->active==PR_M) {
        if(target==PR_ITEM(14)) {MARK(9,5);return SAY(Q09_BIBLE);}
        if(target==PR_ROOM_DOOR) {
            if(HAS(12,6)) {MARK(12,7);return SAY(Q12_DOOR_INTACT);}
            MARK(12,1);return SAY(Q12_DOOR);
        }
        if(target==H(13,2)) {
            if(HAS(12,6)) {
                MARK(12,8);pr_learn(s,PR_M,PR_FACT_UNBROKEN_MARKERS,PR_KNOWN,PR_FACT_UNBROKEN_MARKERS);
                return SAY(Q12_WINDOW_INTACT);
            }
            MARK(12,2);return SAY(Q12_WINDOW);
        }
        if(target==H(12,3) && (s->locks&PR_SHADOW)) {MARK(13,1);return SAY(Q13_WARNING);}
    } else {
        if(target==H(31,2)) {MARK(15,0);return SAY(Q15_SIGN);}
        if(target==PR_PIER_LIGHTS) {MARK(15,2);return SAY(Q15_LIGHTS);}
        if(target==H(30,1) && !HAS(14,0))return SAY(Q14_WARNING);
    }
    if(target>PR_ITEM(0) && target<=PR_ITEM(PR_ITEMS))
        return pr_reply(PR_OK,PR_TEXT_OBSERVED,PR_LOG,target);
    return SAY(OBSERVED);
}
static PrFeedback take(PrState *s,unsigned item)
{
    if(pr_has_item(s,s->active,item))return SAY(ALREADY);
    if(s->active!=PR_M || s->world.item_position[item]!=s->hero[PR_M].location)return DENY(NOT_MINE);
    if(item==12) {if(!pr_container_is_open(s,H(13,1)))return DENY(OPEN_FIRST);}
    else if(item==13 || item==14) {if(!pr_container_is_open(s,PR_DRAWER))return DENY(OPEN_FIRST);}
    else if(item>=16 && item<=18) {
        if(!pr_done(s,9))return DENY(BLOCKED);
        if(s->world.item_position[item]==13 && item!=17)return DENY(Q12_LEAVE_MARKER);
    }
    else if(item==19) {if(!HAS(12,6))return DENY(NO_EFFECT);}
    else return DENY(NOT_MINE);
    pr_place_item(s,item,PR_INVENTORY_M);return SAY(TAKEN);
}
static PrFeedback use(PrState *s,unsigned item,unsigned target)
{
    if(item==12 && target==PR_DRAWER) {MARK(9,2);return SAY(Q09_UNLOCKED);}
    if(item==1 && target==H(10,1) && HAS(10,1)) {MARK(10,2);return SAY(Q10_CONTRACT);}
    if(item==18 && target==PR_ROOM_DOOR && HAS(12,1) && !HAS(12,6)) {
        pr_place_item(s,18,13);MARK(12,3);return SAY(Q12_PAPER_SET);
    }
    if(item==17 && target==H(13,2) && HAS(12,2) && !HAS(12,6)) {MARK(12,4);return SAY(Q12_WAX_SET);}
    if(item==16 && target==H(13,2) && HAS(12,2) && HAS(12,4) && !HAS(12,6)) {
        pr_place_item(s,16,13);MARK(12,5);return SAY(Q12_THREAD_SET);
    }
    return DENY(NO_EFFECT);
}
static PrFeedback go(PrState *s,unsigned target)
{
    unsigned actor=s->active,from=s->hero[actor].location;
    if(actor==PR_M) {
        if(from==13 && target==PR_ROOM_DOOR)target=12;
        if(s->locks&PR_SHADOW) {
            if(target!=11 || !HAS(13,3))return DENY(Q13_WARNING);
        }
        if(target==16 && !pr_done(s,10))return DENY(Q10_FIND_WORKER);
        if(pr_move_local(s,target)!=PR_OK)return DENY(BLOCKED);
        if(from==12 && target==11 && (s->locks&PR_SHADOW)) {MARK(13,4);s->locks&=~PR_SHADOW;return SAY(Q13_LEFT);}
        if(target==12 && pr_done(s,11) && pr_done(s,12) && !pr_done(s,13)) {
            MARK(13,0);s->locks|=PR_SHADOW;return SAY(Q13_DARKNESS);
        }
    } else {
        if(from==30 && target==H(30,4))target=31;
        if(from==30 && target==31) {
            if(!HAS(14,2))return DENY(Q14_WINDOW_FIRST);
            MARK(14,3);pr_story_move(s,31);return SAY(Q14_ESCAPED);
        }
        if(from==31 && target==H(31,3))target=32;
        if(from==31 && target==32) {
            if(!HAS(15,0))return DENY(Q15_SIGN_FIRST);
            MARK(15,1);pr_story_move(s,32);return SAY(Q15_BEACH);
        }
        if(from==32 && (target==PR_PIER_WALK || target==PR_PIER_LIGHTS))return SAY(Q15_RETREAT);
        if(from==32 && (target==33 || target==34))return DENY(Q15_CHOOSE_SHORE);
        if(pr_move_local(s,target)!=PR_OK)return DENY(BLOCKED);
    }
    return SAY(MOVED);
}
PrFeedback pr_rules_b(PrState *s,PrAction a)
{
    if(a.verb==PR_HIT && a.target==H(12,3) && (s->locks&PR_SHADOW)) {
        s->quest[12].actions=1;s->quest[12].substep=1;return SAY(Q13_REPELLED);
    }
    if(a.verb==PR_CHOOSE)return choose(s,a.target);
    if(a.verb==PR_LOOK)return look(s,a.target);
    if(a.verb==PR_USE)return use(s,a.source,a.target);
    if(a.verb==PR_TAKE && a.target>PR_ITEM(0) && a.target<=PR_ITEM(PR_ITEMS))return take(s,a.target-PR_ITEM(0));
    if(a.verb==PR_GO)return go(s,a.target);
    if(a.verb==PR_OPEN) {
        if(a.target==PR_DRAWER) {
            if(!HAS(9,2))return DENY(Q09_LOCKED);
            MARK(9,3);return SAY(CONTENTS);
        }
        if(a.target==H(13,1) || a.target==H(15,1))return SAY(CONTENTS);
        if(a.target==H(12,1) && (s->locks&PR_SHADOW)) {
            if(!HAS(13,2))return DENY(Q13_WARNING);
            MARK(13,3);return SAY(Q13_DOOR_OPEN);
        }
    }
    return DENY(NO_EFFECT);
}
