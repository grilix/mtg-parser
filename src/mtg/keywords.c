#include <stdlib.h>
#include <string.h>

#include "ability.h"

const char *spellAbilities[] = {
  // Others
  //"Epic", // triggered
  "Awaken", // static and triggered
  "Ascend",

  NULL
};

const char *activatedAbilities[] = {
  // Evergreen
  "Equip",

  // Others
  "Cycling",
  "Ninjutsu",
  "Transmute",
  "Forecast",
  "Aura Swap",
  "Fortify",
  "Transfigure",
  "Reinforce",
  "Unearth",
  "Level Up",
  "Scavenge",
  "Outlast",
  "Crew",
  "Embalm",
  "Eternalize",

  NULL
};

const char *evasionAbilities[] = {
  // Evergreen
  "Flying",

  // Others
  "Intimidate",
  "Landwalk",
  "Shadow",
  "Horsemanship",
  "Fear",
  "Menace",
  "Skulk",

  NULL
};

const char *triggeredAbilities[] = {
  // Others
  "Rampage",
  "Cumulative Upkeep",
  "Flanking",
  "Echo",
  "Madness", // Madness represents a static ability and a triggered ability
  "Provoke",
  "Storm",
  "Modular", // Modular represents a static ability and a triggered ability
  "Bushido",
  "Soulshift",
  "Epic", // Epic represents two spell abilities and a triggered ability
  "Haunt",
  "Replicate", // Replicate represents a static ability and a triggered ability
  "Graft", // Graft represents a static ability and a triggered ability
  "Ripple",
  "Vanishing", // Vanishing represents three abilities
  "Frenzy",
  "Gravestorm",
  "Poisonous",
  "Champion", // Champion represents two triggered abilities
  "Evoke", // Evoke represents a static ability and a triggered ability
  "Hideaway", // Hideaway represents a static ability and a triggered ability
  "Conspire", // Conspire represents a static ability and a triggered ability
  "Persist",
  "Exalted",
  "Cascade",
  "Annihilator",
  "Battle Cry",
  "Living Weapon",
  "Undying",
  "Soulbond",
  "Evolve",
  "Extort",
  "Dethrone",
  "Prowess",
  "Exploit",
  "Renown",
  "Ingest",
  "Myriad",
  "Mele",
  "Fabricate",
  "Afflict",

  NULL
};

const char *staticAbilities[] = {
  // Evergreen
  "Deathtouch",
  "Defender",
  "Double Strike",
  "Enchant",
  "First Strike",
  "Flash",
  "Haste",
  "Hexproof",
  "Indestructible",
  "Lifelink",
  "Reach",
  "Trample",
  "Vigilance",

  // Others

  "Absorb", // static
  "Affinity", // static
  "Aftermath", // static
  "Amplify", // static
  "Banding", // static
  "Bestow", // static
  "Bloodthirst", // static
  "Buyback", // static
  "Changeling", // characteristic-defining ability
  "Cipher", // spell and static abilities, creates triggered ability
  "Convoke", // static
  "Dash", // three abilities: static, triggered, static
  "Delve", // static
  "Devoid", // characteristic-defining ability
  "Devour", // static
  "Dredge", // static
  "Emerge", // static
  "Entwine", // static
  "Escalate", // static
  "Fading", // ?
  "Flashback", // static
  "Fuse", // static
  "Hidden Agenda", // static
  "Improvise", // static
  "Infect", // static
  "Kicker", // static
  "Landhome",
  "Megamorph",
  "Miracle", // static ability linked to a triggered ability
  "Morph", // static
  "Offering", // static
  "Overload", // static
  "Partner", // rule changing - commander
  "Phasing", // static
  "Protection", // static
  "Prowl", // static
  "Rebound", // static
  "Recover",
  "Retrace", // static
  "Shroud", // static
  "Splice", // static
  "Split Second", // static
  "Substance",
  "Sunburst", // static
  "Surge", // static
  "Suspend", // Suspend represents a static and two triggered abilities
  "Totem Armor", // static
  "Tribute", // static
  "Undaunted", // static
  "Unleash", // static
  "Wither", // static

  NULL
};

#define KEYWORD(name,keyword,X) \
  if (strcmp(name, keyword) >= 0) \
  { X }

  struct MtgAbility *
mtg_ability_evasion_keyword(char *keyword)
{
  // Evergreen
  KEYWORD("Flying", keyword,
      mtg_ability_from_static_keyword(keyword);
      );

  // Others
  /*"Intimidate",*/
  /*"Landwalk",*/
  /*"Shadow",*/
  /*"Horsemanship",*/
  /*"Fear",*/
  /*"Menace",*/
  /*"Skulk",*/
}
