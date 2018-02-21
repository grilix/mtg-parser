#ifndef RECIPIENT_H
#define RECIPIENT_H

#include "ability.h"

enum MtgRecipientFlag
{
  RECIPIENT_SIMPLE,
  RECIPIENT_TARGET,
  RECIPIENT_SELF
};

enum MtgRecipientTargetType
{
  TARGET_TYPE_OBJECT,
  TARGET_TYPE_PLAYER,
  TARGET_TYPE_ZONE
};

enum MtgRecipientObjectType
{
  OBJECT_TYPE_PERMANENT,
  OBJECT_TYPE_SPELL
};

enum MtgPermanentType
{
  PERMANENT_CREATURE,
  PERMANENT_LAND,
  PERMANENT_ARTIFACT,
  PERMANENT_ENCHANTMENT
};


struct MtgRecipient
{
  enum MtgRecipientFlag flag;
  enum MtgRecipientTargetType target_type;
  enum MtgRecipientObjectType object_type;
  enum MtgPermanentType permanent_type;

  struct MtgAbility *with_ability;

  char *text;
};

  extern struct MtgRecipient *
mtg_recipient_create(enum MtgRecipientFlag flag, char *text);

  extern void
mtg_recipient_add_ability(struct MtgRecipient *recipient, struct MtgAbility *ability);

  extern void
mtg_recipient_debug(struct MtgRecipient *recipient);

  extern void
mtg_recipient_free(struct MtgRecipient *recipient);

#endif
