#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

#include "matrix.h"
#include "util.h"

inline f64 *M(matrix_t *m, u32 i, u32 j) { return m->values + (i * m->n + j); }

f64 mat_unwrap(matrix_t *m) {
  assert(m->m == m->n);
  return *m->values;
}

f64 vec_dot(vector_t a, vector_t b, u32 n) {
  f64 p = 0;

  for (u32 i = 0; i < n; i++) {
    p += a[i] * b[i];
  }

  return p;
}

void vec_add(vector_t v1, vector_t v2, vector_t v3, u32 n) {
  for (u32 i = 0; i < n; i++) {
    v3[i] = v1[i] + v2[i];
  }
}

void vec_mul(vector_t v1, u32 c, vector_t v2, u32 n) {
  for (u32 i = 0; i < n; i++) {
    v2[i] = c * v1[i];
  }
}

void mat_mul(matrix_t *A, matrix_t *B, matrix_t *C) {
  u32 m = A->m;
  u32 n = A->n;
  u32 p = C->n;

  for (u32 i = 0; i < m; i++) {
    for (u32 j = 0; j < p; j++) {
      *M(C, i, j) = 0;

      for (u32 k = 0; k < n; k++) {
        *M(C, i, j) += *M(A, i, k) * *M(B, k, j);
      }
    }
  }
}

void free_matrix(matrix_t *m) {
  free(m->values);
  free(m);
}

void init_random(vector_t src, u32 n) { MAP(src, n, random_float()); }

vector_t vector(u32 n) { return calloc(n, sizeof(f64)); }

vector_t vector_from(u32 n, ...) {
  va_list args;
  va_start(args, n);

  vector_t v = vector(n);

  for (u32 i = 0; i < n; i++) {
    v[i] = va_arg(args, f64);
  }

  va_end(args);

  return v;
}

matrix_t *matrix(u32 m, u32 n) {
  matrix_t *mat = malloc(sizeof(matrix_t));

  *mat = (matrix_t){
      .m = m,
      .n = n,
      .values = vector(m * n),
  };

  return mat;
}

matrix_t *matrix_from(u32 m, u32 n, ...) {
  matrix_t *mat = malloc(sizeof(matrix_t));

  *mat = (matrix_t){
      .m = m,
      .n = n,
      .values = vector(m * n),
  };

  va_list args;
  va_start(args, n);

  for (u32 i = 0; i < m * n; i++) {
    mat->values[i] = va_arg(args, f64);
  }

  va_end(args);

  return mat;
}

matrix_t matrix_vec(u32 m, u32 n, vector_t v) {
  return (matrix_t){.m = m, .n = n, .values = v};
}
