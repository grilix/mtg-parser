#ifndef EFFECT_H
#define EFFECT_H

enum EffectType
{
  EFFECT_DESTROY
};

struct Effect
{
  struct Objective *source;
  struct Objective *objective;

  enum EffectType type;
};

  struct Effect *
effect_create_destroy(struct Objective *source,
                      struct Objective *objective);

  void
effect_debug(struct Effect *effect);

  void
effect_free(struct Effect *effect);

#endif
