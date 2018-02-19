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
    -> Card(Rule(Ability(Effect(destroy:Objective(target:creature)))))

    * Destroy target artifact.
    -> Card(Rule(Ability(Effect(destroy:Objective(target:artifact)))))

    * Reach
    -> Card(Rule(Ability(Reach)))

    * Flying, haste
    -> Card(Rule(Ability(Flying),Ability(haste)))

    * Reach (This creature can block creatures with flying.)
    Syntax error:
    1:Reach (

    * Destroy target creature with flying.
    Syntax error:
    1:Destroy target creature w

## TODO

- Implement it.
- Test it (with actual tests).
- Feed it with a set of real card texts.
