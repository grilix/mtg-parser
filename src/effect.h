#ifndef EFFECT_H
#define EFFECT_H

enum fl_effect_type
{
  EFFECT_DESTROY
};

struct st_effect
{
  struct st_objective *source;
  struct st_objective *objective;

  enum fl_effect_type type;
};

  struct st_effect *
create_destroy_effect(struct st_objective *source,
                      struct st_objective *objective);

  void
debug_effect(struct st_effect *effect);

  void
free_effect(struct st_effect *effect);

#endif
