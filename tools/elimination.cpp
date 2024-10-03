#include "elimination.h"
#include "math.h"

FracturedMatrix::FracturedMatrix(const FracturedMatrix& other) : A(other.A), C(other.C), b(other.b), pivot_column_index(other.pivot_column_index), pivot_row_index(other.pivot_row_index) {}
FracturedMatrix::FracturedMatrix(Matrix A, Vector C, Vector b, int pivot_column_index, int pivot_row_index) : A(A), C(C), b(b), pivot_column_index(pivot_column_index), pivot_row_index(pivot_row_index) {}
FracturedMatrix& FracturedMatrix::operator=(const FracturedMatrix& other) {
    A = other.A;
    C = other.C;
    b = other.b;
    pivot_column_index = other.pivot_column_index;
    pivot_row_index = other.pivot_row_index;
    return *this;
}

DestroyMatrix destroyGeneralMatrix(Matrix& generalMatrix) {
    int rows = generalMatrix.getRows();
    int cols = generalMatrix.getColumns();

    Matrix A(rows - 1, cols - 1);
    Vector C(cols - 1);
    Vector b(rows - 1);

    for (int j = 0; j < cols - 1; ++j) {
        C[j] = generalMatrix[0][j];
    }

    for (int i = 1; i < rows; ++i) {
        b[i - 1] = generalMatrix[i - 1][cols - 1];
    }

    for (int i = 1; i < rows; ++i) {
        for (int j = 0; j < cols - 1; ++j) {
            A[i - 1][j] = generalMatrix[i][j];
        }
    }

    return {A, C, b};
}

Matrix createGeneralMatrix(Matrix& A, Vector& C, Vector& b) {
    Matrix generalMatrix(A.getRows() + 1, A.getColumns() + 1);
    for (int i = 0; i < A.getColumns(); i++) {
        generalMatrix[0][i] = C[i];
    }

    // For objective function (j=0) the value is set to zero automatically
    for (int j = 1; j < A.getRows() + 1; j++) {
        generalMatrix[j][A.getColumns()] = b[j-1];
    }

    for (int i = 0; i < A.getRows(); i++) {
        for (int j = 0; j < A.getColumns(); j++) {
            generalMatrix[i + 1][j] = A[i][j];
        }
    }

    return generalMatrix;
}

void elimination(Matrix& generalMatrix, int pivot_row_index, int pivot_column_index) {

    int rows = generalMatrix.getRows();
    int cols = generalMatrix.getColumns();

    double pivotElement = generalMatrix[pivot_row_index][pivot_column_index];

    for (int j = 0; j < cols; ++j) {
        generalMatrix[pivot_row_index][j] /= pivotElement;
    }

    for (int i = 0; i < rows; ++i) {
        if (i == pivot_row_index) 
            continue;

        double pivotColumnCoefficient = generalMatrix[i][pivot_column_index];

        for (int j = 0; j < cols; ++j) {
            generalMatrix[i][j] -= pivotColumnCoefficient * generalMatrix[pivot_row_index][j];
        }
    }
}

