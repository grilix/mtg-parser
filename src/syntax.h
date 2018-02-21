#ifndef SYNTAX_H
#define SYNTAX_H

struct ParseLineToken
{
  char *text;

  struct ParseLineToken *prev;
  struct ParseLineToken *next;
};

struct ParseLine
{
  int number;
  char eol;

  struct ParseLineToken *last_token;
};

  extern void
push_token(char *text);

  extern void
push_newline(void);

  extern void
init_syntax_checks(void);

  extern void
free_syntax_checks(void);

  extern void
debug_syntax_error(void);

  extern void
syntax_error(char *text);

  extern void
syntax_checkpoint(void);

#endif
