#ifndef COST_H
#define COST_H

#include "types.h"
#include "cost.h"

enum MtgCostType
{
  COST_SACRIFICE,
  COST_DISCARD,
  COST_MANA
};

struct MtgCost
{
  enum MtgCostType type;
  struct MtgRecipient *recipient;
  enum MtgColor color;

  struct MtgCost *prev;
  struct MtgCost *next;
};

  extern struct MtgCost *
mtg_cost_create_sacrifice(struct MtgRecipient *recipient);

  extern struct MtgCost *
mtg_cost_create_mana(enum MtgColor color);

  extern struct MtgCost *
mtg_cost_create_discard(struct MtgRecipient *recipient);

  extern void
mtg_cost_debug(struct MtgCost *cost);

  extern void
mtg_cost_free(struct MtgCost *cost);

#endif
