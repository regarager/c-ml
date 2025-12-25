#ifndef NEURAL_H
#define NEURAL_H

#include "matrix.h"

typedef struct {
  int in;
  int out;
  matrix_t *W;
  vector_t b;
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
void layer_eval(layer_t *l, vector_t x, vector_t z);
void free_layer(layer_t *l);

neural_t *neural(int L, ...);
vector_t neural_eval(neural_t *nn, vector_t x, vector_t *activations);
void neural_fit(neural_t *nn, vector_t X, vector_t Y, int k, int epochs,
                double alpha);
void free_network(neural_t *nn);

vector_t *init_activations(neural_t *nn);

#endif
