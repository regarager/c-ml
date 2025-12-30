#ifndef LINEAR_H
#define LINEAR_H

#include "matrix.h"

typedef struct {
  u32 n;
  vector_t w;
  f64 b;
} linear_t;

linear_t *linr(u32 n);
double linr_eval(linear_t *lr, vector_t x);
void linr_fit(linear_t *lr, vector_t X, vector_t y, u32 k, u32 epochs,
              f64 alpha);

#endif
