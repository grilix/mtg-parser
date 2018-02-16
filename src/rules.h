#ifndef RULES_H
#define RULES_H

#include "ability.h"

struct st_rule
{
  char *text;
  struct st_ability *ability_list;
  struct st_rule *next;
  struct st_rule *prev;
};

  struct st_rule *
init_rule(void);

  struct st_rule *
start_new_rule(struct st_rule *rule);

  void
add_rule_ability(struct st_rule *rule, struct st_ability *ability);

  void
debug_rules(struct st_rule *rule);

  void
free_rules(struct st_rule *rule);

#endif
