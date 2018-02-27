#ifndef TESTS_H
#define TESTS_H

#define ADD_TEST(suite,S,F) \
  if (CU_add_test(suite, S, F) == NULL) \
    return CU_get_error()

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

#endif
