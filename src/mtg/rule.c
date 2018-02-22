#include "../common.h"
#include "rule.h"

  extern struct MtgRule *
mtg_rule_init(void)
{
  INIT_PTR(struct MtgRule, rule);

  rule->last_ability = NULL;
  rule->next = NULL;
  rule->prev = NULL;

  return rule;
}

  extern void
mtg_rule_add_ability(struct MtgRule *rule, struct MtgAbility *last_ability)
{
  APPEND(rule->last_ability, last_ability);
}

  extern void
mtg_rule_free(struct MtgRule *last_rule)
{
  if (last_rule->prev != NULL)
    mtg_rule_free(last_rule->prev);

  if (last_rule->last_ability != NULL)
    mtg_ability_free(last_rule->last_ability);

  free(last_rule);
}
