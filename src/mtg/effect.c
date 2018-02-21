#include <stdio.h>

#include "../common.h"
#include "effect.h"
#include "recipient.h"

  struct Effect *
init_effect()
{
  INIT_PTR(struct Effect, effect);

  effect->recipient = NULL;

  return effect;
}

  struct Effect *
effect_create_destroy(struct Recipient *recipient)
{
  struct Effect *effect = init_effect();

  effect->recipient = recipient;
  effect->type = EFFECT_DESTROY;

  return effect;
}

  struct Effect *
effect_create_draw(int count)
{
  struct Effect *effect = init_effect();

  effect->type = EFFECT_DRAW;
  effect->count = count;

  return effect;
}

  struct Effect *
effect_create_sacrifice(struct Recipient *recipient)
{
  struct Effect *effect = init_effect();

  effect->recipient = recipient;
  effect->type = EFFECT_SACRIFICE;

  return effect;
}

  static char *
_debug_effect_type(enum EffectType type)
{
  switch (type) {
  case EFFECT_DESTROY:
    printf("destroy:");
    break;
  }
}

  void
effect_debug(struct Effect *effect)
{
  printf("Effect(");

  _debug_effect_type(effect->type);

  if (effect->recipient == NULL)
    printf("<no recipient>");
  else
    recipient_debug(effect->recipient);

  printf(")");
}

  void
effect_free(struct Effect *effect)
{
  if (effect->recipient != NULL)
    recipient_free(effect->recipient);

  free(effect);
}
