#ifndef TOOLS_MATRIX_H
#define TOOLS_MATRIX_H

// some functions for matrix interaction
#include <iostream>
#include <vector>

/**
* Vector is a class to represent
* a column vector with n rows.
*/


class Vector {
protected:
	// Number of rows in vector
	int rows;
	// Number of columns in vector
	int columns;
	// Matrix representation as vector of vectors of integers
	std::vector<double> vector;
public:
	Vector(int n);

	Vector(const Vector& other);

	Vector(std::initializer_list<double>);

	/* Getter for the number of rows */
	int size() const;

	double& operator[](int row);

	Vector& operator=(const Vector& other);

	Vector operator+(Vector& other);

	Vector operator-(Vector& other);

	/* Input operator reads element of vector */
	friend std::istream& operator>>(std::istream& cin, Vector& vectorObj);

	/* Output operator prints elements of the vector
	* in a row separated with a space (no space at the end of the line)
	*/
	friend std::ostream& operator<<(std::ostream& cout, Vector& vectorObj);
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
	std::vector<Vector> matrix;
public:
	Matrix(int n, int m);

	Matrix(const Matrix& other);

	Matrix(std::initializer_list<std::vector<double>>);

	/* Getter for the number of rows */
	int getRows() const;

	/* Getter for the number of columns */
	int getColumns() const;

	Vector& operator[](int row);

	Matrix& operator=(const Matrix& other);

	Matrix operator+(Matrix& other) const;

	Matrix operator-(Matrix& other) const;

	Matrix operator*(Matrix& other) const;

	/* Matrix-Vector multiplication */
	Vector operator*(Vector other) const;

	/* Produces transposed version of the matrix */
	Matrix transpose() const;

	/* Input operator reads element of matrix row by row */
	friend std::istream& operator>>(std::istream& cin, Matrix& matrixObj);

	/* Output operator prints elements of the matrix
	* row by row separated with a space (no space at the end of each line)
	*/
	friend std::ostream& operator<<(std::ostream& cout, Matrix& matrixObj);
};

void showMatrix(Matrix);

#endif  // TOOLS_MATRIX_H
