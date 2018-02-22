#include "../common.h"
#include "mana.h"

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

  extern void
mtg_mana_free(struct MtgMana *mana)
{
  if (mana->prev != NULL)
    mtg_mana_free(mana->prev);

  free(mana);
}
