#include <iostream>
#include "tools/matrix.h"
#include "tools/math.h"

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

int main() {
    int n, m;
    std::cin >> n;
    std::cin >> m;

    ColumnVector C(n);
    Matrix A(m - 1, n);
    ColumnVector b(m);
    double eps;
    double eps_default;
    std::cin >> C;
    std::cin >> b;
    std::cin >> A;

    std::cout << "Вектор C: " << C << std::endl;
    std::cout << "Вектор b: " << b << std::endl;

    std::cout << "Матрица A: " << A << std::endl;

    Matrix E = createGeneralMatrix(A, C, b);
    std::cout << "Матрица E: " << E << std::endl;

    DestroyMatrix destroyed = destroyGeneralMatrix(E);
    std::cout << "Вектор C: " << destroyed.C << std::endl;
    std::cout << "Вектор b: " << destroyed.b << std::endl;

    std::cout << "Матрица A: " << destroyed.A << std::endl;


    return 0;
}
