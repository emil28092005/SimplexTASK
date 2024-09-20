#include <algorithm>
#include <iostream>
#include "tools/matrix.h"

enum solver_state {
	unbounded,
	bounded
};

struct Result {
	solver_state state;
	ColumnVector *solution;
	double objective_fucntion_value;
};

Result Simplex(ColumnVector C, Matrix A, ColumnVector b, double eps = 0.01, bool maximize) {
	Result result;
	std::vector<int> basicVars(A.getColumns() - A.getRows());
	basicVars[0] = -1;

	for (int i = 1; i < basicVars.size(); i++) {
		basicVars[i] = static_cast<int>(basicVars.size()) + i;
	}

	int kc = 0;
	double temp = A[0][0];
	for (int j = 0; j< A.getColumns(); j++) {
		if (A[0][j] < temp) {
			temp = A[0][j];
			kc = j;
		}
	}

	if (A[0][kc] >= 0) {
		result.state = unbounded;
		result.solution = new ColumnVector(C.getRows());
		for (int i = 0; i < C.getRows(); i++) {
			result.solution->operator[](i) = 0;
		}
		for (int i = 1; i < basicVars.size(); i++) {
			if (basicVars[i] <= C.getRows()) {
				(*result.solution)[basicVars[i]] = b.getRows() - 1;
			}
		}
		result.objective_fucntion_value = b[0];
	}
}

/*
Function_name(C, A, b, eps = eps_default)

Input:
- C: A vector of coefficients of the objective function
- A: A matrix of coefficients of the constraint functions
- b: A vector of right-hand side values
- eps: Approximation accuracy (optional, default = eps_default)

Steps:
1. Print the optimization problem:
   - max (or min) z = C[0] * x1 + C[1] * x2 + ... + C[n] * xn
   - subject to the constraints:
     - A[0] * x <= b[0]
     - A[1] * x <= b[1]
     - ...
     - A[m] * x <= b[m]

2. Initialize:
   - Form the initial tableau by introducing slack variables to convert inequalities into equalities.

3. Iteratively apply the Simplex method:
   - Step 1: Identify the entering variable (most negative coefficient in the objective row).
   - Step 2: Identify the leaving variable (smallest positive ratio of RHS to pivot column).
   - Step 3: Perform pivot operations to update the tableau.

4. Check for optimality or unboundedness:
   - If all coefficients in the objective function row are non-negative, the solution is optimal.
   - If no leaving variable exists, the problem is unbounded.

5. Return:
   - solver_state: {solved, unbounded}
   - x*: Optimal vector of decision variables (if solved)
   - z: Maximum (or minimum) value of the objective function (if solved)

End Function
*/
