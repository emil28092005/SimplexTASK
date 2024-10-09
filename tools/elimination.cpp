#include "elimination.h"
#include "math.h"

FracturedMatrix::FracturedMatrix(const FracturedMatrix &other) : A(other.A), C(other.C), b(other.b), pivot_column_index(other.pivot_column_index), pivot_row_index(other.pivot_row_index) {}
FracturedMatrix::FracturedMatrix(Matrix A, Vector C, Vector b, int pivot_column_index, int pivot_row_index) : A(A), C(C), b(b), pivot_column_index(pivot_column_index), pivot_row_index(pivot_row_index) {}
FracturedMatrix &FracturedMatrix::operator=(const FracturedMatrix &other)
{
    A = other.A;
    C = other.C;
    b = other.b;
    pivot_column_index = other.pivot_column_index;
    pivot_row_index = other.pivot_row_index;
    return *this;
}

DestroyMatrix disassembleGeneralMatrix(Matrix &generalMatrix)
{
    int rows = generalMatrix.getRows();
    int cols = generalMatrix.getColumns();

    Matrix A(rows - 1, cols - 1);
    Vector C(cols - 1);
    Vector b(rows);

    for (int j = 0; j < cols - 1; ++j)
    {
        C[j] = generalMatrix[0][j];
    }

    for (int i = 0; i < rows; ++i)
    {
        b[i] = generalMatrix[i][cols - 1];
    }

    for (int i = 1; i < rows; ++i)
    {
        for (int j = 0; j < cols - 1; ++j)
        {
            A[i - 1][j] = generalMatrix[i][j];
        }
    }

    return {A, C, b};
}

Matrix createGeneralMatrix(Matrix &A, Vector &C, Vector &b)
{

    int m = A.getRows() + 1;
    int n = A.getColumns() + A.getRows() + 1;
    Matrix generalMatrix(m, n);

    for (int i = 0; i < n; i++)
    {
        if (i < C.size())
        {
            generalMatrix[0][i] = C[i];
        }
        else
        {
            generalMatrix[0][i] = 0;
        }
    }

    // For objective function (j=0) the value is set to zero one step before
    for (int j = 1; j < m; j++)
    {
        generalMatrix[j][n - 1] = b[j - 1];
    }

    int k = 0;
    for (int i = 0; i < m - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (j < A.getColumns())
            {
                generalMatrix[i + 1][j] = A[i][j];
            }
            else
            {
                generalMatrix[i + 1][j] = 0;
            }
        }

        generalMatrix[i + 1][A.getColumns() + k] = 1;
        ++k;
    }

    return generalMatrix;
}

void elimination(Matrix &generalMatrix, int pivot_row_index, int pivot_column_index)
{

    int rows = generalMatrix.getRows();
    int cols = generalMatrix.getColumns();

    double pivotElement = generalMatrix[pivot_row_index][pivot_column_index];

    for (int j = 0; j < cols; ++j)
    {
        generalMatrix[pivot_row_index][j] /= pivotElement;
    }

    for (int i = 0; i < rows; ++i)
    {
        if (i == pivot_row_index)
            continue;

        double pivotColumnCoefficient = generalMatrix[i][pivot_column_index];

        for (int j = 0; j < cols; ++j)
        {
            generalMatrix[i][j] -= pivotColumnCoefficient * generalMatrix[pivot_row_index][j];
        }
    }
}
