%{
#include <stdio.h>

#include "../src/input.h"
#include "parse.h"
#include "scan.h"

#include "../src/mtg/card.h"
#include "../src/mtg/rule.h"
#include "../src/mtg/recipient.h"
#include "../src/mtg/effect.h"
#include "../src/mtg/ability.h"
#include "../src/mtg/cost.h"
#include "../src/mtg/reminder_text.h"
#include "../src/mtg/mana.h"
#include "../src/input.h"

void yyerror (yyscan_t *scanner, struct Input *in, char const *msg);
%}

%define api.pure full
%lex-param {void *scanner}
%parse-param {void *scanner}{struct Input *in}

%define parse.trace
%define parse.error verbose

%token <string> NEWLINE SEMICOLON COLON DOT COMMA RECIPIENT TARGET THIS
%token <string> DESTROY SACRIFICE DISCARD DRAW
%token <string> MANA_COLOR MANA_COLORLESS TAP
%token <string> T_CAN T_BLOCK T_WITH
%token <string> A_KEYWORD

%union {
  struct MtgRule *r_rule;
  struct MtgRecipient *r_recipient;
  struct MtgEffect *r_effect;
  struct MtgAbility *r_ability;
  struct MtgCost *r_cost;
  struct MtgReminderText *r_reminder;
  struct MtgMana *r_mana;

  int integer;
  char *string;
}

%type <r_rule> rule rules
%type <r_recipient> recipient
%type <r_effect> effect
%type <r_cost> cost_list cost sacrifice discard
%type <r_ability> abilities_list ability keyword_ability static_ability
%type <r_reminder> reminder_text
%type <r_mana> mana mana_item
%type <string> error

%%
rules
  : rule
  | rules rule
  { }
  ;

rule
  : abilities_list
  {
    mtg_card_add_ability_set(in->card, $1);
  }
  ;

abilities_list
  : abilities_list SEMICOLON ability NEWLINE
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

ability
  : effect DOT
  {
    /* spell ability */
    $$ = mtg_ability_create_spell($1);
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
    $$ = mtg_ability_create_activated($1, $3);
  }
  /*
    | trigger COMMA ability NEWLINE
    {
    $$ = mtg_ability_create_triggered($1, $3);
    }
  */
  ;

keyword_ability
  : A_KEYWORD
  {
    $$ = mtg_ability_create_keyword($1);
  }
  | keyword_ability mana
  {
    mtg_ability_add_cost($1, mtg_cost_create_mana($2));
    $$ = $1;
  }
  | keyword_ability '(' reminder_text DOT ')'
  {
    mtg_ability_add_reminder_text($$, $3);
  }
  | keyword_ability '(' reminder_text ')'
  {
    mtg_ability_add_reminder_text($$, $3);
  }
  | keyword_ability COMMA keyword_ability
  {
    $1->next = $3;
    $3->prev = $1;
    $$ = $3;
  }
  ;

reminder_text
  : ability
  {
    $$ = mtg_reminder_text_create_ability($1);
  }
  ;

static_ability
  : recipient T_CAN T_BLOCK recipient
  {
    $$ = mtg_ability_create_static_can_block($4);
  }
  | static_ability COMMA static_ability
  {
    $1->next = $3;
    $3->prev = $1;
    $$ = $3;
  }
  ;

cost_list
  : cost
  {
    $$ = $1;
  }
  | cost_list COMMA cost
  {
    $1->next = $3;
    $3->prev = $1;
    $$ = $3;
  }
  ;

cost
  : sacrifice
  | discard
  {
    // TODO
    $$ = $1;
  }
  | TAP
  {
    $$ = mtg_cost_create_tap();
  }
  | mana
  {
    $$ = mtg_cost_create_mana($1);
  }
  ;

sacrifice
  : SACRIFICE recipient
  {
  $$ = mtg_cost_create_sacrifice($2);
  }
  ;

discard
  : DISCARD recipient
  {
    $$ = mtg_cost_create_discard($2);
  }
  ;

mana
  : mana_item
  {
    $$ = $1;
  }
  | mana mana_item
  {
    $1->next = $2;
    $2->prev = $1;
    $$ = $2;
  }
  ;

mana_item
  : MANA_COLOR
  {
    $$ = mtg_mana_create_from_string($1);
  }
  | MANA_COLORLESS
  {
    $$ = mtg_mana_create_from_string($1);
  }
  ;


effect
  : DESTROY recipient
  {
    $$ = mtg_effect_create_destroy($2);
  }
  | DRAW 'a' RECIPIENT /* TODO: "a card" */
  {
    $$ = mtg_effect_create_draw(1);
  }
  ;

recipient
  : TARGET RECIPIENT
  {
    $$ = mtg_recipient_create(MTG_RECIPIENT_TARGET, $2);
  }
  | RECIPIENT
  {
    $$ = mtg_recipient_create(MTG_RECIPIENT_SIMPLE, $1);
  }
  | THIS RECIPIENT
  {
    $$ = mtg_recipient_create(MTG_RECIPIENT_SELF, $2);
  }
  | 'a' RECIPIENT
  {
    $$ = mtg_recipient_create(MTG_RECIPIENT_SIMPLE, $2);
  }
  | recipient T_WITH keyword_ability
  {
    mtg_recipient_add_ability($1, $3);
    $$ = $1;
  }
  ;

%%

void yyerror (yyscan_t *locp, struct Input *in, char const *msg)
{
  return; //fprintf(stderr, "YACC: %s.\n", msg);
}
