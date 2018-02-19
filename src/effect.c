#include <stdio.h>

#include "common.h"
#include "effect.h"
#include "objective.h"

  struct Effect *
effect_create_destroy(struct Objective *objective)
{
  INIT_PTR(struct Effect, effect);

  effect->objective = objective;
  effect->type = EFFECT_DESTROY;

  return effect;
}

  struct Effect *
effect_create_sacrifice(struct Objective *objective)
{
  INIT_PTR(struct Effect, effect);

  effect->objective = objective;
  effect->type = EFFECT_SACRIFICE;

  return effect;
}

  static char *
_debug_effect_type(enum EffectType type)
{
  switch (type) {
  case EFFECT_DESTROY:
    printf("destroy:");
    break;
  }
}

  void
effect_debug(struct Effect *effect)
{
  printf("Effect(");

  _debug_effect_type(effect->type);

  if (effect->objective == NULL)
    printf("<no objective>");
  else
    objective_debug(effect->objective);

  printf(")");
}

  void
effect_free(struct Effect *effect)
{
  if (effect->objective != NULL)
    objective_free(effect->objective);

  free(effect);
}
