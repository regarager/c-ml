#ifndef NEURAL_H
#define NEURAL_H

#include "matrix.h"

typedef struct {
  int in;
  int out;
  Matrix *W;
  vec b;
  func activation;
} Layer;

typedef struct {
  int L;
  Layer **layers;
} Network;

double pass(double x);

Layer *layer(int in, int out, func activation);
void LEval(Layer *l, vec x, vec z);
void free_layer(Layer *l);

Network *network(int L, ...);
vec NEval(Network *nn, vec x, vec *activations);
void free_network(Network *nn);

#endif
