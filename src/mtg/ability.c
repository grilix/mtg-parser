#include <stdio.h>
#include <string.h>

#include "../common.h"
#include "effect.h"
#include "ability.h"
#include "cost.h"
#include "recipient.h"

  static struct MtgAbility *
init_ability(void)
{
  INIT_PTR(struct MtgAbility, ability);

  ability->cost = NULL;
  ability->keyword = NULL;
  ability->reminder_text = NULL;
  ability->effect = NULL;
  ability->can_block_recipient = NULL;
  ability->next = NULL;
  ability->prev = NULL;

  return ability;
}

  extern struct MtgAbility *
mtg_ability_create_static(struct MtgEffect *effect)
{
  struct MtgAbility *ability = init_ability();

  ability->type = ABILITY_STATIC;
  ability->effect = effect;

  return ability;
}

  extern struct MtgAbility *
mtg_ability_create_static_can_block(struct MtgRecipient *recipient)
{
  struct MtgAbility *ability = init_ability();

  ability->type = ABILITY_STATIC;
  ability->can_block_recipient = recipient;

  return ability;
}

  extern struct MtgAbility *
mtg_ability_create_spell(struct MtgEffect *effect)
{
  struct MtgAbility *ability = init_ability();

  ability->type = ABILITY_SPELL;
  ability->effect = effect;

  return ability;
}

  extern struct MtgAbility *
mtg_ability_create_activated(struct MtgCost *cost, struct MtgEffect *effect)
{
  struct MtgAbility *ability = init_ability();

  ability->type = ABILITY_ACTIVATED;
  ability->cost = cost;
  ability->effect = effect;

  return ability;
}

  extern struct MtgAbility *
mtg_ability_create_keyword(char *keyword)
{
  struct MtgAbility *ability = init_ability();

  ability->type = ABILITY_KEYWORD;
  COPY_STR(keyword, ability->keyword);

  return ability;
}

  extern void
mtg_ability_add_reminder_text(struct MtgAbility *ability,
                          struct MtgReminderText *reminder_text)
{
  // TODO: multiple reminder texts?
  ability->reminder_text = reminder_text;
}

  extern void
mtg_ability_add_cost(struct MtgAbility *ability,
                 struct MtgCost *cost)
{
  APPEND(ability->cost, cost);
}

  extern void
mtg_ability_debug(struct MtgAbility *last_ability)
{
  if (last_ability->prev != NULL) {
    mtg_ability_debug(last_ability->prev);
    printf(",");
  }

  printf("Ability(");

  {
    if (last_ability->cost == NULL)
    {
      if (last_ability->type == ABILITY_ACTIVATED)
        printf("<no cost>,");
    }
    else
    {
      mtg_cost_debug(last_ability->cost);
      printf(",");
    }
  }

  if (last_ability->type == ABILITY_KEYWORD)
    printf("%s", last_ability->keyword);
  else
  {
    if (last_ability->effect == NULL)
      printf("<no effect>");
    else
      mtg_effect_debug(last_ability->effect);
  }

  printf(")");
}

  extern void
mtg_ability_free(struct MtgAbility *last_ability)
{
  if (last_ability->prev != NULL)
    mtg_ability_free(last_ability->prev);

  if (last_ability->cost != NULL)
    mtg_cost_free(last_ability->cost);

  if (last_ability->keyword != NULL)
    free(last_ability->keyword);

  if (last_ability->effect != NULL)
    mtg_effect_free(last_ability->effect);

  if (last_ability->reminder_text != NULL)
    mtg_reminder_text_free(last_ability->reminder_text);

  if (last_ability->can_block_recipient != NULL)
    mtg_recipient_free(last_ability->can_block_recipient);

  free(last_ability);
}
