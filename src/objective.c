#include <stdio.h>
#include <string.h>

#include "common.h"
#include "objective.h"

  struct Objective *
objective_create(enum ObjectiveType flags, char *text)
{
  INIT_PTR(struct Objective, objective);

  COPY_STR(text, objective->text);
  objective->type = flags;

  return objective;
}
  static char *
_debug_objective_type(enum ObjectiveType type)
{
  switch (type)
  {
  case OBJECTIVE_TARGET:
    return "target:";
  }

  return "";
}

  void
objective_debug(struct Objective *objective)
{
  printf("Objective(%s", _debug_objective_type(objective->type));

  if (objective->text != NULL)
    printf("%s", objective->text);

  printf(")");
}

  void
objective_free(struct Objective *objective)
{
  if (objective->text != NULL)
    free(objective->text);

  free(objective);
}
