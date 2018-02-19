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
  EFFECT_PAY_MANA
};

struct Effect
{
  struct Objective *objective;

  enum EffectType type;
};

  struct Effect *
effect_create_destroy(struct Objective *objective);

  struct Effect *
effect_create_sacrifice(struct Objective *objective);

  void
effect_debug(struct Effect *effect);

  void
effect_free(struct Effect *effect);

#endif
