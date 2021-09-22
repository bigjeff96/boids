#!/bin/bash
SOURCE="src/*"
BIN="bin/a.out"
g++ $SOURCE -o $BIN -Wall -Wextra -pedantic -ggdb 
# echo "Output of executable: "
# ./test
