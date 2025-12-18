#ifndef UTIL_H
#define UTIL_H

#include "matrix.h"

double urandom_float();
double random_float();
void init_random(vec src, int n);
void map(vec src, int n, double (*)(double x));
void mapi(vec src, int n, double (*)(double x, int index));
vec vector(int n);
vec vec_from(int n, ...);
Matrix *matrix(int m, int n);
Matrix *matrix_from(int m, int n, ...);
Matrix *matrix_vec(vec v, int n);

#endif
