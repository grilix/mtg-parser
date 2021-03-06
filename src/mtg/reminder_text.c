#include "../common.h"
#include "reminder_text.h"

  extern struct MtgReminderText *
mtg_reminder_text_create_ability(struct MtgAbility *ability)
{
  INIT_PTR(struct MtgReminderText, reminder);
  reminder->ability = ability;

  return reminder;
}

  extern void
mtg_reminder_text_free(struct MtgReminderText *reminder_text)
{
  if (reminder_text->ability != NULL)
    mtg_ability_free(reminder_text->ability);

  free(reminder_text);
}
