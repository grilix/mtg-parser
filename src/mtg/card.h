#ifndef CARD_H
#define CARD_H

#include "rule.h"

struct Card
{
  struct Rule *last_rule;
};

  struct Card *
card_init(void);

/* Add a list of abilities as a new rule.
 */
  void
card_add_ability_set(struct Card *card, struct Ability *last_ability);

  void
card_add_rule(struct Card *card, struct Rule *last_rule);

  void
card_debug(struct Card *card);

  void
card_free(struct Card *card);

#endif
