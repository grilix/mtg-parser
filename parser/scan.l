%{
#include "../src/mtg/card.h"
#include "../src/syntax.h"
#include "parse.h"

extern char *yytext;
char *mana(char *text);

#define STR(T) push_token(yytext); yylval.string = yytext; return T
#define STR_V(T,V) push_token(yytext); yylval.string = V; return T
#define INT(T,V) push_token(yytext); yylval.integer = V; return T
%}
%%

":" { STR(COLON); }
";" { STR(SEMICOLON); }
"," { STR(COMMA); }
\. { STR(DOT); }
"{T}" { STR(TAP); }
"{X}" { STR(MANA_COLORLESS); }
\{[RWBUG]\} { STR(MANA_COLOR); }
\{[0-9]+\} { STR(MANA_COLORLESS); }

[Rr]each { STR(A_KEYWORD); }
[Ff]lying { STR(A_KEYWORD); }
[Hh]aste { STR(A_KEYWORD); }
[Cc]ycling { STR(A_KEYWORD); }

Destroy { STR(DESTROY); }
Sacrifice { STR(SACRIFICE); }
Discard { STR(DISCARD); }
Draw { STR(DRAW); }

target { STR(TARGET); }
[Tt]his { STR(THIS); }

artifact { STR(RECIPIENT); }
land { STR(RECIPIENT); }
enchantment { STR(RECIPIENT); }
creatures? { STR(RECIPIENT); }
card { STR(RECIPIENT); }

can { STR(T_CAN); }
block { STR(T_BLOCK); }
with { STR(T_WITH); }

[ \t] { push_token(yytext); }
\n { push_newline(); return NEWLINE; }
. { push_token(yytext); return yytext[0]; }

%%
