#include <stdio.h>

#include "common.h"
#include "effect.h"
#include "ability.h"

  struct Ability *
ability_create_static(struct Effect *effect)
{
  INIT_PTR(struct Ability, ability);

  ability->type = ABILITY_STATIC;
  ability->effect = effect;

  return ability;
}

  void
ability_debug(struct Ability *last_ability)
{
  if (last_ability->prev != NULL) {
    ability_debug(last_ability->prev);
    printf(",");
  }

  printf("Ability(");

  if (last_ability->effect == NULL)
    printf("<no effect>");
  else
    effect_debug(last_ability->effect);

  printf(")");
}

  void
ability_free(struct Ability *last_ability)
{
  if (last_ability->prev != NULL)
    ability_free(last_ability->prev);

  if (last_ability->effect != NULL)
    effect_free(last_ability->effect);

  free(last_ability);
}
