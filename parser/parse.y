%{
#include <stdio.h>

#include "../src/card.h"
#include "../src/rules.h"
#include "../src/objective.h"
#include "../src/effect.h"
#include "../src/ability.h"
#include "../src/cost.h"
#include "../src/syntax.h"

extern int yylex(void);

int yyerror(struct Card * card, char *s);
%}

%parse-param {struct Card * card}

%token <string> NEWLINE SEMICOLON COLON DOT COMMA DESTROY OBJECTIVE TARGET SACRIFICE
%token <string> A_STATIC

%union {
  struct Rule *r_rule;
  struct Objective *r_objective;
  struct Effect *r_effect;
  struct Ability *r_ability;
  struct Cost *r_cost;
  char *string;
}

%type <r_rule> rule rules
%type <r_objective> objective
%type <r_effect> effect
%type <r_cost> cost_list cost sacrifice
%type <r_ability> abilities_list ability static_ability
%type <string> error

%%
rules: rule
     | rules rule
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

ability: effect DOT NEWLINE
       {
         /* spell ability */
         $$ = ability_create_spell($1);
       }
       | static_ability NEWLINE
       {
         /* static ability */
         $$ = $1; //ability_create_static($1);
       }
       | cost_list COLON effect DOT
       {
         /* activated ability */
         $$ = ability_create_activated($1, $3);
       }
       /*
       | trigger COMMA ability NEWLINE
       {
         $$ = ability_create_triggered($1, $3);
       }
       */
       ;

static_ability: A_STATIC
           {
             $$ = ability_create_keyword($1);
           }
           | static_ability COMMA static_ability
           {
                $1->next = $3;
                $3->prev = $1;
                $$ = $3;
           }
           ;
cost_list: cost
         /*{*/
           /*//$$ = cost_create($1);*/
           /*$$ = $1;*/
         /*}*/
         ;

cost: sacrifice
    /*{*/
      /*$$ = $1;*/
    /*}*/
    ;

sacrifice: SACRIFICE 'a' objective
         {
          $$ = cost_create_sacrifice($3);
         }
         ;

effect: DESTROY objective
      {
        $$ = effect_create_destroy($2);
      }
      ;

objective: TARGET OBJECTIVE
         {
           $$ = objective_create(OBJECTIVE_TARGET, $2);
         }
         | OBJECTIVE
         {
           $$ = objective_create(OBJECTIVE_SIMPLE, $1);
         }
         ;

%%

int yyerror(struct Card *card, char *msg)
{
  return 1; //fprintf(stderr, "YACC: %s.\n", msg);
}
