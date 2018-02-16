#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "rules.h"

  struct st_rule *
init_rule(void)
{
  INIT_PTR(struct st_rule, rule);

  rule->ability_list = NULL;
  rule->next = NULL;
  rule->prev = NULL;
  rule->text = NULL;

  return rule;
}

  struct st_rule *
start_new_rule(struct st_rule *rule)
{
  START("start_new_rule");

  struct st_rule *n_rule = &(struct st_rule) {};

  if (!rule->text)
  {
    rule->text = "first";
  }

  n_rule->prev = rule;
  rule->next = n_rule;

  return n_rule;
}

  void
add_rule_ability(struct st_rule *rule, struct st_ability *ability)
{
  if (rule->ability_list)
  {
    rule->ability_list->next = ability;
    ability->prev = rule->ability_list;
  }

  rule->ability_list = ability;
}

  void
debug_rules(struct st_rule *rule)
{
  if (rule->prev != NULL)
    debug_rules(rule->prev);

  printf("Rule(");

  if (rule->ability_list == NULL)
    printf("<no ability>");
  else
    debug_ability(rule->ability_list);

  printf(")");
}

  void
free_rules(struct st_rule *rule)
{
  if (rule->prev != NULL)
    free_rules(rule->prev);

  if (rule->ability_list != NULL)
    free_abilities(rule->ability_list);

  if (rule->text != NULL)
    free(rule->text);

  free(rule);
}
