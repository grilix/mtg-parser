#include <stdio.h>
#include <string.h>

#include "../common.h"
#include "cost.h"
#include "recipient.h"

  static struct Cost *
init_cost()
{
  INIT_PTR(struct Cost, cost);

  cost->recipient = NULL;
  cost->prev = NULL;
  cost->next = NULL;

  return cost;
}

  struct Cost *
cost_create_sacrifice(struct Recipient *recipient)
{
  struct Cost *cost = init_cost();

  cost->recipient = recipient;
  cost->type = COST_SACRIFICE;

  return cost;
}

  struct Cost *
cost_create_discard(struct Recipient *recipient)
{
  struct Cost *cost = init_cost();

  cost->recipient = recipient;
  cost->type = COST_DISCARD;

  return cost;
}

  struct Cost *
cost_create_mana(char color)
{
  struct Cost *cost = init_cost();
  cost->type = COST_MANA;
  cost->color = color;
  return cost;
}

  static void
_debug_type(struct Cost *cost)
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

  void
cost_debug(struct Cost *cost)
{
  if (cost->prev != NULL)
  {
    cost_debug(cost->prev);
    printf(",");
  }

  printf("Cost(");

  _debug_type(cost);

  if (cost->recipient != NULL)
    recipient_debug(cost->recipient);

  printf(")");
}

  void
cost_free(struct Cost *cost)
{
  if (cost->prev != NULL)
    cost_free(cost->prev);

  switch (cost->type)
  {
    case COST_SACRIFICE:
      if (cost->recipient != NULL)
        recipient_free(cost->recipient);
      break;
  }
}
