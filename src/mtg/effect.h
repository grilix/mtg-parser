/* Effects are each change that is going to happen when
 * the ability resolves. It could be either the result or
 * the cost that must be paid.
 */

#ifndef EFFECT_H
#define EFFECT_H

enum EffectType
{
  EFFECT_DESTROY,
  EFFECT_SACRIFICE,
  EFFECT_PAY_MANA,
  EFFECT_DRAW
};

struct Effect
{
  struct Recipient *recipient;
  int count;

  enum EffectType type;
};

  struct Effect *
effect_create_destroy(struct Recipient *recipient);

  struct Effect *
effect_create_draw(int count);

  struct Effect *
effect_create_sacrifice(struct Recipient *recipient);

  void
effect_debug(struct Effect *effect);

  void
effect_free(struct Effect *effect);

#endif
