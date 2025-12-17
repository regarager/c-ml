#include <stdlib.h>

#include "util.h"

double rand_float() { return 1.0 * rand() / RAND_MAX; }

void init_random(double *src, int n) {
  for (int i = 0; i < n; i++) {
    src[i] = rand_float();
  }
}

void map(double *src, int n, double (*f)(double, int)) {
  for (int i = 0; i < n; i++) {
    src[i] = f(src[i], i);
  }
}
