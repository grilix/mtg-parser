#include <stdlib.h>
#include <stdio.h>

#include "../common.h"
#include "rule.h"

  struct Rule *
rule_init(void)
{
  INIT_PTR(struct Rule, rule);

  rule->last_ability = NULL;
  rule->next = NULL;
  rule->prev = NULL;

  return rule;
}

  void
rule_add_ability(struct Rule *rule, struct Ability *last_ability)
{
  APPEND(rule->last_ability, last_ability);
}

  void
rule_debug(struct Rule *last_rule)
{
  if (last_rule->prev != NULL) {
    rule_debug(last_rule->prev);
    printf(",");
  }

  printf("Rule(");

  if (last_rule->last_ability == NULL)
    printf("<no ability>");
  else
    ability_debug(last_rule->last_ability);

  printf(")");
}

  void
rule_free(struct Rule *last_rule)
{
  if (last_rule->prev != NULL)
    rule_free(last_rule->prev);

  if (last_rule->last_ability != NULL)
    ability_free(last_rule->last_ability);

  free(last_rule);
}