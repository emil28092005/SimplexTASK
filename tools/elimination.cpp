#include "elimination.h"
#include "matrix.h"
#include "math.h"

Matrix createGeneralMatrix(Matrix& A, ColumnVector& C, ColumnVector& b) {
    Matrix generalMatrix(A.getRows() + 1, A.getColumns() + 1);
    for (int i = 0; i < A.getColumns(); i++) {
        generalMatrix[0][i] = C[i];
    }

    generalMatrix[0][A.getColumns()] = 0;
    for (int j = 0; j < A.getRows(); j++) {
        generalMatrix[j + 1][A.getColumns()] = b[j];
    }

    for (int i = 0; i < A.getRows(); i++) {
        for (int j = 0; j < A.getColumns(); j++) {
            generalMatrix[i + 1][j] = A[i][j];
        }
    }

    return generalMatrix;
}

Matrix elimination(Matrix A, ColumnVector C, ColumnVector b, int pivot_column_index, int pivot_row_index, double eps) {
    Matrix generalMatrix = createGeneralMatrix(A, C, b);
    
    
    return generalMatrix;
}

