#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linreg.h"
#include "util.h"

double f(double *x) { return x[0] + 2 * x[1] + 3 * x[2] + 4; }

int main() {
  srand(time(NULL));
  LinearRegression lr;
  int n = 3;
  int k = 1000;

  LRInit(&lr, n);

  double *X = (double *)calloc(n * k, sizeof(double));
  double *y = (double *)calloc(k, sizeof(double));

  double *x_test = (double *)calloc(n, sizeof(double));
  init_random(x_test, 3);

  double y_pred = LREval(&lr, x_test);
  printf("y_pred: %f, y: %f\n", y_pred, f(x_test));

  for (int i = 0; i < k; i++) {
    init_random(X + i * n, n);

    y[i] = f(X + i * n);
  }

  LRFit(&lr, X, y, k, 10000, 0.01);

  y_pred = LREval(&lr, x_test);
  printf("y_pred: %f, y: %f\n", y_pred, f(x_test));
}
