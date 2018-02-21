#include <stdio.h>
#include <string.h>

#include "../common.h"
#include "cost.h"
#include "recipient.h"

  struct Cost *
cost_create_sacrifice(struct Recipient *recipient)
{
  INIT_PTR(struct Cost, cost);

  cost->recipient = recipient;
  cost->type = COST_SACRIFICE;

  return cost;
}

  static void
_debug_type(enum CostType type)
{
  switch (type)
  {
  case COST_SACRIFICE:
    printf("sacrifice:");
    break;
  }
}

  void
cost_debug(struct Cost *cost)
{
  printf("Cost(");

  _debug_type(cost->type);

  if (cost->recipient != NULL)
    recipient_debug(cost->recipient);

  printf(")");
}

  void
cost_free(struct Cost *cost)
{
  switch (cost->type)
  {
    case COST_SACRIFICE:
      if (cost->recipient != NULL)
        recipient_free(cost->recipient);
      break;
  }
}
