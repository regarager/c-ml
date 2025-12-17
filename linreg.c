#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linalg.h"
#include "linreg.h"
#include "util.h"

void LRInit(LinearRegression *lr, int n) {
  lr->n = n;
  lr->w = (double *)calloc(n, sizeof(double));
  init_random(lr->w, n);
  lr->b = rand_float();
}

double LREval(LinearRegression *lr, double *x) {
  return dot_product(lr->w, x, lr->n) + lr->b;
}

double LRCost(LinearRegression *lr, double *x, double y) {
  double y_pred = dot_product(lr->w, x, lr->n) + lr->b;

  return (y_pred - y) * (y_pred - y);
}

void LRFit(LinearRegression *lr, double *X, double *y, int k, int epochs,
           double alpha) {
  int n = lr->n;

  double *dw = (double *)calloc(n, sizeof(double));
  for (int epoch = 1; epoch <= epochs; epoch++) {
    double db = 0;

    double cost = 0;

    for (int i = 0; i < k; i++) {
      double error = (dot_product(lr->w, X + n * i, n) + lr->b - y[i]) / k;
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
}
