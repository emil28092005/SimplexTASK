#include "matrix.h"

ColumnVector::ColumnVector(int n) {
  rows = n;
  columns = 1;
  columnVector.resize(n);
}

ColumnVector::ColumnVector(const ColumnVector& other) {
  rows = other.rows;
  columns = other.columns;
  columnVector = other.columnVector;
}

int ColumnVector::getRows() const {
  return rows;
}

int ColumnVector::getColumns() const {
  return columns;
}

double& ColumnVector::operator[](int row) {
  return columnVector[row];
}

ColumnVector& ColumnVector::operator=(const ColumnVector& other) {
  rows = other.rows;
  columns = other.columns;
  columnVector = other.columnVector;
  return *this;
}

ColumnVector ColumnVector::operator+(ColumnVector& other) {
  if (rows != other.rows) {
    throw std::runtime_error("Error: the dimensional problem occurred");
  }
  ColumnVector result(rows);
  for (int i = 0; i < rows; ++i) {
    result[i] = columnVector[i] + other[i];
  }

  return result;
}

ColumnVector ColumnVector::operator-(ColumnVector& other) {
  if (rows != other.rows) {
    throw std::runtime_error("Error: the dimensional problem occurred");
  }
  ColumnVector result(rows);
  for (int i = 0; i < rows; ++i) {
    result[i] = columnVector[i] - other[i];
  }

  return result;
}

std::istream& operator>>(std::istream& cin, ColumnVector& vectorObj) {
  for (int i = 0; i < vectorObj.rows; ++i) {
    cin >> vectorObj[i];
  }
  return cin;
}

std::ostream& operator<<(std::ostream& cout, ColumnVector& vectorObj) {
  for (int i = 0; i < vectorObj.rows; ++i) {
    if (i == vectorObj.rows - 1) {
      cout << vectorObj[i] << std::endl;
    }
    else {
      cout << vectorObj[i] << ' ';
    }
  }
  return cout;
}

Matrix::Matrix(int n, int m) {
  rows = n;
  columns = m;
  matrix.resize(n, ColumnVector(m));
  for (auto& row : matrix) {
    row = ColumnVector(m);
  }
}

Matrix::Matrix(const Matrix& other) {
  rows = other.rows;
  columns = other.columns;
  matrix = other.matrix;
}

int Matrix::getRows() const {
  return rows;
}

int Matrix::getColumns() const {
  return columns;
}

ColumnVector& Matrix::operator[](int row) {
  return matrix[row];
}

Matrix& Matrix::operator=(const Matrix& other) {
  rows = other.rows;
  columns = other.columns;
  matrix = other.matrix;
  return *this;
}

Matrix Matrix::operator+(Matrix& other) const {
  if (rows != other.rows || columns != other.columns) {
    throw std::runtime_error("Error: the dimensional problem occurred");
  }
  Matrix result(rows, columns);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      auto x = matrix[i];
      auto y = other[i];
      result[i][j] = x[j] + y[j];
    }
  }

  return result;
}

Matrix Matrix::operator-(Matrix& other) const {
  if (rows != other.rows || columns != other.columns) {
    throw std::runtime_error("Error: the dimensional problem occurred");
  }
  Matrix result(rows, columns);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      auto x = matrix[i];
      auto y = other[i];
      result[i][j] = x[j] - y[j];
    }
  }

  return result;
}

Matrix Matrix::operator*(Matrix& other) const {
  if (columns != other.rows) {
    throw std::runtime_error("Error: the dimensional problem occurred");
  }

  Matrix result(rows, other.columns);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < other.columns; ++j) {
      result[i][j] = 0;
      for (int k = 0; k < columns; ++k) {
        auto x = matrix[i];
        auto y = other[k];
        result[i][j] += x[k] * y[j];
      }
    }
  }

  return result;
}

ColumnVector Matrix::operator*(ColumnVector other) const {
  if (columns != other.getRows()) {
    throw std::runtime_error("Error: the dimensional problem occurred");
  }

  ColumnVector result(rows);
  for (int i = 0; i < rows; ++i) {
    result[i] = 0;
    for (int k = 0; k < columns; ++k) {
      auto x = matrix[i];
      result[i] += x[k] * other[k];
    }
  }

  return result;
}

Matrix Matrix::transpose() const {
  Matrix result(columns, rows);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      auto x = matrix[i];
      result[j][i] = x[j];
    }
  }

  return result;
}

std::istream& operator>>(std::istream& cin, Matrix& matrixObj) {
  for (int i = 0; i < matrixObj.rows; ++i) {
    for (int j = 0; j < matrixObj.columns; ++j) {
      cin >> matrixObj[i][j];
    }
  }
  return cin;
}

std::ostream& operator<<(std::ostream& cout, Matrix& matrixObj) {
  for (int i = 0; i < matrixObj.rows; ++i) {
    for (int j = 0; j < matrixObj.columns; ++j) {
      if (j == matrixObj.columns - 1) {
        cout << matrixObj[i][j] << std::endl;
      }
      else {
        cout << matrixObj[i][j] << ' ';
      }
    }
  }
  return cout;
}
