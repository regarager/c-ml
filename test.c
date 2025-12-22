#include <stdio.h>

#include "logistic.h"
#include "util.h"

int main() {
  int n = 10;
  logistic_t *lr = logr(n);

  int k = 1000;

  vec X = vector(k * n);
  vec y = vector(k);

  for (int i = 0; i < k; i++) {
    double tot = 0;
    for (int j = 0; j < n; j++) {
      *(X + i * n + j) = random_float();
      tot += *(X + i * n + j);
    }

    y[i] = (double)(tot > 1);
  }

  logr_fit(lr, X, y, k, 100000, 0.05);

  vec x_test = vector(10);

  for (int i = 0; i < 10; i++) {
    x_test[i] = 0.12;
  }

  printf("%f\n", logr_eval(lr, x_test));
}
