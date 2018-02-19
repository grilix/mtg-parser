%{
#include "../src/card.h"
#include "../src/syntax.h"
#include "parse.h"

extern char *yytext;
#define STR(T) push_token(yytext); yylval.string = yytext; return T
%}
%%

":" { STR(COLON); }
";" { STR(SEMICOLON); }
"," { STR(COMMA); }
\. { STR(DOT); }

[Rr]each { STR(A_STATIC); }
[Ff]lying { STR(A_STATIC); }
[Hh]aste { STR(A_STATIC); }

Destroy { STR(DESTROY); }
Sacrifice { STR(SACRIFICE); }

target { STR(TARGET); }

artifact { STR(OBJECTIVE); }
land { STR(OBJECTIVE); }
enchantment { STR(OBJECTIVE); }
creature { STR(OBJECTIVE); }

[ \t] { push_token(yytext); }
\n { push_newline(); return NEWLINE; }
. { push_token(yytext); return yytext[0]; }

%%
