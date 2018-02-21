#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../common.h"
#include "reminder_text.h"

  struct ReminderText *
reminder_text_create_ability(struct Ability *ability)
{
  INIT_PTR(struct ReminderText, reminder);
  reminder->ability = ability;

  return reminder;
}

  void
reminder_text_debug(struct ReminderText *reminder_text)
{
  if (reminder_text->ability == NULL)
    printf("<no ability>");
  else
    ability_debug(reminder_text->ability);
}

  void
reminder_text_free(struct ReminderText *reminder_text)
{
  if (reminder_text->ability != NULL)
    ability_free(reminder_text->ability);

  free(reminder_text);
}
