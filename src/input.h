#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

#include "mtg/card.h"
#include "input.h"

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

struct Input
{
  FILE *src;
  struct MtgCard *card;
  struct ParseLine *_current_line;
};

extern struct Input * input_from_str(char *str);

extern struct Input * input_from_stdin();

extern void input_destroy(struct Input *in);

extern int perform_parse(struct Input *in);

extern void push_token(struct Input *in, char *text);

extern void push_newline(struct Input *in);

extern void debug_syntax_error(struct Input *in);

extern void syntax_error(struct Input *in, char *text);

extern void syntax_checkpoint(struct Input *in);

#endif
