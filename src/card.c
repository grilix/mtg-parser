#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "card.h"
#include "rules.h"

  struct st_card *
init_card(void)
{
  INIT_PTR(struct st_card, card);

  card->rule_list = 0;

  return card;
}

  void
add_card_rule(struct st_card *card, struct st_rule *rule)
{
  if (card->rule_list != NULL)
  {
    card->rule_list->next = rule;
    rule->prev = card->rule_list;
  }
  else
    rule->prev = NULL;

  card->rule_list = rule;
}

  void
add_card_empty_rule(struct st_card *card)
{
  add_card_rule(card, init_rule());
}

  void
debug_card(struct st_card *card)
{
  printf("Card(");

  if (card->rule_list == NULL)
    printf("<no rules>");
  else
    debug_rules(card->rule_list);

  printf(")");
}

  void
free_card(struct st_card *card)
{
  if (card->rule_list != NULL)
    free_rules(card->rule_list);

  free(card);
}
