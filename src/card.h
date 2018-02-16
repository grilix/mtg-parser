#ifndef CARD_H
#define CARD_H

#include "rules.h"

struct st_card
{
  struct st_rule *rule_list;
};

  struct st_card *
init_card(void);

  void
add_card_empty_rule(struct st_card *card);

  void
add_card_rule(struct st_card *card, struct st_rule *rule);

  void
debug_card(struct st_card *card);

  void
free_card(struct st_card *card);

#endif
