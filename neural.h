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
} layer_t;

typedef struct {
  int L;
  layer_t **layers;
} neural_t;

double pass(double x);
double d_pass(double x);

layer_t *layer(int in, int out, func activation, func d_activation);
void layer_eval(layer_t *l, vec x, vec z);
void free_layer(layer_t *l);

neural_t *neural(int L, ...);
vec neural_eval(neural_t *nn, vec x, vec *activations);
void neural_fit(neural_t *nn, vec X, vec Y, int k, int epochs, double alpha);
void free_network(neural_t *nn);

vec *init_activations(neural_t *nn);

#endif
