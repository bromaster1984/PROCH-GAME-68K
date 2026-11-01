/* Action-level chapter A playthroughs. No quest completion/flag setters. */
#include "campaign/rules.h"
#include "campaign_data.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define H(s,n) PR_HOTSPOT(s,n)
#define C(q,n) PR_CHOICE(q,n)
static PrGame game;
static int interleave;

static PrFeedback step(unsigned verb,unsigned source,unsigned target)
{
    PrAction a;
    PrFeedback f;
    a.verb=verb;a.source=source;a.target=target;
    f=pr_act(&game,a);
    if(f.result!=PR_OK)fprintf(stderr,"Denied action %u/%u/%u at hero %u L%u: %s\n",
        verb,source,target,game.current.active,game.current.hero[game.current.active].location,pr_texts[f.text]);
    assert(f.result==PR_OK);
    if(interleave) {
        PrState before=game.current;
        assert(pr_switch_hero(&game.current)==PR_OK);
        assert(pr_switch_hero(&game.current)==PR_OK);
        assert(memcmp(&before,&game.current,sizeof(before))==0);
    }
    return f;
}
static void denied(unsigned verb,unsigned source,unsigned target)
{
    PrGame before=game;
    PrAction a;
    a.verb=verb;a.source=source;a.target=target;
    assert(pr_act(&game,a).result!=PR_OK);
    assert(memcmp(&before,&game,sizeof(game))==0);
}
static void look(unsigned target) {step(PR_LOOK,0,target);}
static void open_box(unsigned target) {assert(step(PR_OPEN,0,target).presentation==PR_CONTAINER);}
static void take(unsigned item) {step(PR_TAKE,0,PR_ITEM(item));}
static void use(unsigned item,unsigned target) {step(PR_USE,item,target);}
static void go(unsigned scene) {step(PR_GO,0,scene);assert(game.current.hero[game.current.active].location==scene);}
static void choose(unsigned npc,unsigned topic)
{
    PrTopic topics[8];
    unsigned i,n=pr_topics(&game.current,npc,topics,8);
    for(i=0;i<n && i<8;++i)if(topics[i].id==topic)break;
    assert(i<n && i<8);
    assert(step(PR_TALK,0,npc).presentation==PR_DIALOG);
    step(PR_CHOOSE,npc,topic);
}

static void m_path(int address)
{
    assert(game.current.active==PR_M);
    denied(PR_CHOOSE,H(1,1),C(1,2)); /* acceptance needs both clues */
    look(H(1,2)); /* reading before asking remains useful */
    choose(H(1,1),C(1,1));choose(H(1,1),C(1,2));
    assert(pr_has_item(&game.current,PR_M,1) && pr_has_item(&game.current,PR_M,2));
    go(2);denied(PR_GO,0,4);choose(H(2,1),C(1,3));
    assert(pr_done(&game.current,1));
    assert(pr_has_item(&game.current,PR_M,3));
    choose(H(2,1),C(1,3)); /* no duplicated reward or journal entry */
    go(4);
    denied(PR_CHOOSE,H(4,1),C(2,1));
    if(address) {
        use(1,H(4,1));choose(H(4,1),C(2,1));choose(H(4,1),C(2,2));
        assert(pr_done(&game.current,2) && pr_flag(&game.current,PR_ADDRESS_LEFT));
    }
    go(5);denied(PR_GO,0,6);denied(PR_USE,2,H(5,3));
    look(H(5,2));use(2,H(5,3));
    assert(game.current.hero[PR_M].location==6);
    denied(PR_GO,0,7);denied(PR_CHOOSE,H(6,2),C(3,2));
    choose(H(6,1),C(3,1));choose(H(6,2),C(3,2));
    assert(pr_done(&game.current,3));
    go(7);denied(PR_OPEN,0,H(7,3));denied(PR_TAKE,0,PR_ITEM(4));
    choose(H(7,1),C(4,1));
    denied(PR_CHOOSE,H(7,1),C(4,2));
    look(H(7,2));look(PR_VALVE);choose(H(7,1),C(4,2));
    denied(PR_TAKE,0,PR_ITEM(4));open_box(H(7,3));take(4);take(5);
    assert(game.current.quest[3].substep==3);
    denied(PR_CHOOSE,H(7,1),C(4,3));
    use(4,PR_VALVE);assert(game.current.world.item_state[41]==1);
    assert(game.current.quest[3].substep==4);
    denied(PR_USE,41,PR_COMPRESSOR_BODY);use(5,PR_ITEM(41));
    assert(game.current.world.item_state[41]==2);
    use(41,PR_COMPRESSOR_BODY);use(4,PR_VALVE);
    assert(game.current.world.item_state[41]==3 && !pr_has_item(&game.current,PR_M,41));
    assert(game.current.quest[3].substep==5);
    denied(PR_USE,4,H(7,3));choose(H(7,1),C(4,3));
    denied(PR_GO,0,6);use(4,H(7,3));denied(PR_GO,0,6);use(5,H(7,3));
    take(4);assert(!pr_has_item(&game.current,PR_M,4));
    go(6);assert(pr_done(&game.current,4) && pr_flag(&game.current,PR_TRAIN_REPAIRED));
    go(8);denied(PR_GO,0,9);denied(PR_CHOOSE,H(8,1),C(5,1));
    use(1,H(8,1));choose(H(8,1),C(5,1));
    denied(PR_GO,0,PR_TAVERN_APPROACH);look(H(9,3));look(PR_FACTORY_GATE);
    step(PR_GO,0,PR_TAVERN_APPROACH);assert(pr_done(&game.current,5));
    assert(!pr_knows(&game.current,PR_M,PR_FACT_MAIL_CONTROL));
    assert(!pr_knows(&game.current,PR_M,PR_FACT_SERVANT_LUIZA));
}

static void k_path(void)
{
    assert(game.current.active==PR_K);
    denied(PR_USE,1,H(3,1));denied(PR_CHOOSE,PR_DEPARTURE,C(6,1));
    denied(PR_TAKE,0,PR_ITEM(6));open_box(H(3,1));
    take(7);take(6); /* pickups before examination */
    look(PR_ITEM(6));use(7,H(3,3));use(6,H(3,3));
    assert(pr_has_item(&game.current,PR_K,6) && pr_has_item(&game.current,PR_K,7));
    assert(pr_has_item(&game.current,PR_K,8));
    choose(PR_DEPARTURE,C(6,1));
    assert(game.current.hero[PR_K].location==25 && pr_done(&game.current,6));
    assert(pr_has_item(&game.current,PR_K,6) && pr_has_item(&game.current,PR_K,7));
    /* Early pickups for Q08 must survive doing Q07 first. */
    open_box(H(25,1));take(10);take(11);denied(PR_USE,10,PR_ITEM(11));
    go(26);denied(PR_GO,0,28);choose(H(26,1),C(7,1));
    go(28);denied(PR_GO,0,29);go(26);go(27);
    choose(H(27,1),C(7,2));assert(pr_has_item(&game.current,PR_K,9));
    assert(pr_knows(&game.current,PR_K,PR_FACT_SERVANT_LUIZA));
    go(26);go(28);use(9,H(28,2));
    assert(!pr_has_item(&game.current,PR_K,9));
    go(29);choose(H(29,1),C(7,3));
    assert(!pr_done(&game.current,7));go(28);assert(pr_done(&game.current,7));
    go(26);denied(PR_CHOOSE,H(26,1),C(8,2));go(25);
    use(11,PR_ITEM(10));choose(PR_LETTER_DESK,C(8,1));
    go(26);use(10,H(26,2));denied(PR_LOOK,0,PR_OPENED_ENVELOPE);
    go(25);denied(PR_CHOOSE,PR_DEPARTURE,C(8,3));go(26);
    look(PR_OPENED_ENVELOPE);choose(H(26,1),C(8,2));
    go(25);choose(PR_DEPARTURE,C(8,3));assert(pr_done(&game.current,8));
    assert(pr_flag(&game.current,PR_INTERCEPTED_LETTER));
    assert(!pr_knows(&game.current,PR_K,PR_FACT_TASK));
    assert(!pr_knows(&game.current,PR_K,PR_FACT_BROOCH));
}

static void complete_a(int k_first,int address)
{
    unsigned q;
    pr_new_game(&game);interleave=1;
    if(k_first) {step(PR_SWITCH,0,0);k_path();}
    else m_path(address);
    assert(game.current.phase==PR_A);
    step(PR_SWITCH,0,0);
    if(k_first)m_path(address);else k_path();
    assert(game.current.phase==PR_B);
    assert(game.current.hero[PR_M].location==9 && game.current.hero[PR_K].location==30);
    assert(pr_has_item(&game.current,PR_M,1) && pr_has_item(&game.current,PR_M,2));
    assert(pr_has_item(&game.current,PR_M,3));
    assert(pr_has_item(&game.current,PR_K,6) && pr_has_item(&game.current,PR_K,7));
    for(q=1;q<=8;++q)if(q!=2 || address)assert(pr_done(&game.current,q));
    assert(pr_done(&game.current,2)==address);
    assert(pr_flag(&game.current,PR_ADDRESS_LEFT)==address);
    assert(game.current.krystyna_alive==PR_UNKNOWN && game.current.book_marriage==PR_UNKNOWN);
    assert(!pr_knows(&game.current,PR_M,PR_FACT_MAIL_CONTROL));
    assert(!pr_knows(&game.current,PR_K,PR_FACT_TRAIN_VALVE));
    assert(!pr_scene_allowed(&game.current,25));
}

static void test_modal_and_negative_actions(void)
{
    PrState before;
    pr_new_game(&game);interleave=0;
    denied(PR_HIT,0,H(1,1));denied(PR_EAT,0,H(1,2));
    denied(PR_LOOK,0,H(30,1));denied(PR_CHOOSE,H(1,1),C(8,3));
    game.current.locks=PR_MODAL;before=game.current;
    denied(PR_SWITCH,0,0);assert(memcmp(&before,&game.current,sizeof(before))==0);
    denied(PR_GO,0,2);
}

int main(void)
{
    complete_a(0,0);complete_a(0,1);complete_a(1,0);complete_a(1,1);
    test_modal_and_negative_actions();
    puts("PASS: Q01-Q08 action playthroughs, M/K first, optional address, interleaved switches, guarded wrong actions");
    return 0;
}
