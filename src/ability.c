#include <stdio.h>
#include <string.h>

#include "common.h"
#include "effect.h"
#include "ability.h"
#include "cost.h"
#include "recipient.h"

  static struct Ability *
init_ability(void)
{
  INIT_PTR(struct Ability, ability);

  ability->cost = NULL;
  ability->keyword = NULL;
  ability->reminder_text = NULL;
  ability->effect = NULL;
  ability->can_block_recipient = NULL;
  ability->next = NULL;
  ability->prev = NULL;

  return ability;
}

  struct Ability *
ability_create_static(struct Effect *effect)
{
  struct Ability *ability = init_ability();

  ability->type = ABILITY_STATIC;
  ability->effect = effect;

  return ability;
}

  struct Ability *
ability_create_static_can_block(struct Recipient *recipient)
{
  struct Ability *ability = init_ability();

  ability->type = ABILITY_STATIC;
  ability->can_block_recipient = recipient;

  return ability;
}

  struct Ability *
ability_create_spell(struct Effect *effect)
{
  struct Ability *ability = init_ability();

  ability->type = ABILITY_SPELL;
  ability->effect = effect;

  return ability;
}

  struct Ability *
ability_create_activated(struct Cost *cost, struct Effect *effect)
{
  struct Ability *ability = init_ability();

  ability->type = ABILITY_ACTIVATED;
  ability->cost = cost;
  ability->effect = effect;

  return ability;
}

  struct Ability *
ability_create_keyword(char *keyword)
{
  struct Ability *ability = init_ability();

  ability->type = ABILITY_KEYWORD;
  COPY_STR(keyword, ability->keyword);

  return ability;
}

  void
ability_add_reminder_text(struct Ability *ability,
                          struct ReminderText *reminder_text)
{
  // TODO: multiple reminder texts?
  ability->reminder_text = reminder_text;
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

  if (last_ability->cost != NULL)
    cost_free(last_ability->cost);

  if (last_ability->keyword != NULL)
    free(last_ability->keyword);

  if (last_ability->effect != NULL)
    effect_free(last_ability->effect);

  if (last_ability->reminder_text != NULL)
    reminder_text_free(last_ability->reminder_text);

  if (last_ability->can_block_recipient != NULL)
    recipient_free(last_ability->can_block_recipient);

  free(last_ability);
}
