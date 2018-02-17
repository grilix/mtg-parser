#ifndef RULES_H
#define RULES_H

#include "ability.h"

struct Rule
{
  char *text;
  struct Ability *last_ability;
  struct Rule *next;
  struct Rule *prev;
};

  struct Rule *
rule_init(void);

  void
add_rule_ability(struct Rule *rule, struct Ability *last_ability);

  void
rule_debug(struct Rule *last_rule);

  void
rule_free(struct Rule *last_rule);

#endif
