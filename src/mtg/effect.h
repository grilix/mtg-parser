/* Effects are each change that is going to happen when
 * the ability resolves. It could be either the result or
 * the cost that must be paid.
 */

#ifndef EFFECT_H
#define EFFECT_H

#include "recipient.h"

enum MtgEffectType
{
  MTG_EFFECT_DESTROY,
  MTG_EFFECT_SACRIFICE,
  MTG_EFFECT_PAY_MANA,
  MTG_EFFECT_DRAW
};

struct MtgEffect
{
  struct MtgRecipient *recipient;
  int count;

  enum MtgEffectType type;
};

  extern struct MtgEffect *
mtg_effect_create_destroy(struct MtgRecipient *recipient);

  extern struct MtgEffect *
mtg_effect_create_draw(int count);

  extern struct MtgEffect *
mtg_effect_create_sacrifice(struct MtgRecipient *recipient);

  extern void
mtg_effect_free(struct MtgEffect *effect);

#endif
