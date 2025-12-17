#ifndef UTIL_H
#define UTIL_H

double rand_float();
void init_random(double *src, int n);
void map(double *src, int n, double (*) (double x, int index));

#endif
