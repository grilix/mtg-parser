#include <stdio.h>

#include "common.h"
#include "mtg/rule.h"
#include "mtg/card.h"
#include "mtg/debug.h"
#include "syntax.h"

  extern int
yyparse(struct MtgCard *current_card);

  int
main(void)
{
  struct MtgCard *card = mtg_card_init();
  int parse_result;

  init_syntax_checks();

  parse_result = yyparse(card);

  if (parse_result == 0)
  {
    mtg_card_debug(card);
    printf("\n");
  }
  else
    debug_syntax_error();

  free_syntax_checks();

  mtg_card_free(card);

  return parse_result == 0 ? 0 : 1;
}
