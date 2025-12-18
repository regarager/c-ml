#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linreg.h"
#include "util.h"

double f(vec x) { return x[0] + 2 * x[1] + 3 * x[2] + 4; }

int main() {
  srand(time(NULL));
  LinearRegression lr;
  int n = 3;
  int k = 1000;

  LRInit(&lr, n);

  vec X = vector(n * k);
  vec y = vector(k);

  vec x_test = vector(n);
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
