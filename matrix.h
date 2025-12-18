#ifndef MATRIX_H
#define MATRIX_H

typedef double (*func)(double);
typedef double* vec;
typedef struct {
  int m, n;
  double *values;
} Matrix;

double *M(Matrix *m, int i, int j);
double dot_product(vec a, vec b, int n);
void add(vec v1, vec v2, vec v3, int n);
void mul(vec v1, int c, vec v2, int n);
void matmul(Matrix *A, Matrix *B, Matrix *C);
void free_matrix(Matrix* m);

#endif
