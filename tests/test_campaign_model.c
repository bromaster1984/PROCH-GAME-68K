/* Model tests construct states. These are not the T01-T04 game playthroughs. */
#include "campaign/model.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void test_knowledge_and_items(void)
{
    PrGame game;
    PrState before;
    unsigned item;
    pr_new_game(&game);
    assert(game.current.hero[PR_M].location==1 && game.current.hero[PR_K].location==3);
    for(item=1;item<=PR_ITEMS;++item)assert(pr_item_owner(&game.current,item)==-1);
    assert(game.current.flags==0 && game.current.krystyna_alive==PR_UNKNOWN);
    assert(pr_learn(&game.current,PR_K,PR_FACT_FINANCIAL_PLOT,PR_KNOWN,301)==PR_OK);
    assert(!pr_knows(&game.current,PR_M,PR_FACT_FINANCIAL_PLOT));
    assert(pr_learn(&game.current,PR_K,PR_FACT_FINANCIAL_PLOT,PR_HEARD,301)==PR_OK);
    assert(game.current.hero[PR_K].confidence[PR_FACT_FINANCIAL_PLOT]==PR_KNOWN);
    assert(game.current.hero[PR_K].journal_count==1);
    assert(pr_place_item(&game.current,8,PR_INVENTORY_K)==PR_OK);
    assert(pr_place_item(&game.current,6,PR_CONTAINER_BASE+8)==PR_OK);
    assert(pr_has_item(&game.current,PR_K,6) && !pr_has_item(&game.current,PR_M,6));
    before=game.current;
    assert(pr_place_item(&game.current,8,PR_CONTAINER_BASE+6)==PR_INVALID);
    assert(memcmp(&before,&game.current,sizeof(before))==0);
    assert(pr_place_item(&game.current,6,PR_INVENTORY_M)==PR_OK);
    assert(pr_has_item(&game.current,PR_M,6) && !pr_has_item(&game.current,PR_K,6));
}

static void test_phase_barriers(void)
{
    PrGame game;
    PrState before;
    unsigned first;
    for(first=0;first<2;++first) {
        pr_new_game(&game);
        pr_finish(&game.current,first?8:5,first?2:1);
        before=game.current;
        assert(pr_advance_phase(&game.current,0)==PR_WAITING);
        assert(memcmp(&before,&game.current,sizeof(before))==0);
        pr_finish(&game.current,first?5:8,first?1:2);
        assert(pr_advance_phase(&game.current,0)==PR_OK && game.current.phase==PR_B);
        assert(game.current.hero[0].location==9 && game.current.hero[1].location==30);
        pr_finish(&game.current,13,1);pr_finish(&game.current,15,2);
        assert(pr_advance_phase(&game.current,0)==PR_OK && game.current.phase==PR_C);
        pr_finish(&game.current,19,1);pr_finish(&game.current,24,2);
        before=game.current;
        assert(pr_advance_phase(&game.current,0)==PR_CONFIRMATION);
        assert(memcmp(&before,&game.current,sizeof(before))==0);
        assert(pr_advance_phase(&game.current,1)==PR_OK && game.current.phase==PR_D);
    }
}

static void test_mail(void)
{
    PrGame game;
    pr_new_game(&game);game.current.phase=PR_C;
    pr_place_item(&game.current,28,PR_INVENTORY_K);
    assert(pr_queue_message(&game.current,28,PR_K,PR_M,PR_ROUTE_NEIGHBOUR_IZYDOR_FLOREK,PR_D)==PR_OK);
    assert(!pr_has_item(&game.current,PR_K,28));
    pr_deliver_messages(&game.current);
    assert(game.current.world.item_position[28]==PR_COURIER);
    game.current.phase=PR_D;pr_deliver_messages(&game.current);
    assert(game.current.world.item_position[28]==PR_FLOREK);
    assert(!pr_flag(&game.current,PR_M_KNOWS_ALIVE));
    pr_place_item(&game.current,28,PR_INVENTORY_M);
    assert(pr_read_message(&game.current,28,PR_M)==PR_OK);
    assert(!pr_flag(&game.current,PR_M_KNOWS_ALIVE)); /* explicit authentication comes later */
    assert(pr_read_message(&game.current,28,PR_M)==PR_OK);
    pr_place_item(&game.current,45,PR_INVENTORY_M);game.current.phase=PR_F;
    assert(pr_queue_message(&game.current,45,PR_M,PR_K,PR_ROUTE_IZYDOR,PR_F)==PR_OK);
    pr_deliver_messages(&game.current);
    assert(game.current.world.item_position[45]==PR_COURIER);
    assert(pr_switch_hero(&game.current)==PR_OK);
    assert(pr_has_item(&game.current,PR_K,45));
    assert(pr_read_message(&game.current,45,PR_K)==PR_OK);
    assert(pr_knows(&game.current,PR_K,PR_FACT_FUTURE_LETTER));
    assert(!pr_knows(&game.current,PR_M,PR_FACT_FUTURE_LETTER));
}

static void test_map_and_undo(void)
{
    PrGame game;
    PrState before;
    unsigned scene;
    pr_new_game(&game);
    assert(pr_local_edge(11,22) && pr_local_edge(22,11));
    assert(!pr_local_edge(5,35)); /* scripted journey, not free local walking */
    assert(!pr_scene_allowed(&game.current,3));
    game.current.phase=PR_B;game.current.active=PR_K;
    assert(!pr_scene_allowed(&game.current,12) && !pr_scene_allowed(&game.current,13));
    game.current.phase=PR_D;pr_finish(&game.current,25,2);
    assert(pr_scene_allowed(&game.current,13));
    assert(!pr_scene_allowed(&game.current,23));
    game.current.locks=PR_RESCUE;assert(pr_scene_allowed(&game.current,23));
    game.current.phase=PR_F;game.current.active=PR_M;game.current.locks=0;
    pr_set_flag(&game.current,PR_M_FREE,1);
    pr_finish(&game.current,9,1);pr_finish(&game.current,16,1);pr_finish(&game.current,18,1);
    for(scene=11;scene<=23;++scene)
        if(scene==11||scene==13||scene==15||scene==19||scene==20||scene==22||scene==23)
            assert(pr_scene_allowed(&game.current,scene));
    game.current.phase=PR_D;game.current.active=PR_K;game.current.locks=PR_RESCUE;
    game.current.hero[PR_M].location=23;game.current.hero[PR_K].location=23;
    pr_place_item(&game.current,31,23);pr_place_item(&game.current,26,PR_WORN_K);
    pr_snapshot(&game);before=game.current;
    game.current.player_dead=1;game.current.hero[PR_M].location=38;
    pr_place_item(&game.current,31,PR_INVENTORY_M);pr_place_item(&game.current,26,PR_ABSENT);
    assert(pr_undo(&game)==PR_OK && memcmp(&before,&game.current,sizeof(before))==0);
}

static void test_endings(void)
{
    PrGame game;
    unsigned resolved,alive,marriage,m,k;
    unsigned found=0;
    for(resolved=0;resolved<2;++resolved)for(alive=PR_YES;alive<=PR_NO;++alive)
    for(marriage=PR_YES;marriage<=PR_NO;++marriage)
    for(m=PR_RECONNECT;m<=PR_SEPARATE;++m)for(k=PR_RECONNECT;k<=PR_SEPARATE;++k) {
        enum PrEnding ending,expected;
        pr_new_game(&game);game.current.krystyna_alive=alive;game.current.book_marriage=marriage;
        game.current.m_future=m;game.current.k_future=k;
        pr_set_flag(&game.current,PR_HAUNTING_RESOLVED,resolved);
        expected=!resolved?PR_E04:alive==PR_NO?PR_E01:
            marriage==PR_NO&&m==PR_RECONNECT&&k==PR_RECONNECT?PR_E02:PR_E03;
        ending=pr_ending(&game.current);assert(ending==expected);found|=1u<<ending;
        assert(!pr_can_finish(&game.current));
    }
    assert(found==((1u<<PR_E01)|(1u<<PR_E02)|(1u<<PR_E03)|(1u<<PR_E04)));
}

int main(void)
{
    test_knowledge_and_items();test_phase_barriers();test_mail();test_map_and_undo();test_endings();
    printf("PASS: campaign model (not Q01-Q40); state=%u bytes\n",(unsigned)sizeof(PrState));
    return 0;
}
