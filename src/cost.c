#include <stdio.h>
#include <string.h>

#include "common.h"
#include "cost.h"
#include "objective.h"

  struct Cost *
cost_create_sacrifice(struct Objective *objective)
{
  INIT_PTR(struct Cost, cost);

  cost->objective = objective;
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

  if (cost->objective != NULL)
    objective_debug(cost->objective);

  printf(")");
}
