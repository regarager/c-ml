#ifndef LINREG_H
#define LINREG_H

typedef struct {
  int n;
  double *w;
  double b;
} LinearRegression;

void LRInit(LinearRegression *lr, int n);
double LREval(LinearRegression *lr, double *x);
double LRCost(LinearRegression *lr, double *x, double y);
void LRFit(LinearRegression *lr, double *X, double *y, int k, int epochs,
             double alpha);

#endif
