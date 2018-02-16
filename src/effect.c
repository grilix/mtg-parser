#include <stdio.h>

#include "common.h"
#include "effect.h"
#include "objective.h"

  struct st_effect *
create_destroy_effect(struct st_objective *source,
                      struct st_objective *objective)
{
  INIT_PTR(struct st_effect, effect);

  effect->source = source;
  effect->objective = objective;
  effect->type = EFFECT_DESTROY;

  return effect;
}

  char *
effect_type_str(enum fl_effect_type type)
{
  switch (type) {
  case EFFECT_DESTROY:
    return "destroy";
  }
}

  void
debug_effect(struct st_effect *effect)
{
  printf("Effect(%s/", effect_type_str(effect->type));

  if (effect->source == NULL)
    printf("<no source>");
  else
    debug_objective(effect->source);

  printf("->");

  if (effect->objective == NULL)
    printf("<no objective>");
  else
    debug_objective(effect->objective);

  printf(")");
}

  void
free_effect(struct st_effect *effect)
{
  if (effect->source != NULL)
    free_objective(effect->source);

  if (effect->objective != NULL)
    free_objective(effect->objective);

  free(effect);
}
