#include <stdarg.h>
#include <stdlib.h>

#include "matrix.h"
#include "util.h"

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

void init_random(vec src, int n) { MAP(src, n, random_float()); }

vec vector(int n) { return calloc(n, sizeof(double)); }

vec vec_from(int n, ...) {
  va_list args;
  va_start(args, n);

  vec v = vector(n);

  for (int i = 0; i < n; i++) {
    v[i] = va_arg(args, double);
  }

  va_end(args);

  return v;
}

Matrix *matrix(int m, int n) {
  Matrix *mat = malloc(sizeof(Matrix));

  *mat = (Matrix){
      .m = m,
      .n = n,
      .values = vector(m * n),
  };

  return mat;
}

Matrix *matrix_from(int m, int n, ...) {
  Matrix *mat = malloc(sizeof(Matrix));

  *mat = (Matrix){
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

Matrix *matrix_vec(vec v, int n) {
  Matrix *mat = malloc(sizeof(Matrix));

  *mat = (Matrix){
      .m = n,
      .n = 1,
      .values = v,
  };

  return mat;
}
