#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logistic.h"
#include "util.h"

logistic_t *logr(u32 n) {
  logistic_t *lr = (logistic_t *)malloc(sizeof(logistic_t));

  *lr = (logistic_t){
      .n = n,
      .w = vector(n),
      .b = random_float(),
  };

  init_random(lr->w, n);

  return lr;
}

f64 logr_eval(logistic_t *lr, vector_t x) {
  f64 u = vec_dot(lr->w, x, lr->n) + lr->b;
  return 1 / (1 + exp(-u));
}

f64 logr_cost(logistic_t *lr, vector_t x, f64 y) {
  f64 y_pred = logr_eval(lr, x);

  return (y_pred - y) * (y_pred - y);
}

void logr_fit(logistic_t *lr, vector_t X, vector_t y, u32 k, u32 epochs,
              f64 alpha) {
  u32 n = lr->n;

  vector_t dw = vector(n);

  for (u32 epoch = 1; epoch <= epochs; epoch++) {
    f64 db = 0;

    f64 cost = 0;

    for (u32 i = 0; i < k; i++) {
      f64 y_pred = logr_eval(lr, X + n * i);
      f64 error = y_pred - y[i];

      cost += error * error / k * 0.5;

      for (u32 j = 0; j < n; j++) {
        dw[j] += error / k * y_pred * (1 - y_pred) * *(X + n * i + j);
      }
      db += error / k * y_pred * (1 - y_pred);
    }

    for (u32 i = 0; i < n; i++) {
      lr->w[i] -= dw[i] * alpha;
    }

    lr->b -= db * alpha;

    memset(dw, 0, n * sizeof(f64));

    if (epoch == 1 || epoch % 1000 == 0) {
      printf("epoch: %d, cost: %f\n", epoch, cost);
    }
  }

  free(dw);
}
