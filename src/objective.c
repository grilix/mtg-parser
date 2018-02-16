#include <stdio.h>
#include <string.h>

#include "common.h"
#include "objective.h"

  struct st_objective *
create_objective(enum fl_objective flags, char *text) // text: TODO
{
  INIT_PTR(struct st_objective, objective);

  COPY_STR(text, objective->text);
  objective->flags = flags;

  return objective;
}
  char *
objective_flags_str(enum fl_objective type)
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
debug_objective(struct st_objective *objective)
{
  printf("Objective(%s/%s)", objective_flags_str(objective->flags),
                             objective->text);
}

  void
free_objective(struct st_objective *objective)
{
  if (objective->text != NULL)
    free(objective->text);

  free(objective);
}
