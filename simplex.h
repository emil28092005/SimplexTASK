#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <vector>
#include "tools/matrix.h"

enum solver_state
{
  unbounded,
  bounded,
  unsolvable
};

struct Result
{
  solver_state state;
  Vector solution;
  double objective_function_value;
  bool maximize;
};

void _printInitialInputs(Vector &C, Matrix &A, Vector &b);
void _stopIterating(Matrix &generalMatrix, std::vector<int> &basicVars, Result &result);
Result simplex(Vector &C, Matrix &A, Vector &b, double eps = 0.01, bool maximize = true);

#endif // SIMPLEX_H