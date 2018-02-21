%{
#include <stdio.h>

#include "../src/mtg/card.h"
#include "../src/mtg/rule.h"
#include "../src/mtg/recipient.h"
#include "../src/mtg/effect.h"
#include "../src/mtg/ability.h"
#include "../src/mtg/cost.h"
#include "../src/mtg/reminder_text.h"
#include "../src/syntax.h"

extern int yylex(void);

int yyerror(struct Card * card, char *s);
%}

%parse-param {struct Card * card}

%token <string> NEWLINE SEMICOLON COLON DOT COMMA RECIPIENT TARGET THIS
%token <string> DESTROY SACRIFICE DISCARD DRAW
%token <r_char> MANA_COLOR
%token <string> T_CAN T_BLOCK T_WITH
%token <string> A_KEYWORD

%union {
  struct Rule *r_rule;
  struct Recipient *r_recipient;
  struct Effect *r_effect;
  struct Ability *r_ability;
  struct Cost *r_cost;
  struct ReminderText *r_reminder;
  char r_char;
  char *string;
}

%type <r_rule> rule rules
%type <r_recipient> recipient
%type <r_effect> effect
%type <r_cost> cost_list cost sacrifice discard mana
%type <r_ability> abilities_list ability keyword_ability static_ability
%type <r_reminder> reminder_text
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

abilities_list: abilities_list SEMICOLON ability NEWLINE
              {
                //TODO: ?
                $1->next = $3;
                $3->prev = $1;
                $$ = $3;
              }
              | ability NEWLINE
              {
                $$ = $1;
              }
              ;

ability: effect DOT
       {
         /* spell ability */
         $$ = ability_create_spell($1);
       }
       | keyword_ability
       {
        $$ = $1;
       }
       | static_ability
       {
         /* static ability */
         $$ = $1;
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

keyword_ability: A_KEYWORD
               {
                 $$ = ability_create_keyword($1);
               }
               | keyword_ability mana
               {
                 ability_add_cost($1, $2);
                 $$ = $1;
               }
               | keyword_ability '(' reminder_text DOT ')'
               | keyword_ability '(' reminder_text ')'
               {
                 ability_add_reminder_text($$, $3);
               }
               | keyword_ability COMMA keyword_ability
               {
                 $1->next = $3;
                 $3->prev = $1;
                 $$ = $3;
               }
               ;

reminder_text: ability
             {
               $$ = reminder_text_create_ability($1);
             }
             ;

static_ability: recipient T_CAN T_BLOCK recipient
              {
                $$ = ability_create_static_can_block($4);
              }
              | static_ability COMMA static_ability
              {
                    $1->next = $3;
                    $3->prev = $1;
                    $$ = $3;
              }
              ;

cost_list: cost
         {
           $$ = $1;
         }
         | cost_list COMMA cost
         {
           $1->next = $3;
           $3->prev = $1;
           $$ = $1;
         }
         ;

cost: sacrifice
    | discard
    {
      // TODO
      $$ = $1;
    }
    | mana
    {
      $$ = $1;
    }
    ;

sacrifice: SACRIFICE recipient
         {
          $$ = cost_create_sacrifice($2);
         }
         ;

discard: DISCARD recipient
       {
         $$ = cost_create_discard($2);
       }
       ;

mana: MANA_COLOR
    {
      $$ = cost_create_mana($1);
    }
    ;


effect: DESTROY recipient
      {
        $$ = effect_create_destroy($2);
      }
      | DRAW 'a' RECIPIENT /* TODO: "a card" */
      {
        $$ = effect_create_draw(1);
      }
      ;

recipient: TARGET RECIPIENT
         {
           $$ = recipient_create(RECIPIENT_TARGET, $2);
         }
         | RECIPIENT
         {
           $$ = recipient_create(RECIPIENT_SIMPLE, $1);
         }
         | THIS RECIPIENT
         {
           $$ = recipient_create(RECIPIENT_SELF, $2);
         }
         | 'a' RECIPIENT
         {
           $$ = recipient_create(RECIPIENT_SIMPLE, $2);
         }
         | recipient T_WITH keyword_ability
         {
           recipient_add_ability($1, $3);
           $$ = $1;
         }
         ;

%%

int yyerror(struct Card *card, char *msg)
{
  return 1; //fprintf(stderr, "YACC: %s.\n", msg);
}
