#include "../common.h"
#include "effect.h"

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
  effect->type = MTG_EFFECT_DESTROY;

  return effect;
}

  extern struct MtgEffect *
mtg_effect_create_draw(int count)
{
  struct MtgEffect *effect = init_effect();

  effect->type = MTG_EFFECT_DRAW;
  effect->count = count;

  return effect;
}

  extern struct MtgEffect *
mtg_effect_create_sacrifice(struct MtgRecipient *recipient)
{
  struct MtgEffect *effect = init_effect();

  effect->recipient = recipient;
  effect->type = MTG_EFFECT_SACRIFICE;

  return effect;
}

  extern void
mtg_effect_free(struct MtgEffect *effect)
{
  if (effect->recipient != NULL)
    mtg_recipient_free(effect->recipient);

  free(effect);
}
