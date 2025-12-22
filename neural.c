#include <stdarg.h>
#include <stdlib.h>

#include "neural.h"
#include "util.h"

double pass(double x) { return x; }
double d_pass(double x) { return 1; }

Layer *layer(int in, int out, func activation, func d_activation) {
  Layer *l = (Layer *)malloc(sizeof(Layer));

  l->in = in;
  l->out = out;
  l->W = matrix(out, in);
  l->b = vector(out);
  l->activation = activation;
  l->d_activation = d_activation;

  init_random(l->W->values, l->in * l->out);
  init_random(l->b, l->out);

  return l;
}

void LEval(Layer *l, vec x, vec z) {
  Matrix *x_mat = matrix_vec(x, l->in);
  Matrix *z_mat = matrix_vec(z, l->out);

  matmul(l->W, x_mat, z_mat);
  add(z_mat->values, l->b, z_mat->values, l->out);
  map(z, l->out, l->activation);

  free(x_mat);
  free(z_mat);
}

void free_layer(Layer *l) {
  free_matrix(l->W);
  free(l->b);
  free(l);
}

Network *network(int L, ...) {
  Network *nn = malloc(sizeof(Network));
  nn->L = L;
  nn->layers = (Layer **)calloc(L, sizeof(Layer *));

  va_list args;
  va_start(args, L);

  for (int i = 0; i < L; i++) {
    nn->layers[i] = va_arg(args, Layer *);
  }

  va_end(args);

  return nn;
}

vec NEval(Network *nn, vec x, vec *activations) {
  LEval(nn->layers[0], x, activations[0]);

  for (int i = 1; i < nn->L; i++) {
    LEval(nn->layers[i], activations[i - 1], activations[i]);
  }

  return activations[nn->L - 1];
}

void free_network(Network *nn) {
  for (int i = 0; i < nn->L; i++) {
    free_layer(nn->layers[i]);
  }

  free(nn->layers);
  free(nn);
}

vec *init_activations(Network *nn) {
  vec *activations = (vec *)calloc(nn->L, sizeof(vec));

  for (int i = 0; i < nn->L; i++) {
    activations[i] = vector(nn->layers[i]->out);
  }

  return activations;
}

typedef struct {
  Matrix *da_dz;
  Matrix *dz_dw; // wrt weights
  Matrix *dz_dx; // i think just W?
  vec dz_db;
  func d_activation;
} _derivative;

_derivative *init_derivative(Layer *l) {
  _derivative *d = (_derivative *)malloc(sizeof(_derivative));

  // TODO: implement sizes
  d->da_dz = matrix(-1, -1);
  d->dz_dw = matrix(-1, -1);
  d->dz_dx = matrix(-1, -1);
  d->dz_db = vector(-1);

  d->d_activation = l->d_activation;

  return d;
}

void NFit(Network *nn, vec X, vec Y, int k, int epochs, double alpha) {
  int L = nn->L;
  int in = nn->layers[0]->in;
  vec *activations = init_activations(nn);

  _derivative **D = (_derivative **)calloc(L, sizeof(_derivative *));
  for (int i = 0; i < L; i++) {
    D[i] = init_derivative(nn->layers[i]);
  }

  for (int epoch = 1; epoch <= epochs; epoch++) {
    for (int i = 0; i < k; i++) {
      vec y = NEval(nn, X + i * in, activations);

      // TODO: backpropagation
    }
  }

  for (int i = 0; i < L; i++) {
    free(activations[i]);
  }

  free(activations);
}
