#include <stdio.h>
#include <string.h>

#include "../common.h"
#include "cost.h"
#include "recipient.h"

  static struct MtgCost *
init_cost()
{
  INIT_PTR(struct MtgCost, cost);

  cost->recipient = NULL;
  cost->prev = NULL;
  cost->next = NULL;

  return cost;
}

  extern struct MtgCost *
mtg_cost_create_sacrifice(struct MtgRecipient *recipient)
{
  struct MtgCost *cost = init_cost();

  cost->recipient = recipient;
  cost->type = COST_SACRIFICE;

  return cost;
}

  extern struct MtgCost *
mtg_cost_create_discard(struct MtgRecipient *recipient)
{
  struct MtgCost *cost = init_cost();

  cost->recipient = recipient;
  cost->type = COST_DISCARD;

  return cost;
}

  extern struct MtgCost *
mtg_cost_create_mana(enum MtgColor color)
{
  struct MtgCost *cost = init_cost();
  cost->type = COST_MANA;
  cost->color = color;
  return cost;
}

  static void
_debug_type(struct MtgCost *cost)
{
  switch (cost->type)
  {
  case COST_SACRIFICE:
    printf("sacrifice:");
    break;
  case COST_MANA:
    printf("%c", cost->color);
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

  switch (cost->type)
  {
    case COST_SACRIFICE:
      if (cost->recipient != NULL)
        mtg_recipient_free(cost->recipient);
      break;
  }
}
