#include <stdio.h>
#include <CUnit/CUnit.h>

#include "../src/common.h"

#include "tests.h"

const char *items_list[] = {
  "ab",
  "cd",
  "ef",
  "gh",
  "ij",
  "kl",
  "mn",
  NULL
};

  static void
test_search_string_null()
{
  CU_ASSERT_EQUAL(search_string(items_list, NULL), -1);
}

  static void
test_search_string_exists()
{
  CU_ASSERT_EQUAL(search_string(items_list, "ab"), 0);
  CU_ASSERT_EQUAL(search_string(items_list, "ef"), 2);
  CU_ASSERT_EQUAL(search_string(items_list, "kl"), 5);
}

  static void
test_search_string_dont_exists()
{
  CU_ASSERT_EQUAL(search_string(items_list, "abc"), -1);
  CU_ASSERT_EQUAL(search_string(items_list, "efg"), -1);
}

  extern int
setup_common_suite()
{
  CU_pSuite pSuite = CU_add_suite("Common routines", NULL, NULL);

  if (pSuite == NULL)
    return CU_get_error();

  ADD_TEST(pSuite, "search_string(): When search is NULL",
           test_search_string_null);
  ADD_TEST(pSuite, "search_string(): When string exists",
           test_search_string_exists);
  ADD_TEST(pSuite, "search_string(): When string does not exist",
           test_search_string_dont_exists);

  return 0;
}
