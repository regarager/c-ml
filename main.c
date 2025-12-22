#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "neural.h"
#include "util.h"

double f(vec x) { return x[0] + 2 * x[1] + 3 * x[2] + 4; }

int main() {
  srand(time(NULL));

  int L = 4;
  layer_t *l1 = layer(2, 100, pass, d_pass);
  layer_t *l2 = layer(100, 100, sigmoid, d_sigmoid);
  layer_t *l3 = layer(100, 1, pass, d_pass);
  layer_t *l4 = layer(1, 1, sigmoid, d_sigmoid);

  neural_t *nn = neural(L, l1, l2, l3, l4);

  vec x = vec_from(2, 1, 1);
  vec *activations = init_activations(nn);

  neural_eval(nn, x, activations);

  printf("%f\n", activations[3][0]);
}
