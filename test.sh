#!/usr/bin/env bash

FILES="test.c matrix.c linreg.c util.c"

set -e
gcc -Wall -Wextra $FILES -o run
./run
rm ./run
