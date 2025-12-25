#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logistic.h"
#include "util.h"

logistic_t *logr(int n) {
  logistic_t *lr = (logistic_t *)malloc(sizeof(logistic_t));

  *lr = (logistic_t){
      .n = n,
      .w = vector(n),
      .b = random_float(),
  };

  init_random(lr->w, n);

  return lr;
}

double logr_eval(logistic_t *lr, vector_t x) {
  double u = vec_dot(lr->w, x, lr->n) + lr->b;
  return 1 / (1 + exp(-u));
}

double logr_cost(logistic_t *lr, vector_t x, double y) {
  double y_pred = logr_eval(lr, x);

  return (y_pred - y) * (y_pred - y);
}

void logr_fit(logistic_t *lr, vector_t X, vector_t y, int k, int epochs,
              double alpha) {
  int n = lr->n;

  vector_t dw = vector(n);

  for (int epoch = 1; epoch <= epochs; epoch++) {
    double db = 0;

    double cost = 0;

    for (int i = 0; i < k; i++) {
      double y_pred = logr_eval(lr, X + n * i);

      if (y_pred == NAN) {
        printf("bad\n");
      }
      double error = y_pred - y[i];
      cost += error * error / k * 0.5;

      for (int j = 0; j < n; j++) {
        dw[j] += error / k * y_pred * (1 - y_pred) * *(X + n * i + j);
      }
      db += error / k * y_pred * (1 - y_pred);
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
