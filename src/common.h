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

#define INIT_PTR(T,N) \
  T * N = (T *) malloc(sizeof(T))

#define COPY_STR(S,D) \
  D = malloc(sizeof(char) * strlen(S)); \
  strcpy(D, S);

#endif
