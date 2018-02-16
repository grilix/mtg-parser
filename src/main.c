#include <stdio.h>

#include "common.h"
#include "rules.h"
#include "card.h"

  extern int
yyparse(struct st_card *current_card);

  int
main(void)
{
  struct st_card *card = init_card();

  if (yyparse(card) == 0)
  {
    debug_card(card);
    printf("\n");
  }

  free_card(card);

  return 0;
}
