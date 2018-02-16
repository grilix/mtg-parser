%{
#include "../src/card.h"
#include "parse.h"
extern char* yytext;
%}

%%

":" { return COLON; }
";" { return SEMICOLON; }
\. { return DOT; }
[Dd]estroy { return DESTROY; }
artifact { return ARTIFACT; }
land { return LAND; }
enchantment { return ENCHANTMENT; }
target { return TARGET; }
creature { return CREATURE; }
[ \t]	{ }
\n	{ return NEWLINE; }
.	{ return yytext[0]; }

%%
