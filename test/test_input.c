#include <stdio.h>
#include <CUnit/CUnit.h>

#include "../src/input.h"

#define ADD_TEST(S,F) \
  if (CU_add_test(pSuite, S, F) == NULL) \
    return CU_get_error()

#define PARSE(C,R,S,X) \
  C = mtg_card_init(); \
  R = parse_string(C,S); \
  {X} \
  mtg_card_free(C)

#define ASSERT_SINGLE_ITEM(P) \
  CU_ASSERT_PTR_NOT_NULL_FATAL(P); \
  CU_ASSERT_PTR_NULL_FATAL(P->prev); \
  CU_ASSERT_PTR_NULL_FATAL(P->next)

#define ASSERT_LAST_ITEM(P) \
  CU_ASSERT_PTR_NOT_NULL_FATAL(P); \
  CU_ASSERT_PTR_NOT_NULL_FATAL(P->prev); \
  CU_ASSERT_PTR_NULL_FATAL(P->next)

#define ASSERT_FIRST_ITEM(P) \
  CU_ASSERT_PTR_NOT_NULL_FATAL(P); \
  CU_ASSERT_PTR_NULL_FATAL(P->prev); \
  CU_ASSERT_PTR_NOT_NULL_FATAL(P->next)

  static int
parse_string(struct MtgCard *card, char *str)
{
  int parse_result;
  struct Input *in = input_from_str(str);

  in->card = card;
  parse_result = perform_parse(in);

  input_destroy(in);

  return parse_result;
}

  static void
test_keyword_abilities()
{
  struct MtgCard *card;
  int result;

  PARSE(card, result, "Reach\n",
      CU_ASSERT_EQUAL_FATAL(result, 0);
      ASSERT_SINGLE_ITEM(card->last_rule);
      ASSERT_SINGLE_ITEM(card->last_rule->last_ability);
      );

  PARSE(card, result, "Reach\n",
      CU_ASSERT_EQUAL(card->last_rule->last_ability->type, ABILITY_KEYWORD);
      );

  // Is a single rule
  PARSE(card, result, "Flying, haste\n",
      CU_ASSERT_EQUAL_FATAL(result, 0);
      ASSERT_SINGLE_ITEM(card->last_rule);
      );

  // The rule contains two abilities
  PARSE(card, result, "Flying, haste\n",
      ASSERT_LAST_ITEM(card->last_rule->last_ability);
      ASSERT_FIRST_ITEM(card->last_rule->last_ability->prev);
      CU_ASSERT_PTR_EQUAL(card->last_rule->last_ability,
                          card->last_rule->last_ability->prev->next);
      );

  // Both abilities are keyword abilities
  PARSE(card, result, "Flying, haste\n",
      CU_ASSERT_EQUAL(card->last_rule->last_ability->type, ABILITY_KEYWORD);
      );
  PARSE(card, result, "Flying, haste\n",
      CU_ASSERT_EQUAL(card->last_rule->last_ability->prev->type, ABILITY_KEYWORD);
      );
}

  static void
test_reminder_texts()
{
  struct MtgCard *card;
  int result;

  // Single rule with single ability
  PARSE(card, result, "Reach (This creature can block creatures with flying.)\n",
      CU_ASSERT_EQUAL_FATAL(result, 0);
      ASSERT_SINGLE_ITEM(card->last_rule);
      ASSERT_SINGLE_ITEM(card->last_rule->last_ability);
      );

  // Ability has reminder text
  PARSE(card, result, "Reach (This creature can block creatures with flying.)\n",
      CU_ASSERT_PTR_NOT_NULL_FATAL(card->last_rule->last_ability->reminder_text);
      CU_ASSERT_PTR_NOT_NULL_FATAL(card->last_rule->last_ability->reminder_text->ability);
      );
}

  static void
test_activated_abilities()
{
  struct MtgCard *card;
  int result;

  PARSE(card, result, "{X}{2}{U}: Draw a card.\n",
      CU_ASSERT_EQUAL_FATAL(result, 0);
      ASSERT_SINGLE_ITEM(card->last_rule);
      ASSERT_SINGLE_ITEM(card->last_rule->last_ability);
      );

  PARSE(card, result, "{X}{2}{U}: Draw a card.\n",
      CU_ASSERT_EQUAL(card->last_rule->last_ability->type, ABILITY_ACTIVATED);
      );

  PARSE(card, result, "{X}{2}{U}: Draw a card.\n",
      CU_ASSERT_PTR_NOT_NULL_FATAL(card->last_rule->last_ability->effect);
      CU_ASSERT_EQUAL_FATAL(card->last_rule->last_ability->effect->type,
                            MTG_EFFECT_DRAW);
      CU_ASSERT_EQUAL_FATAL(card->last_rule->last_ability->effect->count,
                            1);
      );

}

  static void
test_spell_abilities()
{
  struct MtgCard *card;
  int result;

  PARSE(card, result, "Destroy target creature.\n",
      CU_ASSERT_EQUAL(result, 0);
      ASSERT_SINGLE_ITEM(card->last_rule);
      ASSERT_SINGLE_ITEM(card->last_rule->last_ability);
      );

  PARSE(card, result, "Destroy target artifact.\n",
      CU_ASSERT_EQUAL(result, 0);
      ASSERT_SINGLE_ITEM(card->last_rule);
      ASSERT_SINGLE_ITEM(card->last_rule->last_ability);
      );

  PARSE(card, result, "Destroy target artifact.\n",
      CU_ASSERT_EQUAL(card->last_rule->last_ability->type, ABILITY_SPELL);
      );
}

  static void
test_perform_parse()
{
  int parse_result;
  struct Input *in = input_from_str("Destroy target creature.\n");
  in->card = mtg_card_init();

  parse_result = perform_parse(in);

  CU_ASSERT_PTR_NOT_NULL(in->card);
  CU_ASSERT_EQUAL(parse_result, 0);

  mtg_card_free(in->card);
  input_destroy(in);
}

  static int
init_suite() { return 0; }

  static int
clean_suite() { return 0; }

  extern int
setup_input_suite()
{
  CU_pSuite pSuite = CU_add_suite("Input", init_suite, clean_suite);

  if (pSuite == NULL)
    return CU_get_error();

  ADD_TEST("perform_parse(): Text parsing", test_perform_parse);
  ADD_TEST("perform_parse(): Spell abilites", test_spell_abilities);
  ADD_TEST("perform_parse(): Keyword abilities", test_keyword_abilities);
  ADD_TEST("perform_parse(): Activated abilities", test_activated_abilities);
  ADD_TEST("perform_parse(): Reminder texts", test_reminder_texts);

  return 0;
}
