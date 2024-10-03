#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <vector>
#include "tools/matrix.h"

enum solver_state {
  unbounded,
  bounded
};

struct Result {
  solver_state state;
  Vector *solution;
  double objective_fucntion_value;
};

Result Simplex(Vector C, Matrix A, Vector b, double eps = 0.01, bool maximize = true);

#endif // SIMPLEX_H