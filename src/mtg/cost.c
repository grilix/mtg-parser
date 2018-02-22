#include <stdio.h>
#include <string.h>

#include "../common.h"
#include "cost.h"
#include "recipient.h"
#include "mana.h"

  static struct MtgCost *
init_cost()
{
  INIT_PTR(struct MtgCost, cost);

  cost->recipient = NULL;
  cost->prev = NULL;
  cost->next = NULL;
  cost->mana = NULL;

  return cost;
}

  extern struct MtgCost *
mtg_cost_create_sacrifice(struct MtgRecipient *recipient)
{
  struct MtgCost *cost = init_cost();

  cost->recipient = recipient;
  cost->type = MTG_COST_SACRIFICE;

  return cost;
}

  extern struct MtgCost *
mtg_cost_create_discard(struct MtgRecipient *recipient)
{
  struct MtgCost *cost = init_cost();

  cost->recipient = recipient;
  cost->type = MTG_COST_DISCARD;

  return cost;
}

  extern struct MtgCost *
mtg_cost_create_mana(struct MtgMana *mana)
{
  struct MtgCost *cost = init_cost();
  cost->type = MTG_COST_MANA;
  cost->mana = mana;
  return cost;
}

  extern struct MtgCost *
mtg_cost_create_tap(void)
{
  struct MtgCost *cost = init_cost();

  cost->type = MTG_COST_TAP;
  cost->recipient = mtg_recipient_create(MTG_RECIPIENT_SELF, "{T}");

  return cost;
}

  static void
_debug_type(struct MtgCost *cost)
{
  switch (cost->type)
  {
  case MTG_COST_SACRIFICE:
    printf("sacrifice:");
    break;
  case MTG_COST_TAP:
    printf("tap");
    break;
  case MTG_COST_MANA:
    mtg_mana_debug(cost->mana);
    break;
  }
}

  extern void
mtg_cost_debug(struct MtgCost *cost)
{
  if (cost->prev != NULL)
  {
    mtg_cost_debug(cost->prev);
    printf(",");
  }

  printf("Cost(");

  _debug_type(cost);

  if (cost->recipient != NULL)
    mtg_recipient_debug(cost->recipient);

  printf(")");
}

  extern void
mtg_cost_free(struct MtgCost *cost)
{
  if (cost->prev != NULL)
    mtg_cost_free(cost->prev);

  if (cost->mana != NULL)
    mtg_mana_free(cost->mana);

  switch (cost->type)
  {
    case MTG_COST_SACRIFICE:
      if (cost->recipient != NULL)
        mtg_recipient_free(cost->recipient);
      break;
  }
}
