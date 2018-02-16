#ifndef OBJECTIVE_H
#define OBJECTIVE_H

enum fl_objective
{
  OBJECTIVE_SIMPLE,
  OBJECTIVE_TARGET,
  OBJECTIVE_ABILITY
};

struct st_objective
{
  enum fl_objective flags;
  char *text;
};

  struct st_objective *
create_objective(enum fl_objective flags, char *text);

  void
debug_objective(struct st_objective *objective);

  void
free_objective(struct st_objective *objective);

#endif
