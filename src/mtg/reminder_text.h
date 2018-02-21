#ifndef REMINDER_TEXT_H
#define REMINDER_TEXT_H

#include "ability.h"

struct MtgReminderText
{
  struct MtgAbility *ability;
};

  extern struct MtgReminderText *
mtg_reminder_text_create_ability(struct MtgAbility *ability);

  extern void
mtg_reminder_text_debug(struct MtgReminderText *reminder_text);

  extern void
mtg_reminder_text_free(struct MtgReminderText *reminder_text);

#endif
