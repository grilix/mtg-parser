#include <stdio.h>

#include "../common.h"
#include "effect.h"
#include "recipient.h"

  static struct MtgEffect *
init_effect()
{
  INIT_PTR(struct MtgEffect, effect);

  effect->recipient = NULL;

  return effect;
}

  extern struct MtgEffect *
mtg_effect_create_destroy(struct MtgRecipient *recipient)
{
  struct MtgEffect *effect = init_effect();

  effect->recipient = recipient;
  effect->type = EFFECT_DESTROY;

  return effect;
}

  extern struct MtgEffect *
mtg_effect_create_draw(int count)
{
  struct MtgEffect *effect = init_effect();

  effect->type = EFFECT_DRAW;
  effect->count = count;

  return effect;
}

  extern struct MtgEffect *
mtg_effect_create_sacrifice(struct MtgRecipient *recipient)
{
  struct MtgEffect *effect = init_effect();

  effect->recipient = recipient;
  effect->type = EFFECT_SACRIFICE;

  return effect;
}

  static char *
_debug_effect_type(enum MtgEffectType type)
{
  switch (type) {
  case EFFECT_DESTROY:
    printf("destroy:");
    break;
  }
}

  extern void
mtg_effect_debug(struct MtgEffect *effect)
{
  printf("Effect(");

  _debug_effect_type(effect->type);

  if (effect->recipient == NULL)
    printf("<no recipient>");
  else
    mtg_recipient_debug(effect->recipient);

  printf(")");
}

  extern void
mtg_effect_free(struct MtgEffect *effect)
{
  if (effect->recipient != NULL)
    mtg_recipient_free(effect->recipient);

  free(effect);
}
