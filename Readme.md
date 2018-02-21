# MTG Parser

An in-progress parser for the MTG card texts in C.

This project is an experiment to see how far we can go trying to parse
Magic cards with a lex program.

There's still no really long term goal for this, but feel free to make
suggestions or recomendations. My C knowledge is pretty bad, so please
let me know if you can help me make the code better.

## Compile

    $ make

## Test

    $ echo "Destroy target creature." | ./magic-parser

Or use the script to automate it:

    $ make && scripts/test.sh

    # ...

    * Destroy target creature.
    -> Card(Rule(Ability(Effect(destroy:Recipient(target:creature)))))

    * Destroy target artifact.
    -> Card(Rule(Ability(Effect(destroy:Recipient(target:artifact)))))

    * Reach
    -> Card(Rule(Ability(Reach)))

    * Flying, haste
    -> Card(Rule(Ability(Flying),Ability(haste)))

    * Reach (This creature can block creatures with flying.)
    -> Card(Rule(Ability(Reach)))

    * Destroy target creature with flying.
    -> Card(Rule(Ability(Effect(destroy:Recipient(target:creature(Ability(flying)))))))

    * Cycling {R} ({R}, Discard this card: Draw a card.)
    -> Card(Rule(Ability(Cost(R),Cycling)))

    * When Gravedigger enters the battlefield, you may return target creature card from your graveyard to your hand.
    Syntax error:
    1:W


## TODO

- Implement it.
- Test it (with actual tests).
- Feed it with a set of real card texts.
