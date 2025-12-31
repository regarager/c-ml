#ifndef NEURAL_H
#define NEURAL_H

#include "matrix.h"

typedef struct {
  u32 in;
  u32 out;
  matrix_t *W;
  vector_t b;
  func activation;
  func d_activation;
} layer_t;

typedef struct {
  u32 L;
  layer_t **layers;
} neural_t;

f64 pass(f64 x);
f64 d_pass(f64 x);

layer_t *make_layer(u32 in, u32 out, func activation, func d_activation);
void layer_eval(layer_t *l, vector_t x, vector_t z);
void free_layer(layer_t *l);

neural_t *make_neural(u32 L, ...);
vector_t neural_eval(neural_t *nn, vector_t x, vector_t *activations);
void neural_fit(neural_t *nn, vector_t X, vector_t Y, u32 k, u32 epochs,
                f64 alpha);
void free_network(neural_t *nn);

vector_t *init_activations(neural_t *nn);

#endif
