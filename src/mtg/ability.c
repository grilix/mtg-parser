#include <string.h>

#include "../common.h"
#include "ability.h"

  static struct MtgAbility *
init_ability(void)
{
  INIT_PTR(struct MtgAbility, ability);

  ability->cost = NULL;
  ability->keyword = NULL;
  ability->reminder_text = NULL;
  ability->effect = NULL;
  ability->source = NULL;
  ability->can_block_recipient = NULL;
  ability->next = NULL;
  ability->prev = NULL;

  return ability;
}

  extern struct MtgAbility *
mtg_ability_from_static_keyword(char *keyword)
{
  int pos = search_string(staticAbilities, keyword);

  if (pos < 0)
    return NULL;

  struct MtgAbility *ability = init_ability();

  ability->type = ABILITY_STATIC;

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

  if (last_ability->source != NULL)
    mtg_recipient_free(last_ability->source);

  if (last_ability->can_block_recipient != NULL)
    mtg_recipient_free(last_ability->can_block_recipient);

  free(last_ability);
}
