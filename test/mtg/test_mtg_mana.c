#include <stdio.h>
#include <CUnit/CUnit.h>

#include "../../src/mtg/mana.h"

  static void
test_mtg_mana_create_from_string_ptrs()
{
  struct MtgMana *mana = mtg_mana_create_from_string("{10}");

  CU_ASSERT_PTR_NOT_NULL(mana);
  CU_ASSERT_PTR_NULL(mana->prev);
  CU_ASSERT_PTR_NULL(mana->next);
  mtg_mana_free(mana);
}

  static void
test_mtg_mana_create_from_string_colorless()
{
  struct MtgMana *mana = mtg_mana_create_from_string("{10}");

  CU_ASSERT_PTR_NOT_NULL(mana);
  CU_ASSERT_EQUAL(mana->amount, 10);
  CU_ASSERT_EQUAL(mana->type & MTG_MANA_COLORLESS, MTG_MANA_COLORLESS);
  CU_ASSERT_NOT_EQUAL(mana->type & MTG_MANA_WHITE, MTG_MANA_WHITE);
  CU_ASSERT_NOT_EQUAL(mana->type & MTG_MANA_BLUE, MTG_MANA_BLUE);
  CU_ASSERT_NOT_EQUAL(mana->type & MTG_MANA_BLACK, MTG_MANA_BLACK);
  CU_ASSERT_NOT_EQUAL(mana->type & MTG_MANA_RED, MTG_MANA_RED);
  CU_ASSERT_NOT_EQUAL(mana->type & MTG_MANA_GREEN, MTG_MANA_GREEN);

  mtg_mana_free(mana);
}

  static void
test_mtg_mana_create_from_string_multicolor()
{
  struct MtgMana *mana = mtg_mana_create_from_string("{R/U}");

  CU_ASSERT_PTR_NOT_NULL(mana);
  CU_ASSERT_NOT_EQUAL(mana->type & MTG_MANA_WHITE, MTG_MANA_WHITE);
  CU_ASSERT_EQUAL(mana->type & MTG_MANA_BLUE, MTG_MANA_BLUE);
  CU_ASSERT_NOT_EQUAL(mana->type & MTG_MANA_BLACK, MTG_MANA_BLACK);
  CU_ASSERT_EQUAL(mana->type & MTG_MANA_RED, MTG_MANA_RED);
  CU_ASSERT_NOT_EQUAL(mana->type & MTG_MANA_GREEN, MTG_MANA_GREEN);

  mtg_mana_free(mana);

  // TODO: Should this create two mana objects?
  mana = mtg_mana_create_from_string("{R}{U}");

  CU_ASSERT_PTR_NOT_NULL(mana);

  CU_ASSERT_NOT_EQUAL(mana->type & MTG_MANA_WHITE, MTG_MANA_WHITE);
  CU_ASSERT_EQUAL(mana->type & MTG_MANA_BLUE, MTG_MANA_BLUE);
  CU_ASSERT_NOT_EQUAL(mana->type & MTG_MANA_BLACK, MTG_MANA_BLACK);
  CU_ASSERT_EQUAL(mana->type & MTG_MANA_RED, MTG_MANA_RED);
  CU_ASSERT_NOT_EQUAL(mana->type & MTG_MANA_GREEN, MTG_MANA_GREEN);

  mtg_mana_free(mana);
}

  static int
init_suite() { return 0; }

  static int
clean_suite() { return 0; }

  extern int
setup_mana_suite()
{
  CU_pSuite pSuite = CU_add_suite("MtgMana", init_suite, clean_suite);

  if (pSuite == NULL)
    return CU_get_error();

  if (CU_add_test(pSuite,
                  "mtg_mana_create_from_string(): List initialization",
                  test_mtg_mana_create_from_string_ptrs) == NULL)
    return CU_get_error();

  if (CU_add_test(pSuite,
                  "mtg_mana_create_from_string(): Colorless mana",
                  test_mtg_mana_create_from_string_colorless) == NULL)
    return CU_get_error();

  if (CU_add_test(pSuite,
                  "mtg_mana_create_from_string(): Multicolor mana",
                  test_mtg_mana_create_from_string_multicolor) == NULL)
    return CU_get_error();

  return 0;
}
