#include "rules_internal.h"

#define H(s,n) PR_HOTSPOT(s,n)
#define C(q,n) PR_CHOICE(q,n)
#define HAS(q,n) pr_action_done(s,q,n)
#define MARK(q,n) pr_mark_action(s,q,n)
#define SAY(t) pr_reply(PR_OK,PR_TEXT_##t,PR_LOG,0)
#define DENY(t) pr_reply(PR_DENIED,PR_TEXT_##t,PR_LOG,0)

void pr_refresh_c(PrState *s)
{
    static const uint32_t q16[]={1,3,7,15};
    static const uint32_t q17[]={1,3,15,31,127,511};
    static const uint32_t q18[]={1,7,15,63};
    static const uint32_t q19[]={1,7,15,63,127};
    const uint32_t *steps[]={q16,q17,q18,q19};
    unsigned q,i;
    for(q=16;q<=19;++q)if(!pr_done(s,q)) {
        for(i=0;i<pr_quest_steps[q];++i)
            if((s->quest[q-1].actions&steps[q-16][i])!=steps[q-16][i])break;
        s->quest[q-1].substep=(uint8_t)i;
        if(i==pr_quest_steps[q]) {
            pr_finish(s,q,1);
            if(q==19)pr_set_flag(s,PR_POND_SEEN,1);
        }
    }
}

unsigned pr_topics_c(const PrState *s,unsigned target,PrTopic *out,unsigned capacity)
{
    unsigned n=0;
#define ADD(q,i,label) do {if(out && n<capacity) {out[n].id=C(q,i);out[n].text=PR_TEXT_##label;}++n;}while(0)
    if(s->active!=PR_M)return 0;
    if(target==H(17,2) && pr_done(s,13))ADD(16,1,Q16_MARIANNA);
    if(target==H(17,1) && HAS(16,0))ADD(16,2,Q16_PRIEST);
    if(target==H(18,1) && HAS(16,2))ADD(16,3,Q16_INVITE);
    if(target==H(20,2) && HAS(17,2)) {
        if(s->world.scene_variant[20]&1)ADD(17,2,Q17_DESCEND);
        else ADD(17,1,Q17_CLIMB);
    }
    if(target==PR_LUDWIK && HAS(17,5))ADD(17,3,Q17_WHO);
    if(target==H(20,3) && HAS(17,6)) {
        ADD(17,4,Q17_LETTER_P);
        if(HAS(17,7))ADD(17,5,Q17_CARD);
    }
    if(target==H(20,4) && HAS(18,0)) {
        ADD(18,1,Q18_TOME);
        if(HAS(18,1))ADD(18,2,Q18_CARD);
    }
    if(target==PR_CHRONICLE_MARGIN && HAS(18,4))ADD(18,3,Q18_TRACE);
    if(target==H(23,1) && HAS(19,0) && HAS(19,1) && HAS(19,2) && !HAS(19,3))
        ADD(19,1,Q19_REACH);
#undef ADD
    return n;
}

static PrFeedback choose(PrState *s,unsigned target)
{
    switch(target) {
    case C(16,1):MARK(16,0);return SAY(Q16_MARIANNA_REPLY);
    case C(16,2):MARK(16,1);return SAY(Q16_PRIEST_REPLY);
    case C(16,3):
        if(!HAS(16,3))pr_place_item(s,20,PR_INVENTORY_M);
        MARK(16,3);return SAY(Q16_INVITATION);
    case C(17,1):
        s->world.scene_variant[20]|=1;MARK(17,3);return SAY(Q17_HIGH);
    case C(17,2):
        s->world.scene_variant[20]&=(uint8_t)~1u;
        if(HAS(17,4)) {s->world.scene_variant[20]|=2;MARK(17,5);return SAY(Q17_CHANGED);}
        return SAY(Q17_DOWN_EARLY);
    case C(17,3):
        MARK(17,6);pr_learn(s,PR_M,PR_FACT_GRETA_IDENTITY,PR_KNOWN,PR_FACT_GRETA_IDENTITY);
        return SAY(Q17_LUDWIK_REPLY);
    case C(17,4):MARK(17,7);return SAY(Q17_P_INDEX);
    case C(17,5):
        if(!HAS(17,8))pr_place_item(s,21,PR_INVENTORY_M);
        MARK(17,8);return SAY(Q17_CARD_REPLY);
    case C(18,1):MARK(18,1);return SAY(Q18_TOME_OPEN);
    case C(18,2):MARK(18,2);return SAY(Q18_PAGE_FOUND);
    case C(18,3):
        if(!HAS(18,5))pr_place_item(s,22,PR_INVENTORY_M);
        MARK(18,5);return SAY(Q18_MAP_TRACED);
    case C(19,1):
        MARK(19,3);s->locks|=PR_VISION;pr_story_move(s,24);
        return pr_reply(PR_OK,PR_TEXT_Q19_SLIP,PR_CUTSCENE,0);
    default:return DENY(NO_EFFECT);
    }
}

static PrFeedback look(PrState *s,unsigned target)
{
    if(target==H(20,1) && pr_done(s,16)) {
        MARK(17,1);return SAY(Q17_PORTRAIT);
    }
    if(target==PR_CHRONICLE_PAGE && HAS(18,2)) {
        MARK(18,3);
        pr_learn(s,PR_M,PR_FACT_GRETA_LEGEND,PR_SUSPECT,PR_FACT_GRETA_LEGEND);
        return pr_reply(PR_OK,PR_TEXT_Q18_LEGEND,PR_DOCUMENT,target);
    }
    if(target==PR_CHRONICLE_MARGIN && HAS(18,3)) {MARK(18,4);return SAY(Q18_MARGIN);}
    if(target==H(23,1) && HAS(19,0)) {MARK(19,1);return SAY(Q19_STUMP);}
    if(target==H(23,2) && HAS(19,0)) {MARK(19,2);return SAY(Q19_WATER);}
    if(target==H(24,2) && (s->locks&PR_VISION)) {MARK(19,4);return SAY(Q19_BAG);}
    if(target==PR_OLD_ARMS && (s->locks&PR_VISION)) {MARK(19,5);return SAY(Q19_ARMS);}
    return SAY(OBSERVED);
}
static PrFeedback use(PrState *s,unsigned source,unsigned target)
{
    if(source==19 && target==H(18,1) && HAS(16,1)) {
        MARK(16,2);return SAY(Q16_LACE_SHOWN);
    }
    if(source==20 && target==H(19,1) && pr_done(s,16)) {
        MARK(17,0);return SAY(Q17_SERVANT);
    }
    if(source==H(20,2) && target==H(20,1) && HAS(17,1)) {
        MARK(17,2);return SAY(Q17_LADDER_SET);
    }
    if(source==19 && target==H(20,1) && (s->world.scene_variant[20]&1) && HAS(17,3)) {
        MARK(17,4);return SAY(Q17_MATCH);
    }
    if(source==21 && target==H(20,4) && pr_done(s,17)) {
        MARK(18,0);return SAY(Q18_CATALOG_USED);
    }
    if(source==22 && target==H(22,3) && pr_done(s,18)) {
        MARK(19,0);return SAY(Q19_TRACKED);
    }
    return DENY(NO_EFFECT);
}
static PrFeedback go(PrState *s,unsigned target)
{
    unsigned from=s->hero[s->active].location;
    if(from==24 && (s->locks&PR_VISION)) {
        if(target!=22 && target!=H(24,3))return DENY(Q19_LIGHT);
        /* The exit always works. Unexamined details are narrated on the way. */
        MARK(19,4);MARK(19,5);MARK(19,6);
        s->locks&=(uint8_t)~PR_VISION;pr_story_move(s,22);
        if(s->world.item_position[23]==PR_ABSENT)pr_place_item(s,23,PR_INVENTORY_M);
        pr_learn(s,PR_M,PR_FACT_POND_HAZARD,PR_KNOWN,PR_FACT_POND_HAZARD);
        return SAY(Q19_RETURN);
    }
    if((s->locks&PR_VISION) || (from==20 && (s->world.scene_variant[20]&1)))
        return DENY(Q17_DESCEND_FIRST);
    if(pr_move_local(s,target)!=PR_OK)return DENY(BLOCKED);
    return SAY(MOVED);
}
PrFeedback pr_rules_c(PrState *s,PrAction a)
{
    if(s->active!=PR_M)return DENY(NO_EFFECT);
    if(a.verb==PR_CHOOSE)return choose(s,a.target);
    if(a.verb==PR_LOOK)return look(s,a.target);
    if(a.verb==PR_USE)return use(s,a.source,a.target);
    if(a.verb==PR_GO)return go(s,a.target);
    if(a.verb==PR_OPEN && a.target==H(20,4) && HAS(18,0))
        return pr_reply(PR_OK,PR_TEXT_Q18_CATALOG_USED,PR_DIALOG,H(20,4));
    return DENY(NO_EFFECT);
}
