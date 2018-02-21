%{
#include "../src/mtg/card.h"
#include "../src/syntax.h"
#include "parse.h"

extern char *yytext;
#define STR(T) push_token(yytext); yylval.string = yytext; return T
#define STR_V(T, V) push_token(yytext); yylval.string = V; return T
%}
%%

":" { STR(COLON); }
";" { STR(SEMICOLON); }
"," { STR(COMMA); }
\. { STR(DOT); }
\{[RWBUG]\} { STR_V(MANA_COLOR, yytext[1]); }

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
