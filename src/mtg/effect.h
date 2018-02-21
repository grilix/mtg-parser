/* Effects are each change that is going to happen when
 * the ability resolves. It could be either the result or
 * the cost that must be paid.
 */

#ifndef EFFECT_H
#define EFFECT_H

enum MtgEffectType
{
  EFFECT_DESTROY,
  EFFECT_SACRIFICE,
  EFFECT_PAY_MANA,
  EFFECT_DRAW
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
mtg_effect_debug(struct MtgEffect *effect);

  extern void
mtg_effect_free(struct MtgEffect *effect);

#endif
