#include <stdio.h>
#include <CUnit/CUnit.h>

#include "test_mtg_ability.h"
#include "../../src/mtg/ability.h"

  static void
test_create_spell()
{
  struct MtgEffect *effect = mtg_effect_create_draw(1);
  struct MtgAbility *ability = mtg_ability_create_spell(effect);

  CU_ASSERT_PTR_NOT_NULL(ability);

  mtg_ability_free(ability);
}

  static int
init_suite()
{
  return 0;
}

  static int
clean_suite()
{
  return 0;
}

  extern int
setup_ability_suite()
{
  CU_pSuite pSuite = CU_add_suite("MtgAbility", init_suite, clean_suite);

  if (pSuite == NULL)
    return CU_get_error();

  if (CU_add_test(pSuite, "test_create_spell()", test_create_spell) == NULL)
    return CU_get_error();

  return 0;
}
