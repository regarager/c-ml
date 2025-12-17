#ifndef UTIL_H
#define UTIL_H

#include "types.h"

double rand_float();
void init_random(vec src, int n);
void map(vec src, int n, double (*)(double x, int index));
vec vector(int n);

#endif
