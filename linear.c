#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linear.h"
#include "matrix.h"
#include "util.h"

linear_t* linr(int n) {
  linear_t* lr = (linear_t*) malloc(sizeof(linear_t));

  lr->n = n;
  lr->w = vector(n);
  init_random(lr->w, n);
  lr->b = random_float();

  return lr;
}

double linr_eval(linear_t *lr, vec x) {
  return dot_product(lr->w, x, lr->n) + lr->b;
}

double linr_cost(linear_t *lr, vec x, double y) {
  double y_pred = linr_eval(lr, x);

  return (y_pred - y) * (y_pred - y);
}

void linr_fit(linear_t *lr, vec X, vec y, int k, int epochs,
           double alpha) {
  int n = lr->n;

  vec dw = vector(n);

  for (int epoch = 1; epoch <= epochs; epoch++) {
    double db = 0;

    double cost = 0;

    for (int i = 0; i < k; i++) {
      double error = (linr_eval(lr, X + n * i) - y[i]) / k;
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
