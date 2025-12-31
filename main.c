#include <stdio.h>

#include "matrix.h"
#include "neural.h"
#include "util.h"

int main() {
  u32 L = 4;
  layer_t *l0 = make_layer(2, 10, pass, d_pass);
  layer_t *l1 = make_layer(10, 10, sigmoid, d_sigmoid);
  layer_t *l2 = make_layer(10, 1, pass, d_pass);
  layer_t *l3 = make_layer(1, 1, sigmoid, d_sigmoid);

  neural_t *nn = make_neural(L, l0, l1, l2, l3);

  u32 k = 4;

  vector_t X = vector(4 * 2);
  X[0] = 0;
  X[1] = 0;
  X[2] = 0;
  X[3] = 1;
  X[4] = 1;
  X[5] = 0;
  X[6] = 1;
  X[7] = 1;

  vector_t Y = vector(4);
  Y[0] = 0;
  Y[1] = 1;
  Y[2] = 1;
  Y[3] = 0;

  u32 epochs = 1e5;
  f64 alpha = 0.5;
  neural_fit(nn, X, Y, k, epochs, alpha);

  vector_t *activations = init_activations(nn);
  for (u32 i = 0; i < 4; i++) {
    neural_eval(nn, X + 2 * i, activations);
    printf("%f ^ %f = %f\n", (X + 2 * i)[0], (X + 2 * i)[1], activations[3][0]);
  }
}
