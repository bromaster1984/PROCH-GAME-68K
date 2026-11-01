#include "rules_internal.h"

#define H(s,n) PR_HOTSPOT(s,n)
#define C(q,n) PR_CHOICE(q,n)
#define HAS(q,n) pr_action_done(s,q,n)
#define MARK(q,n) pr_mark_action(s,q,n)
#define SAY(t) pr_reply(PR_OK,PR_TEXT_##t,PR_LOG,0)
#define DENY(t) pr_reply(PR_DENIED,PR_TEXT_##t,PR_LOG,0)

void pr_refresh_c_k(PrState *s)
{
    static const uint32_t q21[]={1,7,255,511};
    unsigned i;
    if(pr_done(s,21))return;
    for(i=0;i<pr_quest_steps[21];++i)
        if((s->quest[20].actions&q21[i])!=q21[i])break;
    s->quest[20].substep=(uint8_t)i;
    if(i==pr_quest_steps[21]) {
        pr_finish(s,21,2);
        pr_set_flag(s,PR_DISGUISE,1);
    }
}

unsigned pr_topics_c_k(const PrState *s,unsigned target,PrTopic *out,unsigned capacity)
{
    unsigned n=0;
#define ADD(i,label) do {if(out && n<capacity) {out[n].id=C(21,i);out[n].text=PR_TEXT_##label;}++n;}while(0)
    if(s->active!=PR_K || !pr_done(s,15))return 0;
    if(target==H(33,1) && !HAS(21,0))ADD(1,Q21_ASK);
    if(target==H(33,2) && HAS(21,3) && HAS(21,4)) {
        if(!HAS(21,5))ADD(2,Q21_CUT);
        else if(!HAS(21,6))ADD(3,Q21_LENGTH);
        else if(!HAS(21,7))ADD(4,Q21_SEW);
    }
#undef ADD
    return n;
}

static PrFeedback choose(PrState *s,unsigned target)
{
    switch(target) {
    case C(21,1):MARK(21,0);return SAY(Q21_ASK_REPLY);
    case C(21,2):MARK(21,5);return SAY(Q21_CUT_REPLY);
    case C(21,3):MARK(21,6);return SAY(Q21_LENGTH_REPLY);
    case C(21,4):
        MARK(21,7);pr_place_item(s,26,PR_INVENTORY_K);
        return SAY(Q21_SEWN);
    default:return DENY(NO_EFFECT);
    }
}

static PrFeedback take(PrState *s,unsigned item)
{
    if(pr_has_item(s,PR_K,item))return SAY(ALREADY);
    if((item!=24 && item!=25) || !HAS(21,0) ||
       !pr_container_is_open(s,H(33,3)) || s->world.item_position[item]!=33)
        return DENY(OPEN_FIRST);
    pr_place_item(s,item,PR_INVENTORY_K);
    MARK(21,item==24?1:2);
    return SAY(TAKEN);
}

static PrFeedback use(PrState *s,unsigned source,unsigned target)
{
    if(target==H(33,2) && HAS(21,1) && HAS(21,2)) {
        if(source==24) {MARK(21,3);return SAY(Q21_FABRIC_SET);}
        if(source==25) {MARK(21,4);return SAY(Q21_NEEDLE_SET);}
    }
    if(source==26 && target==PR_SELF_PORTRAIT && HAS(21,7)) {
        pr_place_item(s,26,PR_WORN_K);MARK(21,8);
        return SAY(Q21_DRESSED);
    }
    return DENY(NO_EFFECT);
}

PrFeedback pr_rules_c_k(PrState *s,PrAction a)
{
    if(s->active!=PR_K)return DENY(NO_EFFECT);
    if(a.verb==PR_CHOOSE)return choose(s,a.target);
    if(a.verb==PR_LOOK)return SAY(OBSERVED);
    if(a.verb==PR_USE)return use(s,a.source,a.target);
    if(a.verb==PR_TAKE && a.target>PR_ITEM(0) && a.target<=PR_ITEM(PR_ITEMS))
        return take(s,a.target-PR_ITEM(0));
    if(a.verb==PR_OPEN && a.target==H(33,3) && HAS(21,0))return SAY(CONTENTS);
    return DENY(NO_EFFECT);
}
