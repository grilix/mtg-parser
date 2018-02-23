#include <stdio.h>
#include <CUnit/CUnit.h>

#include "../../src/mtg/card.h"

  static void
test_mtg_card_init()
{
  struct MtgCard *card = mtg_card_init();

  CU_ASSERT_PTR_NOT_NULL(card);
  CU_ASSERT_PTR_NULL(card->last_rule);

  mtg_card_free(card);
}

  static void
test_mtg_card_add_rule()
{
  struct MtgCard *card = mtg_card_init();
  struct MtgRule *rule = mtg_rule_init();

  mtg_card_add_rule(card, rule);
  CU_ASSERT_PTR_NOT_NULL(card->last_rule);
  CU_ASSERT_PTR_EQUAL(card->last_rule, rule);
  CU_ASSERT_PTR_NULL(card->last_rule->prev);

  mtg_card_free(card);
}

  static int
init_suite() { return 0; }

  static int
clean_suite() { return 0; }

  extern int
setup_card_suite()
{
  CU_pSuite pSuite = CU_add_suite("MtgCard", init_suite, clean_suite);

  if (pSuite == NULL)
    return CU_get_error();

  if (CU_add_test(pSuite, "mtg_card_init()", test_mtg_card_init) == NULL)
    return CU_get_error();

  if (
    CU_add_test(pSuite, "mtg_card_add_rule()", test_mtg_card_add_rule) == NULL
  )
    return CU_get_error();

  return 0;
}
