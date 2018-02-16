%{
#include <stdio.h>

#include "../src/card.h"
#include "../src/rules.h"
#include "../src/objective.h"
#include "../src/effect.h"
#include "../src/ability.h"

extern int yylex(void);

int yyerror(struct st_card * card, char *s);
%}

%parse-param {struct st_card * card}

%token <string> NEWLINE SEMICOLON COLON DOT DESTROY ARTIFACT LAND ENCHANTMENT TARGET CREATURE

%union {
  struct st_rule *r_rule;
  struct st_objective *r_objective;
  struct st_effect *r_effect;
  struct st_ability *r_ability;
  char *string;
}

%type <r_objective> objective
%type <r_effect> effect destroy
%type <r_ability> abilities_list ability
%type <string> objective1

%%
rule: abilities_list
    {
      add_card_empty_rule(card);

      add_rule_ability(card->rule_list, $1);
    };

abilities_list: abilities_list SEMICOLON ability
              {
                //TODO: ?
                $1->next = $3;
                $3->prev = $1;
                $$ = $3;
              }
              | ability
              {
                $$ = $1;
              }
              ;

ability: effect DOT NEWLINE
       /* spell ability */
       {
         //$$ = create_spell_ability($1);
         $$ = create_static_ability($1);
       }
       | effect
       /* static ability */
       {
         $$ = create_static_ability($1);
       };

effect: destroy
      {
        $$ = $1;
      };

destroy: DESTROY objective
      {
        $$ = create_destroy_effect(
          create_objective(OBJECTIVE_ABILITY, "card"),
          $2
        );
      };

objective: TARGET objective1
         {
            $$ = create_objective(OBJECTIVE_TARGET, $2);
         }
         | objective1
         {
            $$ = create_objective(OBJECTIVE_SIMPLE, $1);
         };

objective1: CREATURE
          { $$ = "creature"; }
          | ARTIFACT
          { $$ = "artifact"; };

%%

int yyerror(struct st_card *_error_card, char *msg) {
  return fprintf(stderr, "YACC: %s\n", msg);
}
