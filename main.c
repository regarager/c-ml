#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "neural.h"
#include "util.h"

double f(vec x) { return x[0] + 2 * x[1] + 3 * x[2] + 4; }
double sigmoid(double x) { return 1 / (1 + exp(-x)); }

int main() {
  srand(time(NULL));

  int L = 4;
  Layer *l1 = layer(2, 100, pass);
  Layer *l2 = layer(100, 100, sigmoid);
  Layer *l3 = layer(100, 1, pass);
  Layer *l4 = layer(1, 1, sigmoid);

  Network *nn = network(L, l1, l2, l3, l4);

  vec x = vec_from(2, 1, 1);
  vec y = vector(1);

  vec *activations = (vec *)calloc(L, sizeof(vec));

  activations[0] = vector(100);
  activations[1] = vector(100);
  activations[2] = vector(1);
  activations[3] = y;


  NEval(nn, x, activations);

  printf("%f\n", activations[3][0]);
}
