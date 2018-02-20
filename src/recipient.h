#ifndef RECIPIENT_H
#define RECIPIENT_H

#include "ability.h"

enum RecipientFlag
{
  RECIPIENT_SIMPLE,
  RECIPIENT_TARGET,
  RECIPIENT_SELF
};

enum RecipientTargetType
{
  TARGET_TYPE_OBJECT,
  TARGET_TYPE_PLAYER,
  TARGET_TYPE_ZONE
};

enum RecipientObjectType
{
  OBJECT_TYPE_PERMANENT,
  OBJECT_TYPE_SPELL
};

enum PermanentType
{
  PERMANENT_CREATURE,
  PERMANENT_LAND,
  PERMANENT_ARTIFACT,
  PERMANENT_ENCHANTMENT
};


struct Recipient
{
  enum RecipientFlag flag;
  enum RecipientTargetType target_type;
  enum RecipientObjectType object_type;
  enum PermanentType permanent_type;

  struct Ability *with_ability;

  char *text;
};

  struct Recipient *
recipient_create(enum RecipientFlag flag, char *text);

  void
recipient_add_ability(struct Recipient *recipient, struct Ability *ability);

  void
recipient_debug(struct Recipient *recipient);

  void
recipient_free(struct Recipient *recipient);

#endif
