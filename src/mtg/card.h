#ifndef CARD_H
#define CARD_H

#include "rule.h"

struct MtgCard
{
  struct MtgRule *last_rule;
};

  extern struct MtgCard *
mtg_card_init(void);

/* Add a list of abilities as a new rule.
 */
  extern void
mtg_card_add_ability_set(struct MtgCard *card, struct MtgAbility *last_ability);

  extern void
mtg_card_add_rule(struct MtgCard *card, struct MtgRule *last_rule);

  extern void
mtg_card_debug(struct MtgCard *card);

  extern void
mtg_card_free(struct MtgCard *card);

#endif
