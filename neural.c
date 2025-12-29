#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "neural.h"

layer_t *layer(u32 in, u32 out, func activation, func d_activation) {
  layer_t *l = (layer_t *)malloc(sizeof(layer_t));

  *l = (layer_t){
      .in = in,
      .out = out,
      .W = matrix(out, in),
      .b = vector(out),
      .activation = activation,
      .d_activation = d_activation,
  };

  // activation is only pass if layer is linear (f = Wx + b)
  if (activation == pass) {
    init_random(l->W->values, l->in * l->out);
    init_random(l->b, l->out);
  } else {
    assert(in == out);

    for (u32 i = 0; i < out; i++) {
      *M(l->W, i, i) = 1;
    }
  }

  return l;
}

void layer_eval(layer_t *l, vector_t x, vector_t z) {
  matrix_t x_mat = {
      .m = l->in,
      .n = 1,
      .values = x,
  };

  matrix_t z_mat = {
      .m = l->out,
      .n = 1,
      .values = z,
  };

  mat_mul(l->W, &x_mat, &z_mat);
  vec_add(z_mat.values, l->b, z_mat.values, l->out);
  MAP(z, l->out, l->activation(z[i]));
}

void free_layer(layer_t *l) {
  free_matrix(l->W);
  free(l->b);
  free(l);
}

neural_t *neural(u32 L, ...) {
  neural_t *nn = malloc(sizeof(neural_t));

  nn->L = L;
  nn->layers = (layer_t **)calloc(L, sizeof(layer_t *));

  va_list args;
  va_start(args, L);

  for (u32 i = 0; i < L; i++) {
    nn->layers[i] = va_arg(args, layer_t *);
  }

  va_end(args);

  return nn;
}

vector_t neural_eval(neural_t *nn, vector_t x, vector_t *activations) {
  layer_eval(nn->layers[0], x, activations[0]);

  for (u32 i = 1; i < nn->L; i++) {
    layer_eval(nn->layers[i], activations[i - 1], activations[i]);
  }

  return activations[nn->L - 1];
}

void free_network(neural_t *nn) {
  for (u32 i = 0; i < nn->L; i++) {
    free_layer(nn->layers[i]);
  }

  free(nn->layers);
  free(nn);
}

vector_t *init_activations(neural_t *nn) {
  vector_t *activations = malloc(sizeof(vector_t) * nn->L);

  for (u32 i = 0; i < nn->L; i++) {
    activations[i] = vector(nn->layers[i]->out);
  }

  return activations;
}

void neural_fit(neural_t *nn, vector_t X, vector_t Y, u32 k, u32 epochs,
                f64 alpha) {
  layer_t **layers = nn->layers;
  u32 L = nn->L;
  u32 in = layers[0]->in;
  u32 out = layers[L - 1]->out;

  vector_t *activations = init_activations(nn);

  matrix_t **dp = calloc(L + 1, sizeof(matrix_t *));

  for (u32 i = 0; i < L; i++) {
    dp[i] = matrix(1, layers[i]->in);
  }

  dp[L] = matrix(1, out);

  for (u32 epoch = 1; epoch <= epochs; epoch++) {
    f64 cost = 0;
    for (u32 i = 0; i < k; i++) {
      vector_t x = X + i * in;
      vector_t y = Y + i * out;
      vector_t y_pred = neural_eval(nn, x, activations);

      for (u32 j = 0; j < out; j++) {
        f64 error = y_pred[j] - y[j];
        *M(dp[L], 0, j) = error / k;
        cost += 0.5 * error * error / k;
      }

      for (i32 l = L - 1; l >= 0; l--) {
        if (layers[l]->activation != pass) {
          matrix_t *da_dz = matrix(layers[l]->out, layers[l]->in);

          for (u32 t = 0; t < layers[l]->out; t++) {
            *M(da_dz, t, t) = layers[l]->d_activation(activations[l][t]);
          }

          mat_mul(dp[l + 1], da_dz, dp[l]);
          free_matrix(da_dz);
        } else {
          // update weights and biases
          vector_t z = l > 0 ? activations[l - 1] : x;
          for (u32 t = 0; t < layers[l]->out; t++) {
            layers[l]->b[t] -= *M(dp[l + 1], 0, t) * alpha;
            for (u32 u = 0; u < layers[l]->in; u++) {
              *M(layers[l]->W, t, u) -= z[u] * *M(dp[l + 1], 0, u);
            }
          }

          mat_mul(dp[l + 1], layers[l]->W, dp[l]);
        }
      }
    }

    printf("epoch: %d, cost: %f\n", epoch, cost);
  }

  for (u32 i = 0; i < L; i++) {
    free(activations[i]);
    free_matrix(dp[i]);
  }

  free_matrix(dp[L]);

  free(activations);
}
