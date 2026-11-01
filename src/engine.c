#include "engine.h"
#include <string.h>

enum { TALKED = 1, BIBLE_SEEN = 2, BIKE_ASKED = 4 };
enum { DOOR_SEEN = 1, WINDOW_SEEN = 2, DOOR_SEALED = 4, WINDOW_WAX = 8,
       WINDOW_THREAD = 16, RESTED = 32, DOOR_CHECKED = 64, WINDOW_CHECKED = 128 };

static void complete(ProchState *s, unsigned quest, unsigned hero)
{
    s->quest[quest - 1].status = 2;
    s->hero[hero].journal[(quest - 1) / 32] |= (uint32_t)1 << ((quest - 1) % 32);
    if (quest == 9) s->hero[hero].knowledge |= 1;
    if (quest == 12) s->hero[hero].knowledge |= 2;
    if (quest == 21) s->hero[hero].knowledge |= 1;
}

static enum ProchReply reconcile(ProchState *s, enum ProchReply reply)
{
    /* State predicates, not just last-click predicates: early pickups are legal. */
    if (s->active == HERO_M) {
        ProchQuest *q = &s->quest[8];
        if (q->status != 2) {
            q->substep = !(s->q09_bits & TALKED) ? 0 :
                !s->drawer_unlocked ? 1 : !s->drawer_open ? 2 :
                (s->item_location[13] != OWNER_M || !(s->q09_bits & BIBLE_SEEN)) ? 3 : 4;
            q->status = 1;
            if ((s->q09_bits & (TALKED | BIBLE_SEEN | BIKE_ASKED)) == 7 &&
                s->item_location[13] == OWNER_M) {
                q->substep = 5; complete(s, 9, HERO_M); reply = REPLY_Q09;
            }
        }
        q = &s->quest[11];
        if (s->quest[8].status == 2 && q->status != 2) {
            q->status = 1;
            q->substep = !(s->q12_bits & DOOR_SEALED) ? 0 :
                (s->q12_bits & (WINDOW_WAX | WINDOW_THREAD)) != (WINDOW_WAX | WINDOW_THREAD) ? 2 :
                !(s->q12_bits & RESTED) ? 3 : 4;
            if ((s->q12_bits & (RESTED | DOOR_CHECKED | WINDOW_CHECKED)) ==
                (RESTED | DOOR_CHECKED | WINDOW_CHECKED) && s->item_location[19] == OWNER_M) {
                q->substep = 5; complete(s, 12, HERO_M); reply = REPLY_Q12;
            }
        }
    } else if (s->disguise && s->quest[20].status != 2) {
        s->quest[20].substep = 4; complete(s, 21, HERO_K); reply = REPLY_Q21;
    }
    return reply;
}

void proch_demo_init(ProchState *s)
{
    memset(s, 0, sizeof(*s));
    s->schema_version = s->content_version = 1;
    s->phase = 'B'; s->demo_fixture = 1;
    s->hero[HERO_M].location = s->hero[HERO_M].last_safe_location = 11;
    s->hero[HERO_K].location = s->hero[HERO_K].last_safe_location = 33;
    s->item_location[12] = s->item_location[13] = s->item_location[14] = 13;
    s->item_location[16] = s->item_location[17] = s->item_location[18] = 15;
    s->item_location[24] = s->item_location[25] = 33;
}

uint8_t proch_has(const ProchState *s, uint8_t item)
{
    return item > 0 && item <= ITEM_COUNT && s->active < HERO_COUNT &&
           s->item_location[item] == OWNER_M + s->active;
}

enum ProchReply proch_switch(ProchState *s)
{
    if (s->switch_locked) return REPLY_BLOCKED;
    s->active = s->active == HERO_M ? HERO_K : HERO_M;
    return REPLY_SWITCHED;
}

enum ProchReply proch_move(ProchState *s, uint8_t scene)
{
    static const uint8_t edges[][2] = {{11,12},{12,13},{11,14},{11,15},{14,15}};
    unsigned i;
    uint8_t current = s->hero[s->active].location;
    if (s->switch_locked || s->active != HERO_M) return REPLY_BLOCKED;
    if ((scene == 14 || scene == 15) && s->quest[8].status != 2) return REPLY_LOCKED;
    for (i = 0; i < sizeof(edges)/sizeof(edges[0]); ++i)
        if ((edges[i][0] == current && edges[i][1] == scene) ||
            (edges[i][1] == current && edges[i][0] == scene)) {
            s->hero[s->active].location = scene;
            s->hero[s->active].last_safe_location = scene;
            return REPLY_MOVED;
        }
    return REPLY_BLOCKED;
}

uint8_t proch_can_take(const ProchState *s, uint8_t item)
{
    uint8_t loc;
    if (item == 0 || item > ITEM_COUNT || s->active >= HERO_COUNT) return 0;
    loc = s->hero[s->active].location;
    if (s->item_location[item] != loc) return 0;
    if (s->active == HERO_M) {
        if (item == 12 && loc == 13) return 1;
        if ((item == 13 || item == 14) && loc == 13) return s->drawer_open;
        if (item >= 16 && item <= 18 && loc == 15) return s->quest[8].status == 2;
        if (item == 19 && loc == 13) return (s->q12_bits & RESTED) != 0;
    } else if ((item == 24 || item == 25) && loc == 33)
        return s->chest_open && s->fisher_permission;
    return 0;
}

enum ProchReply proch_action(ProchState *s, enum ProchVerb verb,
                            enum ProchTarget target, uint8_t item)
{
    enum ProchReply reply = REPLY_NO_EFFECT;
    uint8_t loc = s->hero[s->active].location;
    if (verb == TAKE) {
        if (!proch_can_take(s, item)) return REPLY_PERMISSION;
        s->item_location[item] = OWNER_M + s->active;
        reply = item == 19 ? REPLY_LACE : REPLY_TAKEN;
    } else if (verb == USE && item != 0 && !proch_has(s, item)) return REPLY_WRONG_HERO;
    else if (s->active == HERO_M) {
        if (loc == 11 && verb == TALK && target == ROOM_TOPIC) {
            s->q09_bits |= TALKED; reply = REPLY_FLOREK;
        } else if (loc == 11 && verb == TALK && target == BIKE_TOPIC) {
            if (!(s->q09_bits & TALKED)) return REPLY_PERMISSION;
            s->q09_bits |= BIKE_ASKED; reply = REPLY_BIKE;
        } else if (loc == 13) {
            if (verb == USE && item == 12 && target == DRAWER) {
                s->drawer_unlocked = 1; reply = REPLY_DONE;
            } else if (verb == OPEN && target == DRAWER) {
                if (!s->drawer_unlocked) return REPLY_LOCKED;
                s->drawer_open = 1; reply = REPLY_DONE;
            } else if (verb == CLOSE && target == DRAWER) {
                s->drawer_open = 0; reply = REPLY_DONE;
            } else if (verb == LOOK && target == BIBLE) {
                if (!s->drawer_open && !proch_has(s, 14)) return REPLY_LOCKED;
                s->q09_bits |= BIBLE_SEEN; reply = REPLY_BIBLE;
            } else if (verb == LOOK && target == ROOM_DOOR) {
                s->q12_bits |= DOOR_SEEN;
                if (s->q12_bits & RESTED) s->q12_bits |= DOOR_CHECKED;
                reply = (s->q12_bits & RESTED) ? REPLY_INTACT_DOOR : REPLY_DOOR;
            } else if (verb == LOOK && target == ROOM_WINDOW) {
                s->q12_bits |= WINDOW_SEEN;
                if (s->q12_bits & RESTED) s->q12_bits |= WINDOW_CHECKED;
                reply = (s->q12_bits & RESTED) ? REPLY_INTACT_WINDOW : REPLY_WINDOW;
            } else if (verb == USE && target == ROOM_DOOR && item == 18) {
                if (!(s->q12_bits & DOOR_SEEN)) return REPLY_PERMISSION;
                s->q12_bits |= DOOR_SEALED; s->item_location[18] = 13; reply = REPLY_DONE;
            } else if (verb == USE && target == ROOM_WINDOW && (item == 16 || item == 17)) {
                if (!(s->q12_bits & WINDOW_SEEN)) return REPLY_PERMISSION;
                s->q12_bits |= item == 16 ? WINDOW_THREAD : WINDOW_WAX;
                s->item_location[item] = 13; reply = REPLY_DONE;
            } else if (verb == USE && target == BED) {
                if ((s->q12_bits & (DOOR_SEALED | WINDOW_WAX | WINDOW_THREAD)) !=
                    (DOOR_SEALED | WINDOW_WAX | WINDOW_THREAD)) return REPLY_NO_REST;
                s->q12_bits |= RESTED;
                if (s->item_location[19] == 0) s->item_location[19] = 13;
                reply = REPLY_MORNING;
            }
        }
    } else if (loc == 33) {
        if (verb == TALK && target == FISHER) {
            s->fisher_permission = 1;
            if (s->quest[20].status == 0) s->quest[20].status = 1;
            reply = REPLY_FISHER;
        } else if (verb == OPEN && target == CHEST) {
            if (!s->fisher_permission) return REPLY_PERMISSION;
            s->chest_open = 1; reply = REPLY_DONE;
        } else if (verb == CLOSE && target == CHEST) {
            s->chest_open = 0; reply = REPLY_DONE;
        } else if (verb == USE && target == TABLE && item == 24) {
            s->cloth_on_table = 1; reply = REPLY_DONE;
        } else if (verb == USE && target == TABLE && item == 25) {
            s->needle_on_table = 1; reply = REPLY_DONE;
        } else if (verb == USE && target == SIMPLE_CUT && s->cloth_on_table && s->needle_on_table) {
            s->cut = 1; reply = REPLY_CUT;
        } else if (verb == USE && target == MARK_LENGTH && s->cut) {
            s->measured = 1; reply = REPLY_LENGTH;
        } else if (verb == USE && target == SEW && s->measured) {
            if (!proch_has(s, 24) || !proch_has(s, 25)) return REPLY_PERMISSION;
            s->item_location[24] = CONSUMED; s->item_location[26] = OWNER_K;
            s->cloth_on_table = s->needle_on_table = 0;
            reply = REPLY_DRESS;
        } else if (verb == USE && target == PORTRAIT && item == 26) {
            s->item_location[26] = WORN_K; s->disguise = 1; reply = REPLY_WORN;
        }
    }
    /* Unrelated, invalid actions are exact no-ops, including quest bookkeeping. */
    return reply == REPLY_NO_EFFECT ? reply : reconcile(s, reply);
}
