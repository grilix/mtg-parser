%{
#include <stdio.h>

#include "../src/card.h"
#include "../src/rules.h"
#include "../src/objective.h"
#include "../src/effect.h"
#include "../src/ability.h"

extern int yylex(void);

int yyerror(struct Card * card, char *s);
%}

%parse-param {struct Card * card}

%token <string> NEWLINE SEMICOLON COLON DOT DESTROY ARTIFACT LAND ENCHANTMENT TARGET CREATURE

%union {
  struct Rule *r_rule;
  struct Objective *r_objective;
  struct Effect *r_effect;
  struct Ability *r_ability;
  char *string;
}

%type <r_rule> rule rules
%type <r_objective> objective
%type <r_effect> effect
%type <r_ability> abilities_list ability
%type <string> objective1

%%
rules: rule
     | rules NEWLINE
     | rules NEWLINE rule
     { }
     ;

rule: abilities_list
    {
      card_add_ability_set(card, $1);
    }
    ;
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

ability: effect DOT
       /* spell ability */
       {
         $$ = ability_create_static($1);
       }
       | effect
       /* static ability */
       {
         $$ = ability_create_static($1);
       }
       ;

effect: DESTROY objective
      {
        $$ = effect_create_destroy(
          objective_create(OBJECTIVE_ABILITY, "card"),
          $2
        );
      };

objective: TARGET objective1
         {
           $$ = objective_create(OBJECTIVE_TARGET, $2);
         }
         | objective1
         {
           $$ = objective_create(OBJECTIVE_SIMPLE, $1);
         };

objective1: CREATURE
          { $$ = "creature"; }
          | ARTIFACT
          { $$ = "artifact"; };

%%

int yyerror(struct Card *_error_card, char *msg) {
  return fprintf(stderr, "YACC: %s.\n", msg);
}
