#ifndef MATRIX_H
#define MATRIX_H

typedef double (*func)(double);
typedef double *vector_t;
typedef struct {
  int m, n;
  double *values;
} matrix_t;

#define MAP(v, n, f)                                                           \
  do {                                                                         \
    for (int i = 0; i < n; i++) {                                              \
      v[i] = f;                                                                \
    }                                                                          \
  } while (0)

vector_t vector(int n);
vector_t vector_from(int n, ...);
void vec_add(vector_t v1, vector_t v2, vector_t v3, int n);
void vec_mul(vector_t v1, int c, vector_t v2, int n);
double vec_dot(vector_t a, vector_t b, int n);

double *M(matrix_t *m, int i, int j);
matrix_t *matrix(int m, int n);
matrix_t *matrix_from(int m, int n, ...);
matrix_t *matrix_vec(vector_t v, int n);
void mat_mul(matrix_t *A, matrix_t *B, matrix_t *C);
void free_matrix(matrix_t *m);

void init_random(vector_t src, int n);

#endif
