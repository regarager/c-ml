#ifndef LOGREG_H
#define LOGREG_H

#include "util.h"

typedef struct {
  int n;
  vec w;
  double b;
} LogisticRegression;

void LgRInit(LogisticRegression *lr, int n);
double LgREval(LogisticRegression *lr, vec x);
double LgRCost(LogisticRegression *lr, vec x, double y);
void LgRFit(LogisticRegression *lr, vec X, vec y, int k, int epochs,
            double alpha);

#endif
