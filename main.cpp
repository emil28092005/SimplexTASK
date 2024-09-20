#include <iostream>
#include "tools/matrix.h"


int main() {
    int n, m;
    ColumnVector C(n);
    Matrix A(n, m);
    ColumnVector b(n);
    double eps;
    double eps_default;

    std::cin >> C;
    std::cin >> A;
    std::cin >> b;
    std::cin >> eps;
    return 0;
}
