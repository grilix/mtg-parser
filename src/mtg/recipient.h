#ifndef RECIPIENT_H
#define RECIPIENT_H

#include "ability.h"

enum MtgRecipientFlag
{
  MTG_RECIPIENT_SIMPLE,
  MTG_RECIPIENT_TARGET,
  MTG_RECIPIENT_SELF
};

enum MtgRecipientTargetType
{
  MTG_TARGET_TYPE_OBJECT,
  MTG_TARGET_TYPE_PLAYER,
  MTG_TARGET_TYPE_ZONE
};

enum MtgRecipientObjectType
{
  MTG_OBJECT_TYPE_PERMANENT,
  MTG_OBJECT_TYPE_SPELL
};

enum MtgPermanentType
{
  MTG_PERMANENT_CREATURE,
  MTG_PERMANENT_LAND,
  MTG_PERMANENT_ARTIFACT,
  MTG_PERMANENT_ENCHANTMENT
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
mtg_recipient_free(struct MtgRecipient *recipient);

#endif
