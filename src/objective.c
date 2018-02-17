#include <stdio.h>
#include <string.h>

#include "common.h"
#include "objective.h"

  struct Objective *
objective_create(enum ObjectiveType flags, char *text) // text: TODO
{
  INIT_PTR(struct Objective, objective);

  COPY_STR(text, objective->text);
  objective->flags = flags;

  return objective;
}
  static char *
_objective_flags_str(enum ObjectiveType type)
{
  switch (type) {
  case OBJECTIVE_SIMPLE:
    return "-";
  case OBJECTIVE_TARGET:
    return "target";
  case OBJECTIVE_ABILITY:
    return "ability";
  }
}

  void
objective_debug(struct Objective *objective)
{
  printf("Objective(%s/%s)", _objective_flags_str(objective->flags),
                             objective->text);
}

  void
objective_free(struct Objective *objective)
{
  if (objective->text != NULL)
    free(objective->text);

  free(objective);
}
