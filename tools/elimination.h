#ifndef ELIMINATION_H
#define ELIMINATION_H

#include "matrix.h"


struct FracturedMatrix {
	Matrix A;
	Vector C;
	Vector b;
	int pivot_column_index;
	int pivot_row_index;
	FracturedMatrix();
	FracturedMatrix(const FracturedMatrix& other);
	FracturedMatrix(Matrix A, Vector C, Vector b, int pivot_column_index, int pivot_row_index);
	FracturedMatrix& operator=(const FracturedMatrix& other);
};

struct DestroyMatrix {
    Matrix A;
    Vector C;
    Vector b;
};

DestroyMatrix destroyGeneralMatrix(Matrix& generalMatrix);
FracturedMatrix elimination(Matrix A, Vector C, Vector b, int pivot_column_index, int pivot_row_index);
Matrix createGeneralMatrix(Matrix& A, Vector& C, Vector& b);


#endif //ELIMINATION_H
