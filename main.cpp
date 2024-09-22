#include <iostream>
#include "tools/matrix.h"
#include "tools/math.h"
#include "simplex.h"

int main() {
    Vector C(6);
    Matrix A(6, 4);
    int Carr[C.size()] = {-5, -4, 0, 0, 0, 0};
    for (int i = 0; i < C.size(); ++i) {
        C[i] = Carr[i];
    }
    A = {{6, 4, 1, 0, 0, 0}, {1, 2, 0, 1, 0, 0}, {-1, 1, 0, 0, 1, 0}, {0, 1, 0, 0, 0, 1}};
    Vector b(A.getRows());
    b = {24, 6, 1, 2};
    std::cout << A << std::endl;
    std::cout << C << std::endl;
    return 0;
}
