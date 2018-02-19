#!/usr/bin/env bash

e() {
  COLOR=$1
  shift
  echo -en "\e[1;${COLOR}m$@\e[0;0m"
}

test-card() {
  echo ""

  RESULT=$(echo -e "$1" | ./magic-parser 2>&1)

  if [ $? == 0 ]; then
    echo -e "$(e 32 "*") $(e 1 $1)"
    echo " -> $(e 34 "${RESULT}")"
  else
    echo -e "$(e 31 "*") $(e 1 $1)"
    echo " $(e 35 "${RESULT}")"
  fi
}

# Some easy examples
test-card "Destroy target creature."
test-card "Destroy target artifact."
#test-card "Destroy target creature.\nDestroy target artifact."
test-card "Reach"
test-card "Flying, haste"

### Some real world examples

## Static abilities
# Giant Spider
test-card "Reach (This creature can block creatures with flying.)"
# Vampire Nighthawk
#test-card "Flying\nDeathtouch (Any amount of damage this deals to a creature is enough to destroy it.)\nLifelink (Damage dealt by this creature also causes you to gain that much life.)"

## Spell abilities
# Divine Veredict
#test-card "Destroy target attacking or blocking creature."
# Wing Snare
test-card "Destroy target creature with flying."
# Rabid Bite
#test-card "Target creature you control deals damage equal to its power to target creature you don't control."
# Stalking Tiger
#test-card "Stalking Tiger can't be blocked by more than one creature."

## Activated abilities
# Druid of the Cowl
#test-card "{T}: Add {G} to your mana pool."

## Combined
# Arborback Stomper
#test-card "Trample (This creature can deal excess combat damage to defending player or planeswalker while attacking.)\nWhen Arborback Stomper enters the battlefield, you gain 5 life."
# Forerunner of Slaughter
#test-card "Devoid (This card has no color.)\n{1}: Target colorless creature gains haste until end of turn."
