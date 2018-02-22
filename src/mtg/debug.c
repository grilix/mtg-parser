#include <stdlib.h>
#include <stdio.h>

#include "debug.h"

  static void
debug_cost_type(struct MtgCost *cost)
{
  switch (cost->type)
  {
  case MTG_COST_SACRIFICE:
    printf("sacrifice:");
    break;
  case MTG_COST_TAP:
    printf("tap");
    break;
  case MTG_COST_MANA:
    mtg_mana_debug(cost->mana);
    break;
  }
}

  static char *
debug_recipient_flag(enum MtgRecipientFlag flag)
{
  switch (flag)
  {
  case MTG_RECIPIENT_TARGET:
    return "target:";
  }

  return "";
}

  static int
mana_is(struct MtgMana *mana, enum MtgManaType type)
{
  return (mana->type & type) == type;
}

  static char *
debug_effect_type(enum MtgEffectType type)
{
  switch (type) {
  case MTG_EFFECT_DESTROY:
    printf("destroy:");
    break;
  }
}

  extern void
mtg_reminder_text_debug(struct MtgReminderText *reminder_text)
{
  if (reminder_text->ability == NULL)
    printf("<no ability>");
  else
    mtg_ability_debug(reminder_text->ability);
}

  extern void
mtg_recipient_debug(struct MtgRecipient *recipient)
{
  printf("Recipient(%s", debug_recipient_flag(recipient->flag));

  if (recipient->text != NULL)
    printf("%s", recipient->text);

  if (recipient->with_ability != NULL)
  {
    printf("(");
    mtg_ability_debug(recipient->with_ability);
    printf(")");
  }
  printf(")");
}

  extern void
mtg_effect_debug(struct MtgEffect *effect)
{
  printf("Effect(");

  debug_effect_type(effect->type);

  if (effect->type == MTG_EFFECT_DRAW)
    printf("draw:%d", effect->count);
  else
  {
    if (effect->recipient == NULL)
      printf("<no recipient>");
    else
      mtg_recipient_debug(effect->recipient);
  }

  printf(")");
}

  extern void
mtg_cost_debug(struct MtgCost *cost)
{
  if (cost->prev != NULL)
  {
    mtg_cost_debug(cost->prev);
    printf(",");
  }

  printf("Cost(");

  debug_cost_type(cost);

  if (cost->recipient != NULL)
    mtg_recipient_debug(cost->recipient);

  printf(")");
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
mtg_mana_debug(struct MtgMana *mana)
{
  if (mana->prev != NULL)
  {
    mtg_mana_debug(mana->prev);
    printf(",");
  }

  printf("Mana(");
  if (mana_is(mana, MTG_MANA_COLORLESS))
  {
    if (mana_is(mana, MTG_MANA_X))
      printf("X");
    else
      printf("%d", mana->amount);
  }
  else
  {
    if (mana_is(mana, MTG_MANA_WHITE))
      printf("W");
    if (mana_is(mana, MTG_MANA_BLUE))
      printf("U");
    if (mana_is(mana, MTG_MANA_BLACK))
      printf("B");
    if (mana_is(mana, MTG_MANA_RED))
      printf("R");
    if (mana_is(mana, MTG_MANA_GREEN))
      printf("G");
  }
  printf(")");
}

  extern void
mtg_rule_debug(struct MtgRule *last_rule)
{
  if (last_rule->prev != NULL) {
    mtg_rule_debug(last_rule->prev);
    printf(",");
  }

  printf("Rule(");

  if (last_rule->last_ability == NULL)
    printf("<no ability>");
  else
    mtg_ability_debug(last_rule->last_ability);

  printf(")");
}

  extern void
mtg_card_debug(struct MtgCard *card)
{
  printf("Card(");

  if (card->last_rule == NULL)
    printf("<no rules>");
  else
    mtg_rule_debug(card->last_rule);

  printf(")");
}

