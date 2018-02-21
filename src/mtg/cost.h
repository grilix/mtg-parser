#ifndef COST_H
#define COST_H

#include "cost.h"

enum CostType
{
  COST_SACRIFICE,
  COST_DISCARD,
  COST_MANA
};

struct Cost
{
  enum CostType type;
  struct Recipient *recipient;
  char color;

  struct Cost *prev;
  struct Cost *next;
};

  struct Cost *
cost_create_sacrifice(struct Recipient *recipient);

  struct Cost *
cost_create_mana(char color);

  struct Cost *
cost_create_discard(struct Recipient *recipient);

  void
cost_debug(struct Cost *cost);

  void
cost_free(struct Cost *cost);

#endif
