#ifndef LINREG_H
#define LINREG_H

#include "util.h"

typedef struct {
  int n;
  vec w;
  double b;
} LinearRegression;

void LRInit(LinearRegression *lr, int n);
double LREval(LinearRegression *lr, vec x);
double LRCost(LinearRegression *lr, vec x, double y);
void LRFit(LinearRegression *lr, vec X, vec y, int k, int epochs,
             double alpha);

#endif
