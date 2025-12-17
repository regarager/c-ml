#include "matrix.h"

double dot_product(vec a, vec b, int n) {
  double p = 0;

  for (int i = 0; i < n; i++) {
    p += a[i] * b[i];
  }

  return p;
}

void matmul(vec A, vec B, vec C, int m, int n, int p) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      *(C + i * p + j) = 0;

      for (int k = 0; k < n; k++) {
        *(C + i * p + j) += *(A + i * n + k) * *(B + k * p + j);
      }
    }
  }
}
