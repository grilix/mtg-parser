#!/usr/bin/env bash

test-card() {
  echo "  -> $1"

  echo -e "$1" | ./magic-parser
  echo ""
}

# Some examples to work with:
test-card "Destroy target creature."
test-card "Destroy target artifact."
test-card "Destroy target creature; Destroy target artifact."
test-card "Destroy target creature.\nDestroy target artifact."
