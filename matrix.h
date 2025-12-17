#ifndef MATRIX_H
#define MATRIX_H

#include "types.h"

double dot_product(vec a, vec b, int n);
void matmul(vec A, vec B, vec C, int n, int m, int p);

#endif
