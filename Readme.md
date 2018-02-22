# MTG Parser

An in-progress parser for the MTG card texts in C.

This project is an experiment to see how far we can go trying to parse
Magic cards with a lex program.

There's still no really long term goal for this, but feel free to make
suggestions or recomendations. My C knowledge is pretty bad, so please
let me know if you can help me make the code better.

## Compile

    $ make

## Testing

  Testing is being done with
  [CUnit](http://cunit.sourceforge.net/doc/index.html).

  On Gentoo: `emerge dev-util/cunit`.
  On Fedora: `dnf install CUnit-devel` (probably).

  Then just:

    $ make test

## Text support

The current output for `scripts/test.sh` is:

    * Destroy target creature.
    -> Card(Rule(Ability(Effect(destroy:Recipient(target:creature)))))

    * Destroy target artifact.
    -> Card(Rule(Ability(Effect(destroy:Recipient(target:artifact)))))

    * Reach
    -> Card(Rule(Ability(Reach)))

    * Flying, haste
    -> Card(Rule(Ability(Flying),Ability(haste)))

    * {X}{2}{U}: Draw a card.
    -> Card(Rule(Ability(Cost(Mana(X),Mana(2),Mana(U)),Effect(draw:1))))

    * Reach (This creature can block creatures with flying.)
    -> Card(Rule(Ability(Reach)))

    * Destroy target creature with flying.
    -> Card(Rule(Ability(Effect(destroy:Recipient(target:creature(Ability(flying)))))))

    * Cycling {R} ({R}, Discard this card: Draw a card.)
    -> Card(Rule(Ability(Cost(Mana(R)),Cycling)))

    * {1}{W}, {T}, Discard a card: Put a 1/1 white Human Soldier creature token onto the battlefield.
    Syntax error:
    1:{1}{W}, {T}, Discard a card: P

    * When Gravedigger enters the battlefield, you may return target creature card from your graveyard to your hand.
    Syntax error:
    1:W

## TODO

- Implement it.
- Test it (with actual tests).
- Feed it with a set of real card texts.

## More information

Here are some links to have around:

- http://mtg.wikia.com/wiki/Target
- http://mtg.wikia.com/wiki/Category:Mechanics
- http://mtg.wikia.com/wiki/Ability_Words
