#include <iostream>
#include "tools/matrix.h"
#include "tools/math.h"

int main() {
    int n, m;
    std::cin >> n;
    std::cin >> m;

    ColumnVector C(n);
    Matrix A(n, m);
    ColumnVector b(n);
    double eps;
    double eps_default;
    std::cin >> A;

    std::cout << "Вектор C: " << C << std::endl;

    std::cout << "Матрица A: " << A << std::endl;

    Matrix B(2, 2);
    std::cout << B << std::endl;
    return 0;
}
