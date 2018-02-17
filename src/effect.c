#include <stdio.h>

#include "common.h"
#include "effect.h"
#include "objective.h"

  struct Effect *
effect_create_destroy(struct Objective *source,
                      struct Objective *objective)
{
  INIT_PTR(struct Effect, effect);

  effect->source = source;
  effect->objective = objective;
  effect->type = EFFECT_DESTROY;

  return effect;
}

  static char *
_effect_type_str(enum EffectType type)
{
  switch (type) {
  case EFFECT_DESTROY:
    return "destroy";
  }
}

  void
effect_debug(struct Effect *effect)
{
  printf("Effect(%s/", _effect_type_str(effect->type));

  if (effect->source == NULL)
    printf("<no source>");
  else
    objective_debug(effect->source);

  printf("->");

  if (effect->objective == NULL)
    printf("<no objective>");
  else
    objective_debug(effect->objective);

  printf(")");
}

  void
effect_free(struct Effect *effect)
{
  if (effect->source != NULL)
    objective_free(effect->source);

  if (effect->objective != NULL)
    objective_free(effect->objective);

  free(effect);
}
