#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "neural.h"
#include "util.h"

double f(vec x) { return x[0] + 2 * x[1] + 3 * x[2] + 4; }
double sigmoid(double x) { return 1 / (1 + exp(-x)); }
double d_sigmoid(double y) { return y * (1 - y); };

int main() {
  srand(time(NULL));

  int L = 4;
  Layer *l1 = layer(2, 100, pass, d_pass);
  Layer *l2 = layer(100, 100, sigmoid, d_sigmoid);
  Layer *l3 = layer(100, 1, pass, d_pass);
  Layer *l4 = layer(1, 1, sigmoid, d_sigmoid);

  Network *nn = network(L, l1, l2, l3, l4);

  vec x = vec_from(2, 1, 1);
  vec *activations = init_activations(nn);

  NEval(nn, x, activations);

  printf("%f\n", activations[3][0]);
}
