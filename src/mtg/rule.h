#ifndef RULES_H
#define RULES_H

#include "ability.h"

struct MtgRule
{
  struct MtgAbility *last_ability;

  struct MtgRule *prev;
  struct MtgRule *next;
};

  extern struct MtgRule *
mtg_rule_init(void);

  extern void
mtg_add_rule_ability(struct MtgRule *rule, struct MtgAbility *last_ability);

  extern void
mtg_rule_debug(struct MtgRule *last_rule);

  extern void
mtg_rule_free(struct MtgRule *last_rule);

#endif
