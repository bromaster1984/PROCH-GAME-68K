#ifndef PROCH_CAMPAIGN_RULES_INTERNAL_H
#define PROCH_CAMPAIGN_RULES_INTERNAL_H
#include "rules.h"
#include "campaign_data.h"

#define PR_BIT(n) ((uint32_t)1<<(n))
int pr_action_done(const PrState *s,unsigned quest,unsigned bit);
void pr_mark_action(PrState *s,unsigned quest,unsigned bit);
void pr_story_move(PrState *s,unsigned scene);
PrFeedback pr_reply(unsigned result,unsigned text,unsigned presentation,unsigned target);
PrFeedback pr_rules_a(PrState *s,PrAction a);
unsigned pr_topics_a(const PrState *s,unsigned target,PrTopic *out,unsigned capacity);
void pr_refresh_a(PrState *s);
PrFeedback pr_rules_b(PrState *s,PrAction a);
unsigned pr_topics_b(const PrState *s,unsigned target,PrTopic *out,unsigned capacity);
void pr_refresh_b(PrState *s);
PrFeedback pr_rules_c(PrState *s,PrAction a);
unsigned pr_topics_c(const PrState *s,unsigned target,PrTopic *out,unsigned capacity);
void pr_refresh_c(PrState *s);
#endif
