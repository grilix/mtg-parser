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

    $ scripts/test.sh
    $ make clean && make && scripts/test.sh

      -> Destroy target creature.
    Card(Rule(Ability(Effect(destroy/Objective(ability/card)->Objective(target/creature)))))

      -> Destroy target artifact.
    Card(Rule(Ability(Effect(destroy/Objective(ability/card)->Objective(target/artifact)))))

      -> Destroy target creature; Destroy target artifact.
    Card(Rule(Ability(Effect(destroy/Objective(ability/card)->Objective(target/creature))),Ability(Effect(destroy/Objective(ability/card)->Objective(target/artifact)))))

      -> Destroy target creature.\nDestroy target artifact.
    YACC: syntax error

## TODO

- Implement it.
- Test it (with actual tests).
- Feed it with a set of real card texts.
