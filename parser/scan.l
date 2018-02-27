%{
#include "parse.h"
#include "../src/mtg/card.h"
#include "../src/input.h"

#define STR(T) push_token(yyextra, yytext); yylval->string = yytext; return T
#define STR_V(T,V) push_token(yyextra, yytext); yylval->string = V; return T
#define INT(T,V) push_token(yyextra, yytext); yylval->integer = V; return T
%}

%option reentrant bison-bridge noyywrap nodefault
%option header-file="parser/scan.h"

%%

":" { STR(COLON); }
";" { STR(SEMICOLON); }
"," { STR(COMMA); }
\. { STR(DOT); }
"{T}" { STR(TAP); }
"{X}" { STR(MANA_COLORLESS); }
\{[RWBUG]\} { STR(MANA_COLOR); }
\{[0-9]+\} { STR(MANA_COLORLESS); }

  /* Static abilities keywords */
[Rr]each { STR(TOK_STATIC_KEYWORD); }
[Ff]lying { STR(TOK_STATIC_KEYWORD); }
[Hh]aste { STR(TOK_STATIC_KEYWORD); }

  /* Activated abilities keywords */
[Cc]ycling { STR(TOK_ACTIVATED_KEYWORD); }

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

[ \t] { push_token(yyextra, yytext); }
\n { push_newline(yyextra); return NEWLINE; }
. { push_token(yyextra, yytext); return yytext[0]; }

%%
