#include <string.h>

#include "common.h"

// FIXME: This is probably far from good, but it works for now.
  extern int
search_string(const char *list[], char *string)
{
  int pos = 0;

  if (string == NULL)
    return -1;

  do {
    if (list[pos] == NULL)
      return -1;

    if (strcmp(string, list[pos]) == 0)
      return pos;

    pos++;
  } while (1);

  return -1;
}
