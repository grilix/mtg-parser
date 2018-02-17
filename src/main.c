#include <stdio.h>

#include "common.h"
#include "rules.h"
#include "card.h"

  extern int
yyparse(struct Card *current_card);

  int
main(void)
{
  struct Card *card = card_init();

  if (yyparse(card) == 0)
  {
    card_debug(card);
    printf("\n");
  }

  card_free(card);

  return 0;
}
