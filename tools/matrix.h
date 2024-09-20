#ifndef TOOLS_MATRIX_H
#define TOOLS_MATRIX_H

// some functions for matrix interaction
#include <iostream>
#include <vector>

/**
* ColumnVector is a class to represent
* a column vector with n rows.
*/
class ColumnVector {
protected:
	// Number of rows in vector
	int rows;
	// Number of columns in vector
	int columns;
	// Matrix representation as vector of vectors of integers
	std::vector<double> columnVector;
public:
	ColumnVector(int n);

	ColumnVector(const ColumnVector& other);

	/* Getter for the number of rows */
	int getRows() const;

	/* Getter for the number of columns */
	int getColumns() const;

	double& operator[](int row);

	ColumnVector& operator=(const ColumnVector& other);

	ColumnVector operator+(ColumnVector& other);

	ColumnVector operator-(ColumnVector& other);

	/* Input operator reads element of vector */
	friend std::istream& operator>>(std::istream& cin, ColumnVector& vectorObj);

	/* Output operator prints elements of the vector
	* in a row separated with a space (no space at the end of the line)
	*/
	friend std::ostream& operator<<(std::ostream& cout, ColumnVector& vectorObj);
};

/**
* Class Matrix represents
* a matrix of size n x m
* of type integer.
*/
class Matrix {
protected:
	// Number of rows in matrix
	int rows;
	// Number of columns in matrix
	int columns;
	// Matrix representation as vector of vectors of integers
	std::vector<ColumnVector> matrix;
public:
	Matrix(int n, int m);

	Matrix(const Matrix& other);

	/* Getter for the number of rows */
	int getRows() const;

	/* Getter for the number of columns */
	int getColumns() const;

	ColumnVector& operator[](int row);

	Matrix& operator=(const Matrix& other);

	Matrix operator+(Matrix& other) const;

	Matrix operator-(Matrix& other) const;

	Matrix operator*(Matrix& other) const;

	/* Matrix-Vector multiplication */
	ColumnVector operator*(ColumnVector other) const;

	/* Produces transposed version of the matrix */
	Matrix transpose() const;

	/* Input operator reads element of matrix row by row */
	friend std::istream& operator>>(std::istream& cin, Matrix& matrixObj);

	/* Output operator prints elements of the matrix
	* row by row separated with a space (no space at the end of each line)
	*/
	friend std::ostream& operator<<(std::ostream& cout, Matrix& matrixObj);
};

#endif  // TOOLS_MATRIX_H
