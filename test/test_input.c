#include <stdlib.h>
#include <stdio.h>
#include <CUnit/CUnit.h>

#include "../src/mtg/card.h"
#include "../src/input.h"
#include "tests.h"

#define PARSE(R,S,X) \
  allocate_test_card(); \
  R = parse_string(S); \
  {X} \
  destroy_test_card()

static struct MtgCard *test_card = NULL;

  static int
destroy_test_card(void)
{
  if (test_card == NULL)
    return 0;

  mtg_card_free(test_card);
  test_card = NULL;

  return 0;
}

  static int
allocate_test_card(void)
{
  if (test_card != NULL)
  {
    printf(" >> Warning: Freeing not freed card.\n");
    destroy_test_card();
  }

  test_card = mtg_card_init();

  return 0;
}

  static int
parse_string(char *str)
{
  int parse_result;
  struct Input *in = input_from_str(str);

  in->card = test_card;
  parse_result = perform_parse(in);

  input_destroy(in);

  return parse_result;
}

  static void
test_keyword_abilities()
{
  int result;

  PARSE(result, "Reach\n",
      CU_ASSERT_EQUAL_FATAL(result, 0);
      ASSERT_SINGLE_ITEM(test_card->last_rule);
      ASSERT_SINGLE_ITEM(test_card->last_rule->last_ability);
      );

  // Is a single rule
  PARSE(result, "Flying, haste\n",
      CU_ASSERT_EQUAL_FATAL(result, 0);
      ASSERT_SINGLE_ITEM(test_card->last_rule);
      );

  // The rule contains two abilities
  PARSE(result, "Flying, haste\n",
      ASSERT_LAST_ITEM(test_card->last_rule->last_ability);
      ASSERT_FIRST_ITEM(test_card->last_rule->last_ability->prev);
      CU_ASSERT_PTR_EQUAL(test_card->last_rule->last_ability,
                          test_card->last_rule->last_ability->prev->next);
      );

  PARSE(result, "Cycling {R} ({R}, Discard this card: Draw a card.)\n",
      CU_ASSERT_EQUAL_FATAL(result, 0);
      ASSERT_SINGLE_ITEM(test_card->last_rule);
      ASSERT_SINGLE_ITEM(test_card->last_rule->last_ability);
      );

  // TODO: Is cycling without reminder text even a thing?
  PARSE(result, "Cycling {R}\n",
      CU_ASSERT_EQUAL_FATAL(result, 0);
      ASSERT_SINGLE_ITEM(test_card->last_rule);
      ASSERT_SINGLE_ITEM(test_card->last_rule->last_ability);
      );
}

  static void
test_keyword_abilities_convertion()
{
  int result;

#define PARSE_CONVERTS(S,T) \
  PARSE(result, S, \
      CU_ASSERT_EQUAL_FATAL(result, 0); \
      CU_ASSERT_EQUAL(test_card->last_rule->last_ability->type, T); \
      )

  // Converts both
  PARSE(result, "Flying, haste\n",
      CU_ASSERT_EQUAL(test_card->last_rule->last_ability->type, ABILITY_STATIC);
      CU_ASSERT_EQUAL(test_card->last_rule->last_ability->prev->type,
                      ABILITY_STATIC);
      );

  // Morph is a keyword ability
  // TODO: Morph is not supported
  /*PARSE_CONVERTS(*/
      /*"Morph {1}{U} (You may play this face down as a 2/2 creature for "*/
      /*"Mana 3. Turn it face up any time for its morph cost.)\n",*/
      /*ABILITY_KEYWORD);*/

  PARSE_CONVERTS("Reach\n", ABILITY_STATIC);
  PARSE_CONVERTS("Deathtouch\n", ABILITY_STATIC);
  PARSE_CONVERTS("Flying\n", ABILITY_STATIC);
  PARSE_CONVERTS("Cycling {R} ({R}, Discard this card: Draw a card.)\n",
      ABILITY_ACTIVATED);

#undef PARSE_CONVERTS

}

  static void
test_reminder_texts()
{
  int result;

  // Single rule with single ability
  PARSE(result,
        "Reach (This creature can block creatures with flying.)\n",
      CU_ASSERT_EQUAL_FATAL(result, 0);
      ASSERT_SINGLE_ITEM(test_card->last_rule);
      ASSERT_SINGLE_ITEM(test_card->last_rule->last_ability);
      );

  // Ability has reminder text
  PARSE(result,
        "Reach (This creature can block creatures with flying.)\n",
      CU_ASSERT_PTR_NOT_NULL_FATAL(
        test_card->last_rule->last_ability->reminder_text);
      CU_ASSERT_PTR_NOT_NULL_FATAL(
        test_card->last_rule->last_ability->reminder_text->ability);
      );
}

  static void
test_activated_abilities()
{
  int result;

  PARSE(result, "{X}{2}{U}: Draw a card.\n",
      CU_ASSERT_EQUAL_FATAL(result, 0);
      ASSERT_SINGLE_ITEM(test_card->last_rule);
      ASSERT_SINGLE_ITEM(test_card->last_rule->last_ability);
      );

  PARSE(result, "{X}{2}{U}: Draw a card.\n",
      CU_ASSERT_EQUAL(test_card->last_rule->last_ability->type, ABILITY_ACTIVATED);
      );

  PARSE(result, "{X}{2}{U}: Draw a card.\n",
      CU_ASSERT_PTR_NOT_NULL_FATAL(test_card->last_rule->last_ability->effect);
      CU_ASSERT_EQUAL_FATAL(test_card->last_rule->last_ability->effect->type,
                            MTG_EFFECT_DRAW);
      CU_ASSERT_EQUAL_FATAL(test_card->last_rule->last_ability->effect->count,
                            1);
      );

  PARSE(result, "{X}{2}{U}: Draw a card.\n",
      ASSERT_SINGLE_ITEM(test_card->last_rule->last_ability->cost);
      ASSERT_LAST_ITEM(test_card->last_rule->last_ability->cost->mana);
      // Costs three mana items
      ASSERT_FIRST_ITEM(test_card->last_rule->last_ability->cost->mana->prev->prev);
      CU_ASSERT_PTR_EQUAL(
        test_card->last_rule->last_ability->cost->mana->prev->next,
        test_card->last_rule->last_ability->cost->mana);
      );
}

  static void
test_spell_abilities_parse()
{
  int result;

  PARSE(result, "Destroy target creature.\n",
      CU_ASSERT_EQUAL_FATAL(result, 0);
      CU_ASSERT_EQUAL(test_card->last_rule->last_ability->type, ABILITY_SPELL);
      );

  PARSE(result, "Destroy target artifact.\n",
      CU_ASSERT_EQUAL_FATAL(result, 0);
      CU_ASSERT_EQUAL(test_card->last_rule->last_ability->type, ABILITY_SPELL);
      );

  PARSE(result, "Destroy target creature with flying.\n",
      CU_ASSERT_EQUAL_FATAL(result, 0);
      CU_ASSERT_EQUAL(test_card->last_rule->last_ability->type, ABILITY_SPELL);
      );
}

  static void
test_spell_abilities_structure()
{
  int result;
  PARSE(result, "Destroy target creature.\n",
      ASSERT_SINGLE_ITEM(test_card->last_rule);
      ASSERT_SINGLE_ITEM(test_card->last_rule->last_ability);
      );

  PARSE(result, "Destroy target artifact.\n",
      ASSERT_SINGLE_ITEM(test_card->last_rule);
      ASSERT_SINGLE_ITEM(test_card->last_rule->last_ability);
      );

  PARSE(result, "Destroy target creature with flying.\n",
      ASSERT_SINGLE_ITEM(test_card->last_rule);
      ASSERT_SINGLE_ITEM(test_card->last_rule->last_ability);
      );
}

  static void
test_perform_parse()
{
  int parse_result;
  struct Input *in = input_from_str("Destroy target creature.\n");
  allocate_test_card();

  in->card = test_card;

  parse_result = perform_parse(in);

  CU_ASSERT_EQUAL_FATAL(parse_result, 0);
  CU_ASSERT_PTR_NOT_NULL_FATAL(in->card);

  destroy_test_card();
  input_destroy(in);
}

  extern int
setup_input_suite()
{
  CU_pSuite pSuite = CU_add_suite("Input", NULL, destroy_test_card);

  if (pSuite == NULL)
    return CU_get_error();

  ADD_TEST(pSuite, "perform_parse(): 1/3 Text parsing", test_perform_parse);
  ADD_TEST(pSuite, "perform_parse(): 2/3 Text parsing", test_perform_parse);
  ADD_TEST(pSuite, "perform_parse(): 3/3 Text parsing", test_perform_parse);

  ADD_TEST(pSuite, "perform_parse(): Spell abilites",
           test_spell_abilities_parse);
  ADD_TEST(pSuite, "perform_parse(): Spell abilites structure",
           test_spell_abilities_structure);
  ADD_TEST(pSuite, "perform_parse(): Keyword abilities",
           test_keyword_abilities);
  ADD_TEST(pSuite,
           "perform_parse(): Keyword abilities are converted to correct types",
           test_keyword_abilities_convertion);
  ADD_TEST(pSuite, "perform_parse(): Activated abilities",
           test_activated_abilities);
  ADD_TEST(pSuite, "perform_parse(): Reminder texts", test_reminder_texts);

  return 0;
}
