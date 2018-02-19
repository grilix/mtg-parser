#include <string.h>
#include <stdio.h>

#include "common.h"
#include "syntax.h"

static struct ParseLine *_current_line = NULL;

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
parse_line_free(struct ParseLine *line)
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
start_newline(void)
{
  int number = _current_line->number + 1;

  parse_line_free(_current_line);

  _current_line = parse_line_init();
  _current_line->number = number;
}

  extern void
push_token(char *text)
{
  INIT_PTR(struct ParseLineToken, token);

  COPY_STR(text, token->text);

  if (_current_line->eol == 1)
    start_newline();

  APPEND(_current_line->last_token, token);

  _current_line->last_token = token;
  //printf("[%s]", text);
}

  extern void
push_newline(void)
{
  _current_line->eol = 1;
}

  extern void
init_syntax_checks(void)
{
  _current_line = parse_line_init();
  _current_line->number = 1;
}
  extern void
free_syntax_checks(void)
{
  parse_line_free(_current_line);
  _current_line = NULL;
}

  extern void
debug_syntax_error(void)
{

  if (_current_line == NULL)
  {
    printf("Syntax error, no line information.\n");
    return;
  }

  printf("Syntax error:\n");
  parse_line_debug(_current_line);
}

  extern void
syntax_checkpoint(void)
{
  printf(" CHECKPOINT AT: %s\n", _current_line->last_token->text);
}

  extern void
syntax_error(char *text)
{
  printf("\n");
  debug_syntax_error();
  //printf(" -> %s\n", text);
}
