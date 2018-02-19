#ifndef ABILITY_H
#define ABILITY_H

#include "effect.h"
#include "cost.h"

enum AbilityType
{
  ABILITY_KEYWORD,
  ABILITY_STATIC,
  ABILITY_TRIGGERED,
  ABILITY_ACTIVATED,
  ABILITY_SPELL
};

struct Ability
{
  enum AbilityType type;
  struct Cost *cost;
  struct Effect *effect;
  char *keyword;

  struct Ability *prev;
  struct Ability *next;
};

  struct Ability *
ability_create_spell(struct Effect *effect);

  struct Ability *
ability_create_keyword(char *keyword);

  struct Ability *
ability_create_static(struct Effect *effect);

  struct Ability *
ability_create_activated(struct Cost *cost, struct Effect *effect);

  //struct Ability *
//ability_create_triggered(struct Trigger *trigger, struct Effect *effect);

  void
ability_debug(struct Ability *last_ability);

  void
ability_free(struct Ability *last_ability);

#endif
