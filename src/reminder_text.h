#ifndef REMINDER_TEXT_H
#define REMINDER_TEXT_H

#include "ability.h"

struct ReminderText
{
  struct Ability *ability;
};

  struct ReminderText *
reminder_text_create_ability(struct Ability *ability);

  void
reminder_text_debug(struct ReminderText *reminder_text);

  void
reminder_text_free(struct ReminderText *reminder_text);

#endif
