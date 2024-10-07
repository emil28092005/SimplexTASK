#ifndef ELIMINATION_H
#define ELIMINATION_H

#include "matrix.h"


struct FracturedMatrix {
	Matrix A;
	Vector C;
	Vector b;
	int pivot_column_index;
	int pivot_row_index;
	FracturedMatrix() = default;
	FracturedMatrix(const FracturedMatrix& other);
	FracturedMatrix(Matrix A, Vector C, Vector b, int pivot_column_index, int pivot_row_index);
	FracturedMatrix& operator=(const FracturedMatrix& other);
};

struct DestroyMatrix {
    Matrix A;
    Vector C;
    Vector b;
};

DestroyMatrix disassembleGeneralMatrix(Matrix& generalMatrix);
void elimination(Matrix&, int pivot_row_index, int pivot_column_index);
Matrix createGeneralMatrix(Matrix& A, Vector& C, Vector& b);


#endif //ELIMINATION_H
