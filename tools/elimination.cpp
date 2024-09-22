#include "elimination.h"
#include "matrix.h"
#include "math.h"

struct FracturedMatrix {
    Matrix A;
    ColumnVector C;
    ColumnVector b;
    int pivot_column_index;
    int pivot_row_index;
};

struct DestroyMatrix {
    Matrix A;
    ColumnVector C;
    ColumnVector b;
};

DestroyMatrix destroyGeneralMatrix(Matrix& generalMatrix) {
    int rows = generalMatrix.getRows();
    int cols = generalMatrix.getColumns();

    Matrix A(rows - 1, cols - 1);
    ColumnVector C(cols - 1);
    ColumnVector b(rows - 1);

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

Matrix createGeneralMatrix(Matrix& A, ColumnVector& C, ColumnVector& b) {
    Matrix generalMatrix(A.getRows() + 1, A.getColumns() + 1);
    for (int i = 0; i < A.getColumns(); i++) {
        generalMatrix[0][i] = C[i];
    }

    for (int j = 0; j < A.getRows(); j++) {
        generalMatrix[j][A.getColumns()] = b[j];
    }

    for (int i = 0; i < A.getRows(); i++) {
        for (int j = 0; j < A.getColumns(); j++) {
            generalMatrix[i + 1][j] = A[i][j];
        }
    }

    return generalMatrix;
}

FracturedMatrix elimination(Matrix A, ColumnVector C, ColumnVector b, int pivot_column_index, int pivot_row_index) {
    Matrix generalMatrix = createGeneralMatrix(A, C, b);

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

    DestroyMatrix destroyedMatrix = destroyGeneralMatrix(generalMatrix);

    pivot_column_index = max_index(destroyedMatrix.C);
    
    ColumnVector ratio_vector(A.getRows());

    for (int i = 0; i < A.getRows(); i++) {
        if (A[i][pivot_column_index] != 0) {
            ratio_vector[i] = b[i] / A[i][pivot_column_index];
        }
        
        else {
            ratio_vector[i] = 0;
        }
    }

    int pivot_row_index = min_index(ratio_vector);

    return {A, C, b, pivot_column_index, pivot_row_index};


