#ifndef MATRIX_H
#define MATRIX_H

typedef double (*func)(double);
typedef double *vec;
typedef struct {
  int m, n;
  double *values;
} Matrix;

#define MAP(v, n, f)                                                           \
  do {                                                                         \
    for (int i = 0; i < n; i++) {                                              \
      v[i] = f;                                                                \
    }                                                                          \
  } while (0)

vec vector(int n);
vec vec_from(int n, ...);
void add(vec v1, vec v2, vec v3, int n);
void mul(vec v1, int c, vec v2, int n);
double dot_product(vec a, vec b, int n);
void init_random(vec src, int n);

double *M(Matrix *m, int i, int j);
Matrix *matrix(int m, int n);
Matrix *matrix_from(int m, int n, ...);
Matrix *matrix_vec(vec v, int n);
void matmul(Matrix *A, Matrix *B, Matrix *C);
void free_matrix(Matrix *m);

#endif
