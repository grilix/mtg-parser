#ifndef ABILITY_H
#define ABILITY_H

#include "effect.h"
#include "cost.h"
#include "reminder_text.h"

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
  char *keyword;
  struct Effect *effect;
  struct ReminderText *reminder_text;
  struct Recipient *can_block_recipient;

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
ability_create_static_can_block(struct Recipient *recipient);

  struct Ability *
ability_create_activated(struct Cost *cost, struct Effect *effect);

  void
ability_add_reminder_text(struct Ability *ability,
                          struct ReminderText *reminder_text);

  void
ability_add_cost(struct Ability *ability,
                 struct Cost *cost);

  void
ability_debug(struct Ability *last_ability);

  void
ability_free(struct Ability *last_ability);

#endif
