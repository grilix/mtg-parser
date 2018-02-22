#include "../common.h"
#include "card.h"

  extern struct MtgCard *
mtg_card_init(void)
{
  INIT_PTR(struct MtgCard, card);

  card->last_rule = 0;

  return card;
}

  extern void
mtg_card_add_rule(struct MtgCard *card, struct MtgRule *rule)
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

  extern void
mtg_card_add_ability_set(struct MtgCard *card, struct MtgAbility *last_ability)
{
  mtg_card_add_rule(card, mtg_rule_init());
  card->last_rule->last_ability = last_ability;
}

  extern void
mtg_card_free(struct MtgCard *card)
{
  if (card->last_rule != NULL)
    mtg_rule_free(card->last_rule);

  free(card);
}
