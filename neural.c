#include <stdarg.h>
#include <stdlib.h>

#include "neural.h"
#include "util.h"

double pass(double x) { return x; }

Layer *layer(int in, int out, func activation) {
  Layer *l = (Layer *)malloc(sizeof(Layer));

  l->in = in;
  l->out = out;
  l->W = matrix(out, in);
  l->b = vector(out);
  l->activation = activation;

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
