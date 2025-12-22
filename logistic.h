#ifndef LOGISTIC_H
#define LOGISTIC_H

#include "matrix.h"

typedef struct {
  int n;
  vec w;
  double b;
} logistic_t;

logistic_t *logr(int n);
double logr_eval(logistic_t *lr, vec x);
double logr_cost(logistic_t *lr, vec x, double y);
void logr_fit(logistic_t *lr, vec X, vec y, int k, int epochs, double alpha);

#endif
