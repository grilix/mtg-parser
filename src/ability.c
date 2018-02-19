#include <stdio.h>
#include <string.h>

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

  struct Ability *
ability_create_spell(struct Effect *effect)
{
  INIT_PTR(struct Ability, ability);

  ability->type = ABILITY_SPELL;
  ability->effect = effect;

  return ability;
}

  struct Ability *
ability_create_activated(struct Cost *cost, struct Effect *effect)
{
  INIT_PTR(struct Ability, ability);

  ability->type = ABILITY_ACTIVATED;
  ability->cost = cost;
  ability->effect = effect;

  return ability;
}

  struct Ability *
ability_create_keyword(char *keyword)
{
  INIT_PTR(struct Ability, ability);
  ability->type = ABILITY_KEYWORD;
  COPY_STR(keyword, ability->keyword);

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

  if (last_ability->type == ABILITY_ACTIVATED)
  {
    if (last_ability->cost == NULL)
      printf("<no cost>");
    else
      cost_debug(last_ability->cost);

    printf(",");
  }

  if (last_ability->type == ABILITY_KEYWORD)
    printf("%s", last_ability->keyword);
  else
  {
    if (last_ability->effect == NULL)
      printf("<no effect>");
    else
      effect_debug(last_ability->effect);
  }

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
