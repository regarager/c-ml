#!/usr/bin/env bash

FILES="main.c linalg.c linreg.c util.c"

set -e
gcc -Wall -Wextra $FILES -o run
./run
rm ./run
