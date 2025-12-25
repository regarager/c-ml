#ifndef LOGISTIC_H
#define LOGISTIC_H

#include "matrix.h"

typedef struct {
  int n;
  vector_t w;
  double b;
} logistic_t;

logistic_t *logr(int n);
double logr_eval(logistic_t *lr, vector_t x);
double logr_cost(logistic_t *lr, vector_t x, double y);
void logr_fit(logistic_t *lr, vector_t X, vector_t y, int k, int epochs,
              double alpha);

#endif
