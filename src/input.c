#include <stdio.h>
#include <string.h>

#include "common.h"
#include "input.h"
#include "mtg/debug.h"

#include "../parser/parse.h"
#include "../parser/scan.h"

static void init_syntax_checks(struct Input *in);
static void free_syntax_checks(struct Input *in);
static struct ParseLine * parse_line_init(void);
static void parse_line_destroy(struct ParseLine *line);
extern void debug_syntax_error(struct Input *in);

  extern struct Input *
input_from_str(char *str)
{
  INIT_PTR(struct Input, in);

  in->src = fmemopen(str, strlen(str) + 1, "r");
  in->card = NULL;
  in->_current_line = parse_line_init();
  in->_current_line->number = 1;

  return in;
}

  extern struct Input *
input_from_stdin()
{
  INIT_PTR(struct Input, in);

  in->src = stdin;
  in->card = NULL;
  in->_current_line = parse_line_init();
  in->_current_line->number = 1;

  return in;
}

  extern void
input_destroy(struct Input *in)
{
  fclose(in->src);
  if (in->_current_line != NULL)
  {
    parse_line_destroy(in->_current_line);
    in->_current_line = NULL;
  }
  free(in);
}

  extern int
perform_parse(struct Input *in)
{
  yyscan_t sc;
  int parse_result;

  yylex_init(&sc);
  yyset_in(in->src, sc);
  yyset_extra(in, sc);

  parse_result = yyparse(sc, in);

  yylex_destroy(sc);

  return parse_result;
}

  static struct ParseLine *
parse_line_init(void)
{
  INIT_PTR(struct ParseLine, line);

  line->last_token = NULL;
  line->eol = 0;

  return line;
}

  static void
parse_line_token_free(struct ParseLineToken *last_token)
{
  if (last_token->prev != NULL)
    parse_line_token_free(last_token->prev);

  if (last_token->text != NULL)
    free(last_token->text);

  free(last_token);
}

  static void
parse_line_destroy(struct ParseLine *line)
{
  if (line->last_token != NULL)
    parse_line_token_free(line->last_token);

  free(line);
}

  static void
parse_line_token_debug(struct ParseLineToken *last_token)
{
  if (last_token->prev != NULL)
    parse_line_token_debug(last_token->prev);

  if (last_token->text != NULL)
    printf("%s", last_token->text);
}

  static void
parse_line_debug(struct ParseLine *line)
{
  printf("%d:", line->number);

  if (line->last_token != NULL)
    parse_line_token_debug(line->last_token);
}

  static void
start_newline(struct Input *in)
{
  int number = in->_current_line->number + 1;

  parse_line_destroy(in->_current_line);

  in->_current_line = parse_line_init();
  in->_current_line->number = number;
}

  extern void
push_token(struct Input *in, char *text)
{
  INIT_PTR(struct ParseLineToken, token);

  COPY_STR(text, token->text);

  if (in->_current_line->eol == 1)
    start_newline(in);

  APPEND(in->_current_line->last_token, token);

  in->_current_line->last_token = token;
}

  extern void
push_newline(struct Input *in)
{
  in->_current_line->eol = 1;
}

  extern void
debug_syntax_error(struct Input *in)
{

  if (in->_current_line == NULL)
  {
    printf("Syntax error, no line information.\n");
    return;
  }

  printf("Syntax error:\n");
  parse_line_debug(in->_current_line);
}

  extern void
syntax_checkpoint(struct Input *in)
{
  printf(" CHECKPOINT AT: %s\n", in->_current_line->last_token->text);
}

  extern void
syntax_error(struct Input *in, char *text)
{
  printf("\n");
  debug_syntax_error(in);
}
