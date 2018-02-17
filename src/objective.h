#ifndef OBJECTIVE_H
#define OBJECTIVE_H

enum ObjectiveType
{
  OBJECTIVE_SIMPLE,
  OBJECTIVE_TARGET,
  OBJECTIVE_ABILITY
};

struct Objective
{
  enum ObjectiveType flags;
  char *text;
};

  struct Objective *
objective_create(enum ObjectiveType flags, char *text);

  void
objective_debug(struct Objective *objective);

  void
objective_free(struct Objective *objective);

#endif
