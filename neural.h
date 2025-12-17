#ifndef NEURAL_H
#define NEURAL_H

#include "types.h"

typedef struct {
  int in;
  int out;
  vec W;
  vec b;
  func activation;
} Layer;

double pass(double x);

#endif
