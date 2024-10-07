#include <iostream>
#include "tools/matrix.h"
#include "tools/math.h"
#include "simplex.h"


void printInitialInputs(Vector C, Matrix A, Vector b) {

}
int main() {
    // TODO: Initially should be positive

    Vector C = {5, 4, 0, 0, 0, 0};

    Matrix A = {
             {6, 4, 1, 0, 0, 0},
             {1, 2, 0, 1, 0, 0},
             {-1, 1, 0, 0, 1, 0},
             {0, 1, 0, 0, 0, 1}
                };

    Vector b = {24, 6, 1, 2};

    for (int i = 0; i < b.size(); i++) {
        if (b[i] < 0) {
            std::cout << "Error: method is not applicable" << std::endl;
            return 1;
        }
    }

    //Matrix test = {{1, -1, -2}, {1, 1, -2}, {1, -1, 2}};

    //showMatrix(test);
    

    Result result = Simplex(C, A, b, 0.1, true);



    if(result.state == bounded) {
        if(result.solution == nullptr) {
            std::cout << "Error: no solution value is returned" << std::endl;
            return 1;
        }
        std::cout << *result.solution << std::endl;
        std::cout << result.objective_fucntion_value << std::endl;

        delete result.solution;
    }
    else {
        std::cout << "Error: unbounded" << std::endl;
        return 1;
    }
    //std::cout << "asdasd" << std::endl;

    return 0;
}


