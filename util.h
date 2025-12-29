#ifndef UTIL_H
#define UTIL_H

#include "base/types.h"

f64 urandom_float();
f64 random_float();
f64 sigmoid(f64 x);
f64 d_sigmoid(f64 y);
f64 pass(f64 x);
f64 d_pass(f64 x);

#endif
