#include <stdarg.h>
#include <stdlib.h>

#include "matrix.h"
#include "util.h"

inline double *M(matrix_t *m, int i, int j) {
  return m->values + (i * m->n + j);
}

double vec_dot(vector_t a, vector_t b, int n) {
  double p = 0;

  for (int i = 0; i < n; i++) {
    p += a[i] * b[i];
  }

  return p;
}

void vec_add(vector_t v1, vector_t v2, vector_t v3, int n) {
  for (int i = 0; i < n; i++) {
    v3[i] = v1[i] + v2[i];
  }
}

void vec_mul(vector_t v1, int c, vector_t v2, int n) {
  for (int i = 0; i < n; i++) {
    v2[i] = c * v1[i];
  }
}

void mat_mul(matrix_t *A, matrix_t *B, matrix_t *C) {
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

void free_matrix(matrix_t *m) {
  free(m->values);
  free(m);
}

void init_random(vector_t src, int n) { MAP(src, n, random_float()); }

vector_t vector(int n) { return calloc(n, sizeof(double)); }

vector_t vector_from(int n, ...) {
  va_list args;
  va_start(args, n);

  vector_t v = vector(n);

  for (int i = 0; i < n; i++) {
    v[i] = va_arg(args, double);
  }

  va_end(args);

  return v;
}

matrix_t *matrix(int m, int n) {
  matrix_t *mat = malloc(sizeof(matrix_t));

  *mat = (matrix_t){
      .m = m,
      .n = n,
      .values = vector(m * n),
  };

  return mat;
}

matrix_t *matrix_from(int m, int n, ...) {
  matrix_t *mat = malloc(sizeof(matrix_t));

  *mat = (matrix_t){
      .m = m,
      .n = n,
      .values = vector(m * n),
  };

  va_list args;
  va_start(args, n);

  for (int i = 0; i < m * n; i++) {
    mat->values[i] = va_arg(args, double);
  }

  va_end(args);

  return mat;
}

matrix_t *matrix_vec(vector_t v, int n) {
  matrix_t *mat = malloc(sizeof(matrix_t));

  *mat = (matrix_t){
      .m = n,
      .n = 1,
      .values = v,
  };

  return mat;
}
