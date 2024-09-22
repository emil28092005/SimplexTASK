#include <iostream>
#include "tools/matrix.h"
#include "tools/math.h"
#include "simplex.h"

int main() {
    Vector C = {5, 4, 0, 0};
    Matrix A = {{6, 4, 1, 0, 0, 0}, {1, 2, 0, 1, 0, 0}, {-1, 1, 0, 0, 1, 0}, {0, 1, 0, 0, 0, 1}};
    Vector b = {24, 6, 1, 2};

    Result result = Simplex(C, A, b);
    if(result.state == bounded) {

        if(result.solution == nullptr) {
            std::cout << "HUYN: Khong tim duoc nghiem" << std::endl;
        }
        std::cout << *result.solution << std::endl;
        std::cout << result.objective_fucntion_value << std::endl;

    }

    return 0;
}
