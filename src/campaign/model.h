#ifndef PROCH_CAMPAIGN_MODEL_H
#define PROCH_CAMPAIGN_MODEL_H
#include <stdint.h>

enum { PR_HEROES=2, PR_M=0, PR_K=1, PR_SCENES=43, PR_ITEMS=45,
       PR_QUESTS=40, PR_FACTS=256, PR_JOURNAL=PR_FACTS+PR_QUESTS, PR_MESSAGES=8, PR_NPCS=34 };
enum PrPhase { PR_A,PR_B,PR_C,PR_D,PR_E,PR_F };
enum PrTruth { PR_UNKNOWN,PR_YES,PR_NO };
enum PrConfidence { PR_UNLEARNED,PR_SUSPECT,PR_HEARD,PR_KNOWN };
enum PrStatus { PR_INACTIVE,PR_ACTIVE,PR_DONE };
enum PrFuture { PR_UNSET,PR_RECONNECT,PR_SEPARATE };
enum PrEscape { PR_ESCAPE_UNKNOWN,PR_ESCAPE_EARLY,PR_ESCAPE_CONFRONTATION };
enum PrCrisis { PR_CRISIS_UNKNOWN,PR_CALM,PR_DESPAIR };
enum PrLock { PR_MODAL=1,PR_VISION=2,PR_SHADOW=4,PR_RESCUE=8,PR_TRANSITION=16 };
enum PrEnding { PR_NO_ENDING,PR_E01,PR_E02,PR_E03,PR_E04 };
enum PrFlag {
    PR_ADDRESS_LEFT,PR_KRYSTYNA_SAW_KINDNESS,PR_TRAIN_REPAIRED,PR_INTERCEPTED_LETTER,
    PR_TAVERN_TRUST,PR_POND_SEEN,PR_HONEST_KRYSTYNA,PR_DISGUISE,PR_SAFE_COURIER,
    PR_LETTER_SENT,PR_M_KNOWS_ALIVE,PR_RESCUE_RIG,PR_DIRECT_CONTACT,
    PR_CONSPIRACY_EVIDENCE,PR_KAROL_RUINED,PR_DOSSIER_READY,PR_M_FREE,
    PR_GRETA_HISTORY,PR_REMAINS_RECOVERED,PR_HAUNTING_RESOLVED,PR_FATHER_KNOWN,
    PR_MARIAN_ACCEPTED,PR_HELPED_KAROL,PR_FLAG_COUNT
};
enum PrPosition {
    PR_ABSENT=0,PR_INVENTORY_M=100,PR_INVENTORY_K=101,PR_WORN_M=102,PR_WORN_K=103,
    PR_CONSUMED=104,PR_COURIER=105,PR_FLOREK=106,PR_CONTAINER_BASE=256
};
enum PrFact {
    PR_FACT_TASK=1,PR_FACT_BROOCH,PR_FACT_ALIVE,PR_FACT_PHOTO_MEETING,
    PR_FACT_FALSE_DEATH_RUMOUR,PR_FACT_GRETA_NAME,PR_FACT_GRETA_IDENTITY,
    PR_FACT_GRETA_LEGEND,PR_FACT_GRETA_HISTORY,PR_FACT_POND_HAZARD,
    PR_FACT_FINANCIAL_PLOT,PR_FACT_KAROL_NOT_FATHER,PR_FACT_MARIAN_FATHER,
    PR_FACT_FUTURE_LETTER,PR_FACT_MESSAGE_WAITING,PR_FACT_MOTHER_PHOTO,
    PR_FACT_SERVANT_LUIZA,PR_FACT_SEROCZYN_DEPENDENCE,PR_FACT_MAIL_CONTROL,
    PR_FACT_TRAIN_VALVE,PR_FACT_TRAIN_ROUTE,PR_FACT_WORKER_STATEMENT,
    PR_FACT_UNBROKEN_MARKERS,PR_FACT_IRENA_ATTACK,PR_FACT_ADAM_HELP
};
enum PrMessageState { PR_MSG_UNUSED,PR_MSG_WAITING,PR_MSG_DELIVERED,PR_MSG_READ };
enum PrMessageRoute { PR_ROUTE_NEIGHBOUR_IZYDOR_FLOREK,PR_ROUTE_ROOM,PR_ROUTE_IZYDOR };
enum PrResult { PR_OK,PR_DENIED,PR_WAITING,PR_CONFIRMATION,PR_INVALID,PR_FULL };

typedef struct { uint8_t status,substep,hint_level;uint32_t actions; } PrQuest;
typedef struct {
    uint8_t location,last_safe_location,tab,inventory_scroll,map_scroll;
    uint32_t knowledge[PR_FACTS/32];
    uint8_t confidence[PR_FACTS];
    uint16_t journal[PR_JOURNAL];
    uint16_t journal_count;
} PrHero;
typedef struct {
    uint16_t item_position[PR_ITEMS+1];
    uint8_t item_state[PR_ITEMS+1],container_open[64];
    uint8_t scene_variant[PR_SCENES+1],npc_location[PR_NPCS+1];
    uint32_t travel_unlocks;
} PrWorld;
typedef struct {
    uint8_t item,sender,recipient,route,phase,state;
} PrMessage;
typedef struct {
    uint16_t schema_version,content_version;
    uint8_t phase,active,locks,crisis_substep;
    PrHero hero[PR_HEROES];
    PrWorld world;
    PrQuest quest[PR_QUESTS];
    uint32_t flags;
    uint8_t krystyna_alive,book_marriage,escape_variant,crisis_mode;
    uint8_t m_future,k_future,coast_legacy,klara_seen;
    uint8_t player_dead,ending,phase_confirmed[PR_HEROES];
    PrMessage messages[PR_MESSAGES];
} PrState;
typedef struct {
    PrState current,safe_snapshot,before_pond;
    uint8_t has_safe_snapshot,has_before_pond;
} PrGame;

void pr_new_game(PrGame *game);
int pr_flag(const PrState *state,enum PrFlag flag);
void pr_set_flag(PrState *state,enum PrFlag flag,int value);
int pr_done(const PrState *state,unsigned quest);
void pr_finish(PrState *state,unsigned quest,unsigned witnesses);
enum PrResult pr_learn(PrState *state,unsigned hero,unsigned fact,enum PrConfidence confidence,uint16_t entry);
int pr_knows(const PrState *state,unsigned hero,unsigned fact);
int pr_item_owner(const PrState *state,unsigned item);
enum PrResult pr_place_item(PrState *state,unsigned item,unsigned position);
int pr_has_item(const PrState *state,unsigned hero,unsigned item);
enum PrResult pr_switch_hero(PrState *state);
enum PrResult pr_advance_phase(PrState *state,int confirm);
enum PrResult pr_queue_message(PrState *state,unsigned item,unsigned sender,unsigned recipient,unsigned route,unsigned phase);
void pr_deliver_messages(PrState *state);
enum PrResult pr_read_message(PrState *state,unsigned item,unsigned hero);
enum PrEnding pr_ending(const PrState *state);
int pr_can_finish(const PrState *state);
void pr_snapshot(PrGame *game);
enum PrResult pr_undo(PrGame *game);

/* Map queries never grant plot access. Story movement is performed by rules. */
int pr_scene_allowed(const PrState *state,unsigned scene);
int pr_local_edge(unsigned from,unsigned to);
enum PrResult pr_move_local(PrState *state,unsigned scene);
#endif
