#include "matrix.h"
#include "util.h"

int main() {
  Matrix *A = matrix(2, 2);
  Matrix *B = matrix(2, 2);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      *M(A, i, j) = i * 2 + j + 1;
      *M(B, i, j) = i * 2 + j + 5;
    }
  }

  Matrix *C = matrix(2, 2);

  matmul(A, B, C);
}
