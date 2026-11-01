#ifndef PROCH_ENGINE_H
#define PROCH_ENGINE_H
#include <stdint.h>

enum { HERO_M, HERO_K, HERO_COUNT, ITEM_COUNT = 45, QUEST_COUNT = 40 };
enum { OWNER_M = 100, OWNER_K, WORN_K, CONSUMED };
enum ProchVerb { LOOK, OPEN, CLOSE, USE, TALK, GO, HIT, EAT, TAKE };
enum ProchTarget {
    TARGET_NONE, FLOREK, ROOM_TOPIC, BIKE_TOPIC, DESK, DRAWER, BIBLE,
    ROOM_DOOR, ROOM_WINDOW, BED, FISHER, CHEST, TABLE, SIMPLE_CUT,
    MARK_LENGTH, SEW, PORTRAIT
};
enum ProchReply {
    REPLY_NO_EFFECT, REPLY_DONE, REPLY_WRONG_HERO, REPLY_LOCKED,
    REPLY_PERMISSION, REPLY_FLOREK, REPLY_BIKE, REPLY_BIBLE,
    REPLY_DOOR, REPLY_WINDOW, REPLY_NO_REST, REPLY_MORNING,
    REPLY_INTACT_DOOR, REPLY_INTACT_WINDOW, REPLY_LACE,
    REPLY_FISHER, REPLY_CUT, REPLY_LENGTH, REPLY_DRESS, REPLY_WORN,
    REPLY_Q09, REPLY_Q12, REPLY_Q21, REPLY_SWITCHED, REPLY_BLOCKED,
    REPLY_MOVED, REPLY_TAKEN, REPLY_ALREADY, REPLY_VIOLENCE, REPLY_INEDIBLE
};
typedef struct { uint8_t status, substep, hint_level; } ProchQuest;
typedef struct {
    uint8_t location, last_safe_location, tab;
    uint32_t knowledge, journal[2];
} ProchHero;
typedef struct {
    uint16_t schema_version, content_version;
    uint8_t active, phase, demo_fixture, switch_locked;
    ProchHero hero[HERO_COUNT];
    uint8_t item_location[ITEM_COUNT + 1];
    ProchQuest quest[QUEST_COUNT];
    uint16_t q09_bits, q12_bits;
    uint8_t drawer_unlocked, drawer_open, chest_open, fisher_permission;
    uint8_t cloth_on_table, needle_on_table, cut, measured, disguise;
} ProchState;

/* Stage-2 fixture only: Q09/Q12 in B, independent L33/Q21 fragment for K.
 * This is not the production A..F campaign initializer. */
void proch_demo_init(ProchState *state);
enum ProchReply proch_switch(ProchState *state);
enum ProchReply proch_move(ProchState *state, uint8_t scene);
enum ProchReply proch_action(ProchState *state, enum ProchVerb verb,
                            enum ProchTarget target, uint8_t item);
uint8_t proch_can_take(const ProchState *state, uint8_t item);
uint8_t proch_has(const ProchState *state, uint8_t item);
#endif
