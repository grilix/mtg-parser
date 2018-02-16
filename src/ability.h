#ifndef ABILITY_H
#define ABILITY_H

#include "effect.h"

enum fl_ability_type
{
  ABILITY_STATIC,
  ABILITY_TRIGGERED,
  ABILITY_ACTIVATED,
  ABILITY_SPELL
};

struct st_ability
{
  enum fl_ability_type type;
  struct st_effect *effect;

  struct st_ability *prev;
  struct st_ability *next;
};

  struct st_ability *
create_static_ability(struct st_effect *effect);

  void
debug_ability(struct st_ability *ability);

  void
free_abilities(struct st_ability *ability);

#endif
