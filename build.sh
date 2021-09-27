#!/bin/bash
SOURCE="src/*"
BIN="bin/a.out"
FLAGS="-Wall -Wextra -ggdb"
g++ $SOURCE -o $BIN  $FLAGS 
