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

  void
push_token(char *text);

  void
push_newline(void);

  void
init_syntax_checks(void);

  void
free_syntax_checks(void);

  void
debug_syntax_error(void);

  void
syntax_error(char *text);

  void
syntax_checkpoint(void);

#endif
