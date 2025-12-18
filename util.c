#include <stdarg.h>
#include <stdlib.h>

#include "matrix.h"

double urandom_float() { return 1.0 * rand() / RAND_MAX; }
double random_float() { return urandom_float() * 2 - 1; }

void init_random(vec src, int n) {
  for (int i = 0; i < n; i++) {
    src[i] = random_float();
  }
}

void map(vec src, int n, double (*f)(double, int)) {
  for (int i = 0; i < n; i++) {
    src[i] = f(src[i], i);
  }
}

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
  mat->m = m;
  mat->n = n;
  mat->values = vector(m * n);
  return mat;
}

Matrix *matrix_from(int m, int n, ...) {
  Matrix *mat = malloc(sizeof(Matrix));
  mat->m = m;
  mat->n = n;
  mat->values = vector(m * n);

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
  mat->m = n;
  mat->n = 1;
  mat->values = v;

  return mat;
}
