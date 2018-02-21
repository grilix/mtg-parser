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
  struct Recipient *recipient;
};

  struct Cost *
cost_create_sacrifice(struct Recipient *recipient);

  void
cost_debug(struct Cost *cost);

  void
cost_free(struct Cost *cost);

#endif
