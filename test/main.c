#include <CUnit/Basic.h>

extern int setup_card_suite();
extern int setup_ability_suite();
extern int setup_mana_suite();
extern int setup_input_suite();
extern int setup_common_suite();

int load_suite_result(int result, char *name)
{
  if (result == CUE_SUCCESS)
    return 1;

  fprintf(stderr, "Error initializing suite for: %s\n", name);
  CU_cleanup_registry();

  return 0;
}

int main()
{
  CU_pSuite pSuite = NULL;

  if (CU_initialize_registry() != CUE_SUCCESS)
  {
    fprintf(stderr, "Can't initialize the registry.\n");
    return CU_get_error();
  }

  if (!load_suite_result(setup_common_suite(), "Common"))
    return CU_get_error();

  if (!load_suite_result(setup_card_suite(), "MtgCard"))
    return CU_get_error();

  if (!load_suite_result(setup_ability_suite(), "MtgAbility"))
    return CU_get_error();

  if (!load_suite_result(setup_mana_suite(), "MtgMana"))
    return CU_get_error();

  if (!load_suite_result(setup_input_suite(), "Input"))
    return CU_get_error();

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

  CU_cleanup_registry();
  return CU_get_error();
}
