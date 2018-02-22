#include <stdio.h>
#include <stdlib.h>
#include "mana.h"
#include "../common.h"

  static struct MtgMana *
init_mana(void)
{
  INIT_PTR(struct MtgMana, mana);

  mana->prev = NULL;
  mana->next = NULL;

  return mana;
}

  extern struct MtgMana *
mtg_mana_create_from_string(char *text)
{
  struct MtgMana *mana = init_mana();
  enum MtgManaType type = 0;
  int c, amount = 0;

  while (c = *text++)
  {
    switch (c)
    {
      case '{':
      case '}': break;
      case 'W': type = type | MTG_MANA_WHITE; break;
      case 'U': type = type | MTG_MANA_BLUE; break;
      case 'B': type = type | MTG_MANA_BLACK; break;
      case 'R': type = type | MTG_MANA_RED; break;
      case 'G': type = type | MTG_MANA_GREEN; break;
      case 'X':
        type = type | MTG_MANA_COLORLESS | MTG_MANA_X;
        break;
      default:
        // TODO: This code is not portable. Fix it.
        if ((c >= '0') && (c <= '9'))
        {
          type = type | MTG_MANA_COLORLESS;

          amount = (amount * 10) + (c - '0');
        }
        break;
    }
  }

  mana->type = type;
  mana->amount = amount;

  return mana;
}

  static int
mana_is(struct MtgMana *mana, enum MtgManaType type)
{
  return (mana->type & type) == type;
}

  extern void
mtg_mana_debug(struct MtgMana *mana)
{
  if (mana->prev != NULL)
  {
    mtg_mana_debug(mana->prev);
    printf(",");
  }

  printf("Mana(");
  if (mana_is(mana, MTG_MANA_COLORLESS))
  {
    if (mana_is(mana, MTG_MANA_X))
      printf("X");
    else
      printf("%d", mana->amount);
  }
  else
  {
    if (mana_is(mana, MTG_MANA_WHITE))
      printf("W");
    if (mana_is(mana, MTG_MANA_BLUE))
      printf("U");
    if (mana_is(mana, MTG_MANA_BLACK))
      printf("B");
    if (mana_is(mana, MTG_MANA_RED))
      printf("R");
    if (mana_is(mana, MTG_MANA_GREEN))
      printf("G");
  }
  printf(")");
}

  extern void
mtg_mana_free(struct MtgMana *mana)
{
  if (mana->prev != NULL)
    mtg_mana_free(mana->prev);

  free(mana);
}
