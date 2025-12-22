#ifndef NEURAL_H
#define NEURAL_H

#include "matrix.h"

typedef struct {
  int in;
  int out;
  Matrix *W;
  vec b;
  func activation;
  func d_activation;
} Layer;

typedef struct {
  int L;
  Layer **layers;
} Network;

double pass(double x);
double d_pass(double x);

Layer *layer(int in, int out, func activation, func d_activation);
void LEval(Layer *l, vec x, vec z);
void free_layer(Layer *l);

Network *network(int L, ...);
vec NEval(Network *nn, vec x, vec *activations);
void NFit(Network *nn, vec X, vec Y, int k, int epochs, double alpha);
void free_network(Network *nn);

vec *init_activations(Network *nn);

#endif
