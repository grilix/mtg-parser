#include <stdio.h>
#include <CUnit/CUnit.h>

#include "../../src/mtg/ability.h"
#include "../tests.h"

  static void
test_create_spell()
{
  struct MtgEffect *effect = mtg_effect_create_draw(1);
  struct MtgAbility *ability = mtg_ability_create_spell(effect);

  CU_ASSERT_PTR_NOT_NULL_FATAL(ability);

  mtg_ability_free(ability);
}

  static void
test_ability_from_static_keyword_invalid()
{
  struct MtgAbility *ability = mtg_ability_from_static_keyword(
      "NOT A VALID KEYWORD");

  CU_ASSERT_PTR_NULL(ability);
}

  static void
test_ability_from_static_keyword()
{
  struct MtgAbility *ability = mtg_ability_from_static_keyword("Reach");

  CU_ASSERT_PTR_NOT_NULL_FATAL(ability);
  CU_ASSERT_EQUAL(ability->type, ABILITY_STATIC);

  mtg_ability_free(ability);
}

  extern int
setup_ability_suite()
{
  CU_pSuite pSuite = CU_add_suite("MtgAbility", NULL, NULL);

  if (pSuite == NULL)
    return CU_get_error();

  ADD_TEST(pSuite, "mtg_ability_create_spell()", test_create_spell);
  ADD_TEST(pSuite, "mtg_ability_from_static_keyword(): When keyword is valid",
           test_ability_from_static_keyword);
  ADD_TEST(pSuite,
          "mtg_ability_from_static_keyword(): When keyword is invalid",
           test_ability_from_static_keyword_invalid);

  return 0;
}
