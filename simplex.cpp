#include <algorithm>
#include <iostream>
#include "tools/matrix.h"
#include "tools/math.h"
#include "tools/elimination.h"

enum solver_state {
	unbounded,
	bounded
};

struct Result {
	solver_state state;
	Vector *solution;
	double objective_function_value;
};

Result Simplex(Vector C, Matrix A, Vector b, double eps = 0.01, bool maximize=true) {

    int m = A.getRows();

	Result result{};
	std::vector<int> basicVars(A.getColumns() - A.getRows());
	basicVars[0] = -1;

	for (int i = 1; i < basicVars.size(); i++) {
		basicVars[i] = static_cast<int>(basicVars.size()) + i;
	}

	while (true) {
		//3
		int pivot_column_index = 0;
		pivot_column_index = max_index(C);

		if (A[0][pivot_column_index] >= 0) {

			result.state = bounded;
			result.solution = new Vector(C.size());
			for (int i = 0; i < C.size(); i++) {
				result.solution->operator[](i) = 0;
			}
			for (int i = 1; i < basicVars.size(); i++) {
				if (basicVars[i] <= C.size()) {
					(*result.solution)[basicVars[i]] = b.size() - 1;
				}
			}
			result.objective_function_value = b[0];
			return result;
		}

		//4
		Vector ratio_vector(m);
		for (int i = 0; i < m; i++) {
			ratio_vector[i] = b[i] / A[i][pivot_column_index];
		}
		int pivot_row_index = min_index(ratio_vector);

		basicVars[pivot_row_index] = pivot_column_index;

		//5
		FracturedMatrix fractured_matrix(elimination(A, C, b, pivot_column_index, pivot_row_index));
		A = fractured_matrix.A;
		C = fractured_matrix.C;
		b = fractured_matrix.b;
		pivot_column_index = fractured_matrix.pivot_column_index;
		pivot_row_index = fractured_matrix.pivot_row_index;
	}

	return result;

	/*
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
		result.solution = new Vector(C.getRows());
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
	*/
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
