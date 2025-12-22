#!/usr/bin/env bash

entry="${1:-main.c}"

FILES="$entry linear.c logistic.c matrix.c neural.c util.c"

set -e
mkdir -p build
gcc -Wall -Wextra -lm -g -o build/main $FILES
./build/main
