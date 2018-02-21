#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>

#define START(T) \
  printf("[D] %s: start.\n", T)

#define DEBUG(T) \
  printf("[D] %s.\n", T)

#define DONE(T) \
  printf("[D] %s: done.\n", T)

// These helpers are mainly for remembering, I might remove them later.
// Or not.

// INIT_PTR(struct Type, var_name);
#define INIT_PTR(T,N) \
  T * N = (T *) malloc(sizeof(T))

// COPY_STR(source, destination);
#define COPY_STR(S,D) \
  D = malloc(strlen(S) + 1); \
  strcpy(D, S); D[strlen(S)] = '\0'

// APPEND(last_item, item);
#define APPEND(L,I) \
  if (L != NULL) \
  { \
    L->next = I; \
    I->prev = L; \
  } \
  else \
    I->prev = NULL; \
  L = I;

#endif
