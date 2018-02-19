#ifndef COST_H
#define COST_H

#include "cost.h"

enum CostType
{
  COST_SACRIFICE
};

struct Cost
{
  enum CostType type;
  struct Objective *objective;
};

  struct Cost *
cost_create_sacrifice(struct Objective *objective);

  void
cost_debug(struct Cost *cost);

#endif
