#include <stdarg.h>
#include <stdlib.h>

#include "matrix.h"
#include "neural.h"

layer_t *layer(int in, int out, func activation, func d_activation) {
  layer_t *l = (layer_t *)malloc(sizeof(layer_t));

  *l = (layer_t){
      .in = in,
      .out = out,
      .W = matrix(out, in),
      .b = vector(out),
      .activation = activation,
      .d_activation = d_activation,
  };

  init_random(l->W->values, l->in * l->out);
  init_random(l->b, l->out);

  return l;
}

void layer_eval(layer_t *l, vector_t x, vector_t z) {
  matrix_t *x_mat = matrix_vec(x, l->in);
  matrix_t *z_mat = matrix_vec(z, l->out);

  mat_mul(l->W, x_mat, z_mat);
  vec_add(z_mat->values, l->b, z_mat->values, l->out);
  MAP(z, l->out, l->activation(z[i]));

  free(x_mat);
  free(z_mat);
}

void free_layer(layer_t *l) {
  free_matrix(l->W);
  free(l->b);
  free(l);
}

neural_t *neural(int L, ...) {
  neural_t *nn = malloc(sizeof(neural_t));

  nn->L = L;
  nn->layers = (layer_t **)calloc(L, sizeof(layer_t *));

  va_list args;
  va_start(args, L);

  for (int i = 0; i < L; i++) {
    nn->layers[i] = va_arg(args, layer_t *);
  }

  va_end(args);

  return nn;
}

vector_t neural_eval(neural_t *nn, vector_t x, vector_t *activations) {
  layer_eval(nn->layers[0], x, activations[0]);

  for (int i = 1; i < nn->L; i++) {
    layer_eval(nn->layers[i], activations[i - 1], activations[i]);
  }

  return activations[nn->L - 1];
}

void free_network(neural_t *nn) {
  for (int i = 0; i < nn->L; i++) {
    free_layer(nn->layers[i]);
  }

  free(nn->layers);
  free(nn);
}

vector_t *init_activations(neural_t *nn) {
  vector_t *activations = (vector_t *)calloc(nn->L, sizeof(vector_t));

  for (int i = 0; i < nn->L; i++) {
    activations[i] = vector(nn->layers[i]->out);
  }

  return activations;
}

typedef struct {
  matrix_t *da_dz;
  matrix_t *dz_dw; // wrt weights
  matrix_t *dz_dx; // i think just W?
  vector_t dz_db;
  func d_activation;
} _derivative;

_derivative *init_derivative(layer_t *l) {
  _derivative *d = (_derivative *)malloc(sizeof(_derivative));

  // TODO: implement sizes
  *d = (_derivative){
      .da_dz = matrix(-1, -1),
      .dz_dw = matrix(-1, -1),
      .dz_dx = matrix(-1, -1),
      .dz_db = vector(-1),
      .d_activation = l->d_activation,
  };

  return d;
}

void neural_fit(neural_t *nn, vector_t X, vector_t Y, int k, int epochs,
                double alpha) {
  int L = nn->L;
  int in = nn->layers[0]->in;
  vector_t *activations = init_activations(nn);

  _derivative **D = (_derivative **)calloc(L, sizeof(_derivative *));
  for (int i = 0; i < L; i++) {
    D[i] = init_derivative(nn->layers[i]);
  }

  for (int epoch = 1; epoch <= epochs; epoch++) {
    for (int i = 0; i < k; i++) {
      vector_t y = neural_eval(nn, X + i * in, activations);

      // TODO: backpropagation
    }
  }

  for (int i = 0; i < L; i++) {
    free(activations[i]);
  }

  free(activations);
}
