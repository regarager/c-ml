#ifndef LINEAR_H
#define LINEAR_H

#include "matrix.h"

typedef struct {
  int n;
  vector_t w;
  double b;
} linear_t;

linear_t *linr(int n);
double linr_eval(linear_t *lr, vector_t x);
double linr_cost(linear_t *lr, vector_t x, double y);
void linr_fit(linear_t *lr, vector_t X, vector_t y, int k, int epochs,
              double alpha);

#endif
