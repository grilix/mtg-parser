#include <stdio.h>
#include <string.h>

#include "../common.h"
#include "recipient.h"

  static struct MtgRecipient *
init_recipient(void)
{
  INIT_PTR(struct MtgRecipient, recipient);

  recipient->with_ability = NULL;

  return recipient;
}

  extern struct MtgRecipient *
mtg_recipient_create(enum MtgRecipientFlag flag, char *text)
{
  struct MtgRecipient *recipient = init_recipient();

  COPY_STR(text, recipient->text);
  recipient->flag = flag;

  return recipient;
}

  extern void
mtg_recipient_add_ability(struct MtgRecipient *recipient, struct MtgAbility *ability)
{
  APPEND(recipient->with_ability, ability);
}

  static char *
_debug_recipient_flag(enum MtgRecipientFlag flag)
{
  switch (flag)
  {
  case RECIPIENT_TARGET:
    return "target:";
  }

  return "";
}

  extern void
mtg_recipient_debug(struct MtgRecipient *recipient)
{
  printf("Recipient(%s", _debug_recipient_flag(recipient->flag));

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
mtg_recipient_free(struct MtgRecipient *recipient)
{
  if (recipient->text != NULL)
    free(recipient->text);

  if (recipient->with_ability != NULL)
    mtg_ability_free(recipient->with_ability);

  free(recipient);
}
