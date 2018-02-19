#include <stdio.h>

#include "common.h"
#include "rules.h"
#include "card.h"
#include "syntax.h"

  extern int
yyparse(struct Card *current_card);

  int
main(void)
{
  struct Card *card = card_init();
  int parse_result;

  init_syntax_checks();

  parse_result = yyparse(card);

  if (parse_result == 0)
  {
    card_debug(card);
    printf("\n");
  }
  else
    debug_syntax_error();

  free_syntax_checks();

  card_free(card);

  return parse_result == 0 ? 0 : 1;
}
