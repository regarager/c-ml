#ifndef MATRIX_H
#define MATRIX_H

#include "base/types.h"

typedef f64 (*func)(f64);
typedef f64 *vector_t;
typedef struct {
  u32 m, n;
  f64 *values;
} matrix_t;

#define MAP(v, n, f)                                                           \
  do {                                                                         \
    for (u32 i = 0; i < n; i++) {                                              \
      v[i] = f;                                                                \
    }                                                                          \
  } while (0)

vector_t vector(u32 n);
vector_t vector_from(u32 n, ...);
void vec_add(vector_t v1, vector_t v2, vector_t v3, u32 n);
void vec_mul(vector_t v1, u32 c, vector_t v2, u32 n);
f64 vec_dot(vector_t a, vector_t b, u32 n);

f64 *M(matrix_t *m, u32 i, u32 j);
f64 mat_unwrap(matrix_t *m);
matrix_t *matrix(u32 m, u32 n);
matrix_t *matrix_from(u32 m, u32 n, ...);
matrix_t matrix_vec(u32 m, u32 n, vector_t v);
void mat_mul(matrix_t *A, matrix_t *B, matrix_t *C);
void free_matrix(matrix_t *m);

void init_random(vector_t src, u32 n);

#endif
