# c-ml

Basic ML implementations in C

## Examples

These examples are just a proof of concept, therefore they are very simple.

**Note that all data is passed as a `vector_t` value, even if they are matrices mathematically.**

### Linear Regression

In this example we use linear regression to approximate `f(x, y) = x + 2y` with added noise.

```c
#include "linear.h"
#include "base/types.h"
#include "util.h"

int main() {
    linear_t* lr = make_linr(2);

    u32 k = 100, epochs = 20; // number of data points; epochs
    f64 alpha = 0.01;

    vector_t X = vector(k * 2);
    vector_t y = vector(k);

    for (u32 i = 0; i < 10; i++) {
        for (u32 j = 0; j < 10; j++) {
            u32 index = 10 * i + j;
            X[2 * index] = i;
            X[2 * index + 1] = j;
            y[index] = i + 2 * j + random_float();
        }
    }

    linr_fit(lr, X, y, k, epochs, alpha);
}
```

Output:
```
epoch: 1, cost: 78.499436
epoch: 2, cost: 20.135432
epoch: 3, cost: 5.295783
epoch: 4, cost: 1.519915
epoch: 5, cost: 0.556851
epoch: 6, cost: 0.309251
epoch: 7, cost: 0.243933
...
epoch: 19, cost: 0.205783
epoch: 20, cost: 0.205271
```


### Logistic Regression

In this example we use logistic regression to determine if a number is positive (1.0) or negative (0.0).

```c
#include "logistic.h"
#include "base/types.h"
#include "util.h"

int main() {
  logistic_t *lr = make_logr(1);

  u32 k = 1000, epochs = 100; // number of data points; epochs
  f64 alpha = 1;

  vector_t X = vector(k);
  vector_t y = vector(k);

  for (u32 i = 0; i < k; i++) {
    X[i] = random_float(); // uniformly generated in [-1, 1]
    y[i] = X[i] > 0.0;
  }

  logr_fit(lr, X, y, k, epochs, alpha);
}
```

Output:
```
epoch: 1, cost: 0.146599
epoch: 2, cost: 0.142606
epoch: 3, cost: 0.138609
epoch: 4, cost: 0.134628
epoch: 5, cost: 0.130683
...
epoch: 99, cost: 0.036360
epoch: 100, cost: 0.036182
```

### Neural Network

In this example we use a neural network to approximate the xor function. Specifically, we want `f(0, 0) = f(1, 1) = 0, f(0, 1) = f(1, 0) = 1`.

```c
#include <stdio.h>

#include "matrix.h"
#include "neural.h"
#include "util.h"

int main() {
  u32 L = 4;
  layer_t *l0 = make_layer(2, 10, pass, d_pass);
  layer_t *l1 = make_layer(10, 10, sigmoid, d_sigmoid);
  layer_t *l2 = make_layer(10, 1, pass, d_pass);
  layer_t *l3 = make_layer(1, 1, sigmoid, d_sigmoid);

  neural_t *nn = make_neural(L, l0, l1, l2, l3);

  u32 k = 4;

  // equivalent to all 2-bit pairs
  vector_t X = vector(4 * 2);
  X[0] = 0;
  X[1] = 0;
  X[2] = 0;
  X[3] = 1;
  X[4] = 1;
  X[5] = 0;
  X[6] = 1;
  X[7] = 1;

  vector_t Y = vector(4);
  Y[0] = 0;
  Y[1] = 1;
  Y[2] = 1;
  Y[3] = 0;

  u32 epochs = 1e5;
  f64 alpha = 0.5;
  neural_fit(nn, X, Y, k, epochs, alpha);

  vector_t *activations = init_activations(nn);
  for (u32 i = 0; i < 4; i++) {
    neural_eval(nn, X + 2 * i, activations);
    printf("%f ^ %f = %f\n", (X + 2 * i)[0], (X + 2 * i)[1], activations[3][0]);
  }
}
```

Output:
```
epoch: 1, cost: 0.141103
epoch: 2, cost: 0.138057
epoch: 3, cost: 0.135911
epoch: 4, cost: 0.134431
epoch: 5, cost: 0.133427
...
epoch: 99999, cost: 0.000045
epoch: 100000, cost: 0.000045
0.000000 ^ 0.000000 = 0.008983
0.000000 ^ 1.000000 = 0.997625
1.000000 ^ 0.000000 = 0.988037
1.000000 ^ 1.000000 = 0.011288
```
