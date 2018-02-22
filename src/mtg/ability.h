#ifndef ABILITY_H
#define ABILITY_H

#include "effect.h"
#include "cost.h"
#include "reminder_text.h"
#include "recipient.h"

enum MtgAbilityType
{
  ABILITY_KEYWORD,
  ABILITY_STATIC,
  ABILITY_TRIGGERED,
  ABILITY_ACTIVATED,
  ABILITY_SPELL
};

struct MtgAbility
{
  enum MtgAbilityType type;
  struct MtgCost *cost;
  char *keyword;
  struct MtgEffect *effect;
  struct MtgReminderText *reminder_text;
  struct MtgRecipient *can_block_recipient;

  struct MtgAbility *prev;
  struct MtgAbility *next;
};

  extern struct MtgAbility *
mtg_ability_create_spell(struct MtgEffect *effect);

  extern struct MtgAbility *
mtg_ability_create_keyword(char *keyword);

  extern struct MtgAbility *
mtg_ability_create_static(struct MtgEffect *effect);

  extern struct MtgAbility *
mtg_ability_create_static_can_block(struct MtgRecipient *recipient);

  extern struct MtgAbility *
mtg_ability_create_activated(struct MtgCost *cost, struct MtgEffect *effect);

  extern void
mtg_ability_add_reminder_text(struct MtgAbility *ability,
                          struct MtgReminderText *reminder_text);

  extern void
mtg_ability_add_cost(struct MtgAbility *ability,
                 struct MtgCost *cost);

  extern void
mtg_ability_free(struct MtgAbility *last_ability);

#endif
