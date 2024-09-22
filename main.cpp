#include <iostream>
#include "tools/matrix.h"
#include "tools/math.h"
#include "simplex.h"

int main() {
    ColumnVector C(6);
    Matrix A(6, 4);
    int Carr[C.getColumns()] = {-5, -4, 0, 0, 0, 0};
    for (int i = 0; i < C.getRows(); ++i) {
        C[i] = Carr[i];
    }
    A = {{6, 4, 1, 0, 0, 0}, {1, 2, 0, 1, 0, 0}, {-1, 1, 0, 0, 1, 0}, {0, 1, 0, 0, 0, 1}};
    ColumnVector b(A.getRows());
    b = {24, 6, 1, 2};
    std::cout << A << std::endl;
    std::cout << C << std::endl;
    return 0;
}
