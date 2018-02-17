#ifndef ABILITY_H
#define ABILITY_H

#include "effect.h"

enum AbilityType
{
  ABILITY_STATIC,
  ABILITY_TRIGGERED,
  ABILITY_ACTIVATED,
  ABILITY_SPELL
};

struct Ability
{
  enum AbilityType type;
  struct Effect *effect;

  struct Ability *prev;
  struct Ability *next;
};

  struct Ability *
ability_create_static(struct Effect *effect);

  void
ability_debug(struct Ability *last_ability);

  void
ability_free(struct Ability *last_ability);

#endif
