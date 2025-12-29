#include <math.h>
#include <stdlib.h>

#include "util.h"

f64 urandom_float() { return 1.0 * rand() / RAND_MAX; }
f64 random_float() { return urandom_float() * 2 - 1; }
f64 sigmoid(f64 x) { return 1 / (1 + exp(-x)); }
f64 d_sigmoid(f64 y) { return y * (1 - y); }
f64 pass(f64 x) { return x; }
f64 d_pass(f64 x) { return 1; }
