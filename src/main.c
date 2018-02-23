#include <stdio.h>

#include "common.h"
#include "mtg/rule.h"
#include "mtg/card.h"
#include "mtg/debug.h"
#include "input.h"

#include "../parser/parse.h"
#include "../parser/scan.h"

  static void
print_result(int parse_result, struct Input *in)
{
  if (parse_result == 0)
  {
    mtg_card_debug(in->card);
    printf("\n");
  }
  else
    debug_syntax_error(in);
}

  int
main(int argc, char **argv)
{
  int parse_result;
  struct Input *in;

  if (argc > 1)
  {
    for (int i = 1; i < argc; i++)
    {
      in = input_from_str(argv[i]);
      in->card = mtg_card_init();

      parse_result = perform_parse(in);
      print_result(parse_result, in);

      mtg_card_free(in->card);
      input_destroy(in);
      printf("\n");
    }

    // TODO: return errors.
    return 0;
  }

  in = input_from_stdin();
  in->card = mtg_card_init();

  parse_result = perform_parse(in);
  print_result(parse_result, in);

  mtg_card_free(in->card);
  input_destroy(in);

  return parse_result == 0 ? 0 : 1;
}
