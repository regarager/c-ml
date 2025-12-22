#include <math.h>
#include <stdlib.h>

#include "util.h"

double urandom_float() { return 1.0 * rand() / RAND_MAX; }
double random_float() { return urandom_float() * 2 - 1; }
double sigmoid(double x) { return 1 / (1 + exp(-x)); }
double d_sigmoid(double y) { return y * (1 - y); };
double pass(double x) { return x; }
double d_pass(double x) { return 1; }
