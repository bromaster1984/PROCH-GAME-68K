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
        if(game.current.locks)assert(pr_switch_hero(&game.current)==PR_DENIED);
        else {
            assert(pr_switch_hero(&game.current)==PR_OK);
            assert(pr_switch_hero(&game.current)==PR_OK);
        }
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

static void b_m_path(int bible,int q12_first)
{
    assert(game.current.active==PR_M);
    go(11);go(12);go(13);
    denied(PR_OPEN,0,PR_DRAWER);open_box(H(13,1));take(12); /* legal early pickup */
    go(12);go(11);choose(H(11,1),C(9,1));
    go(12);go(13);use(12,PR_DRAWER);open_box(PR_DRAWER);
    take(13);look(PR_ITEM(14));if(bible)take(14);
    go(12);go(11);choose(H(11,1),C(9,2));assert(pr_done(&game.current,9));
    if(!q12_first) {
        go(9);go(10);choose(H(10,1),C(10,1));choose(H(10,1),C(10,2));
        denied(PR_CHOOSE,H(10,1),C(10,3));use(1,H(10,1));choose(H(10,1),C(10,3));
        go(9);go(16);denied(PR_CHOOSE,H(16,3),C(11,4));
        choose(H(16,1),C(11,1));choose(H(16,1),C(11,2));
        choose(H(16,2),C(11,3));choose(H(16,3),C(11,4));
        assert(pr_has_item(&game.current,PR_M,15) && pr_done(&game.current,11));
        go(9);go(11);
    }
    go(15);take(18);take(16);take(17);go(11);go(12);go(13);
    denied(PR_CHOOSE,H(13,3),C(12,1));
    look(H(13,2));look(PR_ROOM_DOOR);use(18,PR_ROOM_DOOR);
    denied(PR_USE,16,H(13,2));use(17,H(13,2));use(16,H(13,2));
    choose(H(13,3),C(12,1));take(19); /* pickup before final inspections */
    assert(!pr_done(&game.current,12));look(H(13,2));
    assert(!pr_knows(&game.current,PR_M,PR_FACT_UNBROKEN_MARKERS));
    look(PR_ROOM_DOOR);
    assert(pr_done(&game.current,12));
    go(12);
    if(q12_first) {
        assert(!game.current.locks);go(11);go(9);go(10);
        choose(H(10,1),C(10,1));choose(H(10,1),C(10,2));use(1,H(10,1));choose(H(10,1),C(10,3));
        go(9);go(16);choose(H(16,1),C(11,1));choose(H(16,1),C(11,2));
        choose(H(16,2),C(11,3));choose(H(16,3),C(11,4));go(9);go(11);go(12);
    }
    assert(game.current.locks&PR_SHADOW);denied(PR_SWITCH,0,0);denied(PR_GO,0,13);
    look(H(12,3));step(PR_HIT,0,H(12,3));assert(pr_has_item(&game.current,PR_M,19));
    denied(PR_CHOOSE,H(12,3),C(13,1)); /* reset scene, not inventory or prior Q */
    look(H(12,3));choose(H(12,3),C(13,1));step(PR_OPEN,0,H(12,1));go(11);
    assert(pr_done(&game.current,13) && !game.current.locks);
    assert(pr_has_item(&game.current,PR_M,14)==bible);
}
static void b_k_path(int confrontation,int skip)
{
    assert(game.current.active==PR_K);
    denied(PR_GO,0,31);choose(H(30,1),C(14,skip?2:1));
    denied(PR_GO,0,31);choose(H(30,2),C(14,3));
    choose(H(30,2),C(14,confrontation?5:4));go(31);
    assert(pr_done(&game.current,14) && pr_has_item(&game.current,PR_K,7));
    assert(game.current.escape_variant==(confrontation?PR_ESCAPE_CONFRONTATION:PR_ESCAPE_EARLY));
    denied(PR_GO,0,30);denied(PR_GO,0,32);look(H(31,2));go(32);
    denied(PR_GO,0,33);denied(PR_CHOOSE,H(32,3),C(15,1));
    step(PR_GO,0,PR_PIER_WALK);assert(game.current.hero[PR_K].location==32);
    look(PR_PIER_LIGHTS);choose(H(32,3),C(15,1));assert(game.current.hero[PR_K].location==33);
    choose(H(33,1),C(15,2));assert(pr_done(&game.current,15));
    assert(!pr_knows(&game.current,PR_K,PR_FACT_GRETA_NAME));
}
static void complete_ab(int k_first,int alternate)
{
    unsigned q;
    complete_a(k_first,alternate);
    /* Start B with the opposite hero to exercise both shared barriers. */
    if(game.current.active!=(unsigned)(k_first?PR_K:PR_M))step(PR_SWITCH,0,0);
    if(k_first)b_k_path(alternate,!alternate);else b_m_path(alternate,!alternate);
    assert(game.current.phase==PR_B);step(PR_SWITCH,0,0);
    if(k_first)b_m_path(alternate,!alternate);else b_k_path(alternate,!alternate);
    assert(game.current.phase==PR_C && game.current.hero[PR_M].location==11 && game.current.hero[PR_K].location==33);
    for(q=9;q<=15;++q)assert(pr_done(&game.current,q));
    assert(!pr_knows(&game.current,PR_M,PR_FACT_IRENA_ATTACK));
    assert(!pr_knows(&game.current,PR_K,PR_FACT_UNBROKEN_MARKERS));
}

static void c_m_path(int inspect_vision,int do_q20)
{
    unsigned q,item;
    uint16_t before_vision[PR_ITEMS+1];
    complete_ab(0,0);
    assert(game.current.active==PR_K);
    step(PR_SWITCH,0,0);
    denied(PR_GO,0,19);denied(PR_USE,19,H(18,1));
    go(9);go(18);go(17);
    choose(H(17,2),C(16,1));choose(H(17,1),C(16,2));
    go(18);use(19,H(18,1));choose(H(18,1),C(16,3));
    assert(pr_done(&game.current,16) && pr_has_item(&game.current,PR_M,20));
    go(19);use(20,H(19,1));go(20);
    denied(PR_USE,19,H(20,1));look(H(20,1));
    step(PR_USE,H(20,2),H(20,1));choose(H(20,2),C(17,1));
    denied(PR_GO,0,19);use(19,H(20,1));choose(H(20,2),C(17,2));
    assert((game.current.world.scene_variant[20]&2)!=0);
    choose(PR_LUDWIK,C(17,3));
    assert(pr_knows(&game.current,PR_M,PR_FACT_GRETA_IDENTITY));
    assert(!pr_knows(&game.current,PR_K,PR_FACT_GRETA_IDENTITY));
    choose(H(20,3),C(17,4));choose(H(20,3),C(17,5));
    assert(pr_done(&game.current,17) && pr_has_item(&game.current,PR_M,21));
    use(21,H(20,4));choose(H(20,4),C(18,1));choose(H(20,4),C(18,2));
    look(PR_CHRONICLE_PAGE);look(PR_CHRONICLE_MARGIN);
    assert(game.current.hero[PR_M].confidence[PR_FACT_GRETA_LEGEND]==PR_SUSPECT);
    choose(PR_CHRONICLE_MARGIN,C(18,3));
    assert(pr_done(&game.current,18) && pr_has_item(&game.current,PR_M,22));
    go(19);go(18);go(9);go(11);go(22);
    denied(PR_GO,0,24);use(22,H(22,3));go(23);
    look(H(23,1));look(H(23,2));
    memcpy(before_vision,game.current.world.item_position,sizeof(before_vision));
    choose(H(23,1),C(19,1));
    assert(game.current.hero[PR_M].location==24 && (game.current.locks&PR_VISION));
    denied(PR_SWITCH,0,0);denied(PR_TAKE,0,PR_ITEM(23));
    denied(PR_GO,0,23);
    if(inspect_vision) {look(H(24,2));look(PR_OLD_ARMS);}
    step(PR_GO,0,H(24,3));
    assert(game.current.hero[PR_M].location==22 && game.current.locks==0);
    assert(pr_has_item(&game.current,PR_M,23) && pr_done(&game.current,19));
    for(item=1;item<=PR_ITEMS;++item)if(item!=23)
        assert(game.current.world.item_position[item]==before_vision[item]);
    assert(pr_flag(&game.current,PR_POND_SEEN));
    assert(pr_knows(&game.current,PR_M,PR_FACT_POND_HAZARD));
    assert(!pr_knows(&game.current,PR_K,PR_FACT_POND_HAZARD));
    for(q=16;q<=19;++q)assert(pr_done(&game.current,q));
    assert(game.current.phase==PR_C); /* K has not completed Q24. */
    assert(!pr_done(&game.current,20) && !pr_flag(&game.current,PR_HONEST_KRYSTYNA));
    if(do_q20) {
        go(11);go(9);go(18);
        denied(PR_CHOOSE,H(18,1),C(20,2));
        denied(PR_USE,1,H(18,1));
        choose(H(18,1),C(20,1));choose(H(18,1),C(20,2));
        assert(!pr_done(&game.current,20) && !pr_flag(&game.current,PR_HONEST_KRYSTYNA));
        denied(PR_USE,1,H(18,1));
        use(3,H(18,1));
        assert(pr_has_item(&game.current,PR_M,3));
        assert(!pr_done(&game.current,20) && !pr_flag(&game.current,PR_HONEST_KRYSTYNA));
        choose(H(18,1),C(20,3));
        assert(pr_done(&game.current,20) && pr_flag(&game.current,PR_HONEST_KRYSTYNA));
        assert(pr_has_item(&game.current,PR_M,3));
    }
}

static void c_k_q21(void)
{
    complete_ab(0,0);
    assert(game.current.active==PR_K && game.current.hero[PR_K].location==33);
    denied(PR_OPEN,0,H(33,3));denied(PR_TAKE,0,PR_ITEM(24));
    denied(PR_CHOOSE,H(33,2),C(21,2));
    choose(H(33,1),C(21,1));
    denied(PR_TAKE,0,PR_ITEM(24));open_box(H(33,3));
    take(25);take(24);
    assert(pr_has_item(&game.current,PR_K,24) && pr_has_item(&game.current,PR_K,25));
    assert(!pr_has_item(&game.current,PR_M,24));
    denied(PR_CHOOSE,H(33,2),C(21,4));
    denied(PR_USE,7,H(33,2));
    use(25,H(33,2));use(24,H(33,2));
    choose(H(33,2),C(21,2));choose(H(33,2),C(21,3));
    assert(!pr_has_item(&game.current,PR_K,26));
    choose(H(33,2),C(21,4));
    assert(pr_has_item(&game.current,PR_K,26) && !pr_done(&game.current,21));
    denied(PR_USE,24,PR_SELF_PORTRAIT);
    use(26,PR_SELF_PORTRAIT);
    assert(pr_done(&game.current,21) && pr_flag(&game.current,PR_DISGUISE));
    assert(game.current.quest[20].substep==4);
    assert(game.current.world.item_position[26]==PR_WORN_K);
    assert(pr_has_item(&game.current,PR_K,24) && pr_has_item(&game.current,PR_K,25));
    assert(game.current.phase==PR_C && !pr_done(&game.current,22));
    step(PR_SWITCH,0,0);
    assert(!pr_has_item(&game.current,PR_M,26));
}

static void c_k_q22(int skip)
{
    PrState expected;
    c_k_q21();
    step(PR_SWITCH,0,0);
    assert(game.current.active==PR_K && game.current.phase==PR_C);
    denied(PR_CHOOSE,H(33,2),C(23,2));
    denied(PR_GO,0,34); /* There is no direct route from the hut. */
    go(32);denied(PR_GO,0,31);go(34);
    assert(!pr_done(&game.current,22) && !pr_flag(&game.current,PR_SAFE_COURIER));
    assert(!pr_has_item(&game.current,PR_K,27));
    if(skip) {
        go(32);go(33);
        assert(!pr_done(&game.current,22) && pr_done(&game.current,21));
        return;
    }
    look(H(34,2));
    assert(game.current.quest[21].actions==0); /* Looking before the offer is harmless. */
    denied(PR_USE,25,H(34,2));
    denied(PR_CHOOSE,H(34,2),C(22,2));
    choose(H(34,1),C(22,1));
    denied(PR_CHOOSE,H(34,2),C(22,2));
    look(H(34,2));
    denied(PR_CHOOSE,H(34,2),C(22,2));
    use(25,H(34,2));
    assert(pr_has_item(&game.current,PR_K,25));
    expected=game.current;
    assert(step(PR_CHOOSE,H(34,2),C(22,3)).text==PR_TEXT_Q22_WRONG);
    assert(memcmp(&expected,&game.current,sizeof(expected))==0);
    choose(H(34,2),C(22,2));
    expected=game.current;
    expected.quest[21].actions&=~((uint32_t)(1u<<3)|(1u<<4));
    assert(step(PR_CHOOSE,H(34,2),C(22,2)).text==PR_TEXT_Q22_WRONG);
    assert(memcmp(&expected,&game.current,sizeof(expected))==0);
    choose(H(34,2),C(22,2));choose(H(34,2),C(22,3));
    assert(!pr_done(&game.current,22) && !pr_flag(&game.current,PR_SAFE_COURIER));
    assert(!pr_has_item(&game.current,PR_K,27));
    choose(H(34,2),C(22,4));
    assert(!pr_done(&game.current,22) && !pr_has_item(&game.current,PR_K,27));
    choose(H(34,1),C(22,5));
    assert(pr_done(&game.current,22) && pr_flag(&game.current,PR_SAFE_COURIER));
    assert(game.current.quest[21].substep==4 && pr_has_item(&game.current,PR_K,27));
    assert(pr_has_item(&game.current,PR_K,25) && !pr_done(&game.current,23));
    denied(PR_CHOOSE,H(34,1),C(22,5));
    go(32);go(33);
}

static void c_k_q23(int missing_paper,int use_letter)
{
    PrState before;
    c_k_q22(0);
    assert(game.current.active==PR_K && game.current.hero[PR_K].location==33);
    denied(PR_CHOOSE,H(33,2),C(23,3));
    if(missing_paper) {
        /* Fixture for the Q08 paper having been used up before Q23. */
        game.current.world.item_position[10]=PR_CONSUMED;
        denied(PR_CHOOSE,H(33,2),C(23,2));
        choose(H(33,2),C(23,1));
        assert(pr_has_item(&game.current,PR_K,10));
        game.current.world.item_position[10]=PR_CONSUMED;
        choose(H(33,2),C(23,1)); /* the hut has another sheet */
        assert(pr_has_item(&game.current,PR_K,10));
    } else denied(PR_CHOOSE,H(33,2),C(23,1));
    assert(pr_has_item(&game.current,PR_K,11) && pr_has_item(&game.current,PR_K,27));
    choose(H(33,2),C(23,2));
    denied(PR_CHOOSE,H(33,2),C(23,4));
    before=game.current;
    denied(PR_CHOOSE,H(33,2),C(23,6)); /* wrong wording is never offered */
    assert(memcmp(&before,&game.current,sizeof(before))==0);
    assert(!pr_has_item(&game.current,PR_K,28));
    choose(H(33,2),C(23,3));
    go(32);go(34);denied(PR_CHOOSE,H(34,1),C(23,5));
    go(32);go(33);choose(H(33,2),C(23,4));
    assert(pr_has_item(&game.current,PR_K,28));
    assert(!pr_done(&game.current,23) && !pr_flag(&game.current,PR_LETTER_SENT));
    go(32);go(34);
    if(use_letter)use(28,H(34,1));else choose(H(34,1),C(23,5));
    assert(pr_done(&game.current,23) && pr_flag(&game.current,PR_LETTER_SENT));
    assert(game.current.quest[22].substep==4);
    assert(game.current.world.item_position[28]==PR_COURIER);
    assert(game.current.messages[0].item==28 && game.current.messages[0].state==PR_MSG_WAITING);
    assert(game.current.messages[0].route==PR_ROUTE_NEIGHBOUR_IZYDOR_FLOREK);
    assert(!pr_has_item(&game.current,PR_K,28) && pr_has_item(&game.current,PR_K,27));
    assert(pr_has_item(&game.current,PR_K,11));
    denied(PR_CHOOSE,H(34,1),C(23,5));denied(PR_USE,28,H(34,1));
    step(PR_SWITCH,0,0);
    assert(game.current.world.item_position[28]==PR_COURIER);
    assert(!pr_flag(&game.current,PR_M_KNOWS_ALIVE));
    assert(!pr_knows(&game.current,PR_M,PR_FACT_ALIVE));
    if(!missing_paper) {
        /* Q24 is not implemented yet: satisfy its gate only in this model fixture. */
        pr_finish(&game.current,19,1);pr_finish(&game.current,24,2);
        before=game.current;
        assert(pr_advance_phase(&game.current,0)==PR_CONFIRMATION);
        assert(memcmp(&before,&game.current,sizeof(before))==0);
        assert(pr_advance_phase(&game.current,1)==PR_OK);
        assert(game.current.phase==PR_D);
        assert(game.current.world.item_position[28]==PR_FLOREK);
        assert(game.current.messages[0].state==PR_MSG_DELIVERED);
        assert(!pr_flag(&game.current,PR_M_KNOWS_ALIVE));
        assert(!pr_knows(&game.current,PR_M,PR_FACT_ALIVE));
    }
}

int main(void)
{
    complete_a(0,0);complete_a(0,1);complete_a(1,0);complete_a(1,1);
    complete_ab(0,0);complete_ab(0,1);complete_ab(1,0);complete_ab(1,1);
    c_m_path(0,0);c_m_path(1,0);c_m_path(0,1);
    c_k_q21();
    c_k_q22(1);c_k_q22(0);
    c_k_q23(0,0);c_k_q23(1,1);
    test_modal_and_negative_actions();
    puts("PASS: Q01-Q20 M, Q21-Q23 K action playthroughs, optional Q20/Q22 skip, C vision, A/B variants and isolation");
    return 0;
}
