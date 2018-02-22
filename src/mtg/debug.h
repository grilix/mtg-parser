#ifndef DEBUG_H
#define DEBUG_H

#include "card.h"
#include "ability.h"
#include "mana.h"
#include "reminder_text.h"
#include "recipient.h"
#include "rule.h"

// TODO: We might not need to expose all of them.

  extern void
mtg_reminder_text_debug(struct MtgReminderText *reminder_text);

  extern void
mtg_recipient_debug(struct MtgRecipient *recipient);

  extern void
mtg_effect_debug(struct MtgEffect *effect);

  extern void
mtg_cost_debug(struct MtgCost *cost);

  extern void
mtg_ability_debug(struct MtgAbility *last_ability);

  extern void
mtg_mana_debug(struct MtgMana *mana);

  extern void
mtg_rule_debug(struct MtgRule *last_rule);

  extern void
mtg_card_debug(struct MtgCard *card);

#endif
