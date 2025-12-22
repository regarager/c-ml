#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linreg.h"
#include "matrix.h"
#include "util.h"

void LRInit(LinearRegression *lr, int n) {
  lr->n = n;
  lr->w = vector(n);
  init_random(lr->w, n);
  lr->b = random_float();
}

double LREval(LinearRegression *lr, vec x) {
  return dot_product(lr->w, x, lr->n) + lr->b;
}

double LRCost(LinearRegression *lr, vec x, double y) {
  double y_pred = LREval(lr, x);

  return (y_pred - y) * (y_pred - y);
}

void LRFit(LinearRegression *lr, vec X, vec y, int k, int epochs,
           double alpha) {
  int n = lr->n;

  vec dw = vector(n);

  for (int epoch = 1; epoch <= epochs; epoch++) {
    double db = 0;

    double cost = 0;

    for (int i = 0; i < k; i++) {
      double error = (LREval(lr, X + n * i) - y[i]) / k;
      cost += error * error * k * 0.5;

      for (int j = 0; j < n; j++) {
        dw[j] += *(X + n * i + j) * error;
      }
      db += error;
    }

    for (int i = 0; i < n; i++) {
      lr->w[i] -= dw[i] * alpha;
    }

    lr->b -= db * alpha;

    memset(dw, 0, n * sizeof(double));

    if (epoch == 1 || epoch % 1000 == 0) {
      printf("epoch: %d, cost: %f\n", epoch, cost);
    }
  }

  free(dw);
}
