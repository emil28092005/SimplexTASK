#include <iostream>
#include "tools/matrix.h"
#include "tools/math.h"

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

int main() {
    int n, m;
    std::cin >> n;
    std::cin >> m;

    ColumnVector C(n);
    Matrix A(n, m);
    ColumnVector b(n);
    double eps;
    double eps_default;
    std::cin >> C;
    std::cin >> A;
    std::cin >> b;

    std::cout << "Вектор C: " << C << std::endl;
    std::cout << "Вектор b: " << b << std::endl;

    std::cout << "Матрица A: " << A << std::endl;

    Matrix E = createGeneralMatrix(A, C, b);

    std::cout << "Новая матрица:" << E << std::endl;

    return 0;
}
