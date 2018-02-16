#include <stdio.h>

#include "common.h"
#include "effect.h"
#include "ability.h"

  struct st_ability *
create_static_ability(struct st_effect *effect)
{
  INIT_PTR(struct st_ability, ability);

  ability->type = ABILITY_STATIC;
  ability->effect = effect;

  return ability;
}

  void
debug_ability(struct st_ability *ability)
{
  if (ability->prev != NULL) {
    debug_ability(ability->prev);
    printf(",");
  }

  printf("Ability(");

  if (ability->effect == NULL)
    printf("<no effect>");
  else
    debug_effect(ability->effect);

  printf(")");
}

  void
free_abilities(struct st_ability *ability)
{
  if (ability->prev != NULL)
    free_abilities(ability->prev);

  if (ability->effect != NULL)
    free_effect(ability->effect);

  free(ability);
}
