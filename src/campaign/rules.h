#ifndef PROCH_CAMPAIGN_RULES_H
#define PROCH_CAMPAIGN_RULES_H
#include "model.h"

/* Stable semantic targets. Pixel rectangles belong to the platform UI. */
#define PR_HOTSPOT(scene,index) ((scene)*8u+(index)-1u)
#define PR_ITEM(item) (1024u+(item))
#define PR_CHOICE(quest,index) (4096u+(quest)*16u+(index))
enum PrProp {
    PR_VALVE=8192,PR_COMPRESSOR_BODY,PR_FACTORY_GATE,PR_TAVERN_APPROACH,
    PR_OPENED_ENVELOPE,PR_DEPARTURE,PR_LETTER_DESK,PR_DRAWER,PR_ROOM_DOOR,
    PR_PIER_LIGHTS,PR_PIER_WALK,PR_LUDWIK,PR_CHRONICLE_PAGE,
    PR_CHRONICLE_MARGIN,PR_OLD_ARMS
};
enum PrVerb {
    PR_LOOK,PR_OPEN,PR_CLOSE,PR_USE,PR_TALK,PR_GO,PR_HIT,PR_EAT,PR_TAKE,
    PR_CHOOSE,PR_SWITCH
};
enum PrPresentation { PR_LOG,PR_DIALOG,PR_CONTAINER,PR_DOCUMENT,PR_CUTSCENE };
typedef struct { uint8_t verb;uint16_t source,target; } PrAction;
typedef struct { uint16_t id,text; } PrTopic;
typedef struct { uint8_t result,presentation;uint16_t text,target; } PrFeedback;

/* Queries have no side effects. CHOOSE requires a currently available topic
 * from the indicated conversation target; a stale/foreign choice is rejected. */
unsigned pr_topics(const PrState *s,unsigned target,PrTopic *out,unsigned capacity);
int pr_target_here(const PrState *s,unsigned target);
int pr_container_is_open(const PrState *s,unsigned target);
PrFeedback pr_act(PrGame *game,PrAction action);
#endif
