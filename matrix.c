#include <stdlib.h>

#include "matrix.h"

double *M(Matrix *m, int i, int j) { return m->values + (i * m->n + j); }

double dot_product(vec a, vec b, int n) {
  double p = 0;

  for (int i = 0; i < n; i++) {
    p += a[i] * b[i];
  }

  return p;
}

void add(vec v1, vec v2, vec v3, int n) {
  for (int i = 0; i < n; i++) {
    v3[i] = v1[i] + v2[i];
  }
}

void mul(vec v1, int c, vec v2, int n) {
  for (int i = 0; i < n; i++) {
    v2[i] = c * v1[i];
  }
}

void matmul(Matrix *A, Matrix *B, Matrix *C) {
  int m = A->m;
  int n = A->n;
  int p = C->n;

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      *M(C, i, j) = 0;

      for (int k = 0; k < n; k++) {
        *M(C, i, j) += *M(A, i, k) * *M(B, k, j);
      }
    }
  }
}

void free_matrix(Matrix *m) {
  free(m->values);
  free(m);
}
