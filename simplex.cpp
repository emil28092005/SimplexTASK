#include <algorithm>
#include <iostream>
#include "tools/matrix.h"
#include "tools/math.h"
#include "tools/elimination.h"

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

void _stopIterating(Matrix &generalMatrix, Vector &C, std::vector<int> &basicVars, solver_state state, Result &result)
{
	DestroyMatrix destroyedGeneralMatrix = disassembleGeneralMatrix(generalMatrix);
	Matrix _A = destroyedGeneralMatrix.A;
	Vector _C = destroyedGeneralMatrix.C;
	Vector _b = destroyedGeneralMatrix.b;

	result.state = state;
	if (state == bounded)
	{
		result.solution = Vector(C.size());
		for (int i = 0; i < C.size(); i++)
		{
			result.solution[i] = 0;
		}
		for (size_t i = 1; i < basicVars.size(); i++)
		{
			if (basicVars[i] < C.size())
			{
				result.solution[basicVars[i]] = _b[i];
			}
		}

		result.objective_function_value = _b[0];
	}
	else
	{
		result.solution = Vector({0});
		result.objective_function_value = 0;
	}
}

/*
	Implementation of the Simplex method.
*/
Result simplex(Vector &C, Matrix &A, Vector &b, double eps = 0.01, bool maximize = true)
{

	if (maximize == true)
	{
		for (int i = 0; i < C.size(); i++)
		{
			C[i] = -C[i];
		}
	}
	Result result{};
	result.maximize = maximize;

	Matrix generalMatrix = createGeneralMatrix(A, C, b);
	std::cout << generalMatrix;
	std::vector<int> basicVars(generalMatrix.getRows());
	basicVars[0] = -1;

	for (int i = 0; i < b.size(); ++i)
	{
		if (b[i] < 0)
		{
			_stopIterating(generalMatrix, C, basicVars, unsolvable, result);
			return result;
		}
	}

	for (size_t i = 1; i < basicVars.size(); i++)
	{
		basicVars[i] = static_cast<int>(basicVars.size()) + i;
	}
	int iterationCount = 0;
	while (true)
	{
		// 3
		iterationCount++;
		int pivot_column_index = 0;

		pivot_column_index = min_index(generalMatrix[0]);

		if (generalMatrix[0][pivot_column_index] >= 0)
		{
			_stopIterating(generalMatrix, C, basicVars, bounded, result);
			if (!maximize)
			{
				result.objective_function_value = -result.objective_function_value;
			}
			return result;
		}

		// 4
		Vector ratio_vector(generalMatrix.getRows());
		for (int i = 1; i < generalMatrix.getRows(); i++)
		{
			if (generalMatrix[i][pivot_column_index] != 0)
			{
				ratio_vector[i] = generalMatrix[i][generalMatrix.getColumns() - 1] / generalMatrix[i][pivot_column_index];
				if (std::abs(ratio_vector[i]) < eps)
				{
					ratio_vector[i] = 0;
				}
			}
			else
			{
				ratio_vector[i] = 0;
			}
		}
		ratio_vector[0] = 0;

		int pivot_row_index = min_index_positive(ratio_vector);

		// No leaving variable exists
		if (pivot_row_index == -1)
		{
			_stopIterating(generalMatrix, C, basicVars, unbounded, result);
			return result;
		}

		basicVars[pivot_row_index] = pivot_column_index;

		// 5
		elimination(generalMatrix, pivot_row_index, pivot_column_index);
		std::cout << "Iteration " << iterationCount << " " << std::endl;
		;
		std::cout << generalMatrix;
	}
	return result;
}
