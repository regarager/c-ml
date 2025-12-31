#ifndef LOGISTIC_H
#define LOGISTIC_H

#include "matrix.h"

typedef struct {
  u32 n;
  vector_t w;
  f64 b;
} logistic_t;

logistic_t *make_logr(u32 n);
f64 logr_eval(logistic_t *lr, vector_t x);
void logr_fit(logistic_t *lr, vector_t X, vector_t y, u32 k, u32 epochs,
              f64 alpha);

#endif
