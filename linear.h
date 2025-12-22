#ifndef LINEAR_H
#define LINEAR_H

#include "matrix.h"

typedef struct {
  int n;
  vec w;
  double b;
} linear_t;

linear_t *linr(int n);
double linr_eval(linear_t *lr, vec x);
double linr_cost(linear_t *lr, vec x, double y);
void linr_fit(linear_t *lr, vec X, vec y, int k, int epochs, double alpha);

#endif
