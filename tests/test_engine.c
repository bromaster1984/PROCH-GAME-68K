#include "engine.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void switch_roundtrip(ProchState *s)
{
    ProchState before = *s;
    assert(proch_switch(s) == REPLY_SWITCHED);
    assert(proch_switch(s) == REPLY_SWITCHED);
    assert(memcmp(s, &before, sizeof(*s)) == 0);
}

static enum ProchReply act(ProchState *s, enum ProchVerb v, enum ProchTarget t, unsigned item)
{
    enum ProchReply result = proch_action(s, v, t, item);
    switch_roundtrip(s);
    return result;
}

static void quest9(ProchState *s)
{
    ProchState before;
    assert(proch_move(s, 15) == REPLY_LOCKED);
    assert(proch_move(s, 12) == REPLY_MOVED);
    assert(proch_move(s, 13) == REPLY_MOVED);
    /* Legal early pickup; no dependency on the last click. */
    assert(act(s, TAKE, TARGET_NONE, 12) == REPLY_TAKEN);
    assert(act(s, OPEN, DRAWER, 0) == REPLY_LOCKED);
    assert(act(s, USE, DRAWER, 12) == REPLY_DONE);
    assert(act(s, OPEN, DRAWER, 0) == REPLY_DONE);
    assert(act(s, TAKE, TARGET_NONE, 13) == REPLY_TAKEN);
    assert(act(s, LOOK, BIBLE, 0) == REPLY_BIBLE);
    assert(s->item_location[14] == 13); /* Bible need not be taken. */
    assert(proch_move(s, 12) == REPLY_MOVED);
    assert(proch_move(s, 11) == REPLY_MOVED);
    assert(act(s, TALK, ROOM_TOPIC, 0) == REPLY_FLOREK);
    assert(act(s, TALK, BIKE_TOPIC, 0) == REPLY_Q09);
    before = *s;
    act(s, TALK, BIKE_TOPIC, 0);
    assert(memcmp(s, &before, sizeof(*s)) == 0);
    assert(s->quest[8].status == 2 && s->quest[8].substep == 5);
    assert(s->hero[HERO_M].journal[0] == ((uint32_t)1 << 8));
    assert(s->hero[HERO_K].journal[0] == 0);
}

static void quest12(ProchState *s)
{
    ProchState before;
    assert(proch_move(s, 15) == REPLY_MOVED);
    act(s, TAKE, TARGET_NONE, 16); act(s, TAKE, TARGET_NONE, 17); act(s, TAKE, TARGET_NONE, 18);
    assert(proch_move(s, 11) == REPLY_MOVED);
    proch_move(s, 12); proch_move(s, 13);
    before = *s;
    assert(act(s, USE, BED, 0) == REPLY_NO_REST);
    assert(memcmp(s, &before, sizeof(*s)) == 0);
    act(s, LOOK, ROOM_DOOR, 0); act(s, LOOK, ROOM_WINDOW, 0);
    act(s, USE, ROOM_DOOR, 18); act(s, USE, ROOM_WINDOW, 17);
    assert(act(s, USE, BED, 0) == REPLY_NO_REST); /* thread is required too */
    act(s, USE, ROOM_WINDOW, 16);
    assert(act(s, USE, BED, 0) == REPLY_MORNING);
    assert(proch_can_take(s, 19));
    act(s, TAKE, TARGET_NONE, 19); /* early lace pickup still reconciles later */
    assert(s->quest[11].status != 2);
    assert(act(s, LOOK, ROOM_DOOR, 0) == REPLY_INTACT_DOOR);
    assert(act(s, LOOK, ROOM_WINDOW, 0) == REPLY_Q12);
    assert(s->quest[11].status == 2 && s->item_location[19] == OWNER_M);
    before = *s;
    act(s, USE, BED, 0); act(s, LOOK, ROOM_WINDOW, 0);
    assert(memcmp(s, &before, sizeof(*s)) == 0); /* no duplicate lace or entries */
    assert(s->hero[HERO_M].knowledge == 3);
    assert(s->hero[HERO_K].knowledge == 0);
}

static void quest21(ProchState *s)
{
    ProchState before;
    proch_switch(s);
    before = *s;
    assert(act(s, USE, DRAWER, 12) == REPLY_WRONG_HERO);
    assert(act(s, OPEN, CHEST, 0) == REPLY_PERMISSION);
    assert(memcmp(s, &before, sizeof(*s)) == 0);
    act(s, TALK, FISHER, 0); act(s, OPEN, CHEST, 0);
    act(s, TAKE, TARGET_NONE, 24); act(s, TAKE, TARGET_NONE, 25);
    act(s, USE, TABLE, 24); act(s, USE, TABLE, 25);
    before = *s;
    assert(act(s, USE, SEW, 0) == REPLY_NO_EFFECT);
    assert(memcmp(s, &before, sizeof(*s)) == 0);
    act(s, USE, SIMPLE_CUT, 0); act(s, USE, MARK_LENGTH, 0);
    assert(act(s, USE, SEW, 0) == REPLY_DRESS);
    assert(act(s, USE, PORTRAIT, 26) == REPLY_Q21);
    assert(s->disguise && s->item_location[26] == WORN_K && s->item_location[24] == CONSUMED);
    assert(s->item_location[25] == OWNER_K);
    assert(s->hero[HERO_K].journal[0] == ((uint32_t)1 << 20));
    assert(s->hero[HERO_M].journal[0] == (((uint32_t)1 << 8) | ((uint32_t)1 << 11)));
    before = *s;
    act(s, USE, SEW, 0); act(s, TAKE, TARGET_NONE, 24);
    assert(memcmp(s, &before, sizeof(*s)) == 0);
}

int main(void)
{
    ProchState s, before;
    proch_demo_init(&s);
    quest9(&s); quest12(&s); quest21(&s);
    s.switch_locked = 1; before = s;
    assert(proch_switch(&s) == REPLY_BLOCKED && memcmp(&s, &before, sizeof(s)) == 0);
    puts("PASS: Q09/Q12/Q21 demo rules, early pickup, isolation, switching, idempotence");
    return 0;
}
