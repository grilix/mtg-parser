#ifndef COST_H
#define COST_H

#include "types.h"
#include "mana.h"

enum MtgCostType
{
  MTG_COST_SACRIFICE,
  MTG_COST_DISCARD,
  MTG_COST_MANA,
  MTG_COST_TAP
};

struct MtgCost
{
  enum MtgCostType type;
  struct MtgRecipient *recipient;
  struct MtgMana *mana;

  struct MtgCost *prev;
  struct MtgCost *next;
};

  extern struct MtgCost *
mtg_cost_create_sacrifice(struct MtgRecipient *recipient);

  extern struct MtgCost *
mtg_cost_create_mana(struct MtgMana *mana);

  extern struct MtgCost *
mtg_cost_create_discard(struct MtgRecipient *recipient);

  extern struct MtgCost *
mtg_cost_create_tap(void);

  extern void
mtg_cost_debug(struct MtgCost *cost);

  extern void
mtg_cost_free(struct MtgCost *cost);

#endif
