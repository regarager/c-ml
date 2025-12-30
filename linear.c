#include <stdio.h>
#include <stdlib.h>

#include "linear.h"
#include "matrix.h"
#include "util.h"

linear_t *make_linr(u32 n) {
  linear_t *lr = (linear_t *)malloc(sizeof(linear_t));

  *lr = (linear_t){
      .n = n,
      .w = vector(n),
      .b = random_float(),
  };

  init_random(lr->w, n);

  return lr;
}

f64 linr_eval(linear_t *lr, vector_t x) {
  return vec_dot(lr->w, x, lr->n) + lr->b;
}

void linr_fit(linear_t *lr, vector_t X, vector_t y, u32 k, u32 epochs,
              f64 alpha) {
  u32 n = lr->n;
  vector_t dw = vector(n);

  for (u32 epoch = 1; epoch <= epochs; epoch++) {
    f64 db = 0, cost = 0;

    for (u32 i = 0; i < k; i++) {
      f64 error = (linr_eval(lr, X + n * i) - y[i]) / k;
      cost += error * error * k * 0.5;

      for (u32 j = 0; j < n; j++) {
        dw[j] += *(X + n * i + j) * error;
      }

      db += error;
    }

    for (u32 i = 0; i < n; i++) {
      lr->w[i] -= dw[i] * alpha;
      dw[i] = 0;
    }

    lr->b -= db * alpha;

    printf("epoch: %d, cost: %f\n", epoch, cost);
  }

  free(dw);
}
