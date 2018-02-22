#ifndef MANA_H
#define MANA_H

enum MtgManaType
{
  MTG_MANA_COLORLESS = 1,
  MTG_MANA_WHITE = 2,
  MTG_MANA_BLUE = 4,
  MTG_MANA_BLACK = 8,
  MTG_MANA_RED = 16,
  MTG_MANA_GREEN = 32,
  MTG_MANA_X = 64
};

struct MtgMana
{
  enum MtgManaType type;
  int amount;

  struct MtgMana *prev;
  struct MtgMana *next;
};

  extern struct MtgMana *
mtg_mana_create_from_string(char *color);

  extern void
mtg_mana_free(struct MtgMana *mana);

#endif
