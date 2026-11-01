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
    static const uint32_t q22[]={1,3,63,127};
    static const uint32_t q23[]={1,3,7,15};
    unsigned i;
    if(!pr_done(s,21)) {
        for(i=0;i<pr_quest_steps[21];++i)
            if((s->quest[20].actions&q21[i])!=q21[i])break;
        s->quest[20].substep=(uint8_t)i;
        if(i==pr_quest_steps[21]) {
            pr_finish(s,21,2);
            pr_set_flag(s,PR_DISGUISE,1);
        }
    }
    if(pr_done(s,21) && !pr_done(s,22)) {
        for(i=0;i<pr_quest_steps[22];++i)
            if((s->quest[21].actions&q22[i])!=q22[i])break;
        s->quest[21].substep=(uint8_t)i;
        if(i==pr_quest_steps[22]) {
            pr_finish(s,22,2);
            pr_set_flag(s,PR_SAFE_COURIER,1);
        }
    }
    if(pr_done(s,22) && !pr_done(s,23)) {
        for(i=0;i<pr_quest_steps[23];++i)
            if((s->quest[22].actions&q23[i])!=q23[i])break;
        s->quest[22].substep=(uint8_t)i;
        if(i==pr_quest_steps[23]) {
            pr_finish(s,23,2);
            pr_set_flag(s,PR_LETTER_SENT,1);
        }
    }
}

unsigned pr_topics_c_k(const PrState *s,unsigned target,PrTopic *out,unsigned capacity)
{
    unsigned n=0;
#define ADD(q,i,label) do {if(out && n<capacity) {out[n].id=C(q,i);out[n].text=PR_TEXT_##label;}++n;}while(0)
    if(s->active!=PR_K || !pr_done(s,15))return 0;
    if(target==H(33,1) && !HAS(21,0))ADD(21,1,Q21_ASK);
    if(target==H(33,2) && HAS(21,3) && HAS(21,4)) {
        if(!HAS(21,5))ADD(21,2,Q21_CUT);
        else if(!HAS(21,6))ADD(21,3,Q21_LENGTH);
        else if(!HAS(21,7))ADD(21,4,Q21_SEW);
    }
    if(pr_done(s,21) && !pr_done(s,22)) {
        if(target==H(34,1)) {
            if(!HAS(22,0))ADD(22,1,Q22_ASK);
            else if(HAS(22,5))ADD(22,5,Q22_COURIER);
        }
        if(target==H(34,2) && HAS(22,2) && !HAS(22,5)) {
            ADD(22,2,Q22_LINK_LEFT_MIDDLE);
            ADD(22,3,Q22_LINK_MIDDLE_RIGHT);
            if(HAS(22,3) && HAS(22,4))ADD(22,4,Q22_CONFIRM);
        }
    }
    if(pr_done(s,22)) {
        if(target==H(33,2)) {
            if(!pr_has_item(s,PR_K,10))ADD(23,1,Q23_TAKE_EXTRA_PAPER);
            if(!pr_done(s,23) && pr_has_item(s,PR_K,10) &&
               pr_has_item(s,PR_K,11) && pr_has_item(s,PR_K,27)) {
                if(!HAS(23,0))ADD(23,2,Q23_WRITE);
                else if(!HAS(23,1))ADD(23,3,Q23_WORDS);
                else if(!HAS(23,2))ADD(23,4,Q23_MEMORY);
            }
        }
        if(target==H(34,1) && HAS(23,2) && !pr_done(s,23) &&
           pr_has_item(s,PR_K,28))ADD(23,5,Q23_SEND);
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
    case C(22,1):MARK(22,0);return SAY(Q22_ASK_REPLY);
    case C(22,2):
        if(HAS(22,4) || HAS(22,3))goto wrong_link;
        MARK(22,3);return SAY(Q22_LINKED);
    case C(22,3):
        if(!HAS(22,3) || HAS(22,4))goto wrong_link;
        MARK(22,4);return SAY(Q22_LINKED);
    case C(22,4):MARK(22,5);return SAY(Q22_NET_REPAIRED);
    case C(22,5):
        if(!HAS(22,6))pr_place_item(s,27,PR_INVENTORY_K);
        MARK(22,6);return SAY(Q22_ADDRESS);
    case C(23,1):
        pr_place_item(s,10,PR_INVENTORY_K);return SAY(Q23_PAPER_TAKEN);
    case C(23,2):MARK(23,0);return SAY(Q23_DRAFT_REPLY);
    case C(23,3):MARK(23,1);return SAY(Q23_WORDS);
    case C(23,4):
        pr_place_item(s,28,PR_INVENTORY_K);MARK(23,2);
        return SAY(Q23_MEMORY_REPLY);
    case C(23,5):
        if(pr_queue_message(s,28,PR_K,PR_M,
                            PR_ROUTE_NEIGHBOUR_IZYDOR_FLOREK,PR_D)!=PR_OK)
            return DENY(BLOCKED);
        MARK(23,3);return SAY(Q23_SENT_REPLY);
    default:return DENY(NO_EFFECT);
    }
wrong_link:
    /* Only the two connections are undone. The conversation, observation,
     * needle, inventory and other quests remain as they were. */
    s->quest[21].actions&=~(PR_BIT(3)|PR_BIT(4));
    return SAY(Q22_WRONG);
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
    if(source==25 && target==H(34,2) && pr_done(s,21) &&
       HAS(22,0) && HAS(22,1) && !pr_done(s,22)) {
        MARK(22,2);return SAY(Q22_NEEDLE);
    }
    if(source==28 && target==H(34,1) && pr_done(s,22) && HAS(23,2) &&
       !pr_done(s,23))return choose(s,C(23,5));
    return DENY(NO_EFFECT);
}

PrFeedback pr_rules_c_k(PrState *s,PrAction a)
{
    if(s->active!=PR_K)return DENY(NO_EFFECT);
    if(a.verb==PR_CHOOSE)return choose(s,a.target);
    if(a.verb==PR_LOOK) {
        if(a.target==H(34,2) && pr_done(s,21) && HAS(22,0) && !pr_done(s,22)) {
            MARK(22,1);return SAY(Q22_NET);
        }
        return SAY(OBSERVED);
    }
    if(a.verb==PR_USE)return use(s,a.source,a.target);
    if(a.verb==PR_GO) {
        if(!pr_done(s,21) || a.target<32 || a.target>34 ||
           pr_move_local(s,a.target)!=PR_OK)return DENY(BLOCKED);
        return SAY(MOVED);
    }
    if(a.verb==PR_TAKE && a.target>PR_ITEM(0) && a.target<=PR_ITEM(PR_ITEMS))
        return take(s,a.target-PR_ITEM(0));
    if(a.verb==PR_OPEN && a.target==H(33,3) && HAS(21,0))return SAY(CONTENTS);
    return DENY(NO_EFFECT);
}
