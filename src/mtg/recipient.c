#include <stdio.h>
#include <string.h>

#include "../common.h"
#include "recipient.h"

  struct Recipient *
init_recipient(void)
{
  INIT_PTR(struct Recipient, recipient);

  recipient->with_ability = NULL;

  return recipient;
}

  struct Recipient *
recipient_create(enum RecipientFlag flag, char *text)
{
  struct Recipient *recipient = init_recipient();

  COPY_STR(text, recipient->text);
  recipient->flag = flag;

  return recipient;
}

  void
recipient_add_ability(struct Recipient *recipient, struct Ability *ability)
{
  APPEND(recipient->with_ability, ability);
}

  /*struct Recipient **/
/*recipient_create_with_ability(enum RecipientType flags, struct Ability *ability)*/
/*{*/
  /*INIT_PTR(struct Recipient, recipient);*/

  /*recipient->with_ability = ability;*/
  /*recipient->type = flags;*/

  /*return recipient;*/
/*}*/

  static char *
_debug_recipient_flag(enum RecipientFlag flag)
{
  switch (flag)
  {
  case RECIPIENT_TARGET:
    return "target:";
  }

  return "";
}

  void
recipient_debug(struct Recipient *recipient)
{
  printf("Recipient(%s", _debug_recipient_flag(recipient->flag));

  if (recipient->text != NULL)
    printf("%s", recipient->text);

  printf(")");
}

  void
recipient_free(struct Recipient *recipient)
{
  if (recipient->text != NULL)
    free(recipient->text);

  if (recipient->with_ability != NULL)
    ability_free(recipient->with_ability);

  free(recipient);
}
