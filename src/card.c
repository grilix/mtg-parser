#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "card.h"
#include "rules.h"

  struct Card *
card_init(void)
{
  INIT_PTR(struct Card, card);

  card->last_rule = 0;

  return card;
}

  void
card_add_rule(struct Card *card, struct Rule *rule)
{
  if (card->last_rule != NULL)
  {
    card->last_rule->next = rule;
    rule->prev = card->last_rule;
  }
  else
    rule->prev = NULL;

  card->last_rule = rule;
}

  void
card_add_ability_set(struct Card *card, struct Ability *last_ability)
{
  card_add_rule(card, rule_init());
  card->last_rule->last_ability = last_ability;
}

  void
card_debug(struct Card *card)
{
  printf("Card(");

  if (card->last_rule == NULL)
    printf("<no rules>");
  else
    rule_debug(card->last_rule);

  printf(")");
}

  void
card_free(struct Card *card)
{
  if (card->last_rule != NULL)
    rule_free(card->last_rule);

  free(card);
}
