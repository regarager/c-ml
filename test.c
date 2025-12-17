#include "matrix.h"
#include "util.h"

int main() {
  vec A = vector(2 * 2);
  vec B = vector(2 * 2);
  for (int i = 0; i < 4; i++) {
    A[i] = i + 1;
    B[i] = i + 5;
  }
  
  vec C = vector(2 * 2);

  matmul(A, B, C, 2, 2, 2);
}
