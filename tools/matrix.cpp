#include "matrix.h"

void showMatrix(Matrix matrix) {
  int maxNumberLength = 1;
  for (size_t y = 0; y < matrix.getRows(); y++) {
    for (size_t x = 0; x < matrix.getColumns(); x++) {
      if (std::to_string(matrix[y][x]).length() > maxNumberLength) {
        maxNumberLength = std::to_string(matrix[y][x]).length();
      }
    }
  }
  std::cout << maxNumberLength << std::endl;
  for (size_t y = 0; y < matrix.getRows(); y++) {
    std::string row = "";
    for (size_t x = 0; x < matrix.getColumns(); x++) {
      std::string strNumber = std::to_string(matrix[y][x]);
      bool spaceRight = true;
      while (strNumber.length() < maxNumberLength) {
        if (spaceRight) {
          strNumber += " ";
        }
        else {
          strNumber = " " + strNumber;
        }
        spaceRight = !spaceRight;
        strNumber = "" + strNumber;

      }
      if (matrix[y][x] == 0) {
        row += "[\033[0m" + strNumber + "\033[0m] ";
      }
      else if(matrix[y][x] > 0) {
        row += "[\033[32m" + strNumber + "\033[0m] ";
      }else {
        row += "[\033[31m" + strNumber + "\033[0m] ";
      }

    }
    std::cout << row << std::endl;
  }
}

Vector::Vector(int n) {
  rows = n;
  columns = 1;
  vector.resize(n);
}

Vector::Vector(const Vector& other) {
  rows = other.rows;
  columns = other.columns;
  vector = other.vector;
}

Vector::Vector(std::initializer_list<double> init) {
  rows = init.size();
  columns = 1;
  vector = std::vector<double>(rows);

  auto it = init.begin();
  
  for (size_t i = 0; i < init.size(); ++i) {
    vector[i] = *it++;
  }
}

int Vector::size() const {
  return rows;
}

double& Vector::operator[](int row) {
  return vector[row];
}

Vector& Vector::operator=(const Vector& other) {
  rows = other.rows;
  columns = other.columns;
  vector = other.vector;
  return *this;
}

Vector Vector::operator+(Vector& other) {
  if (rows != other.rows) {
    throw std::runtime_error("Error: the dimensional problem occurred");
  }
  Vector result(rows);
  for (int i = 0; i < rows; ++i) {
    result[i] = vector[i] + other[i];
  }

  return result;
}

Vector Vector::operator-(Vector& other) {
  if (rows != other.rows) {
    throw std::runtime_error("Error: the dimensional problem occurred");
  }
  Vector result(rows);
  for (int i = 0; i < rows; ++i) {
    result[i] = vector[i] - other[i];
  }

  return result;
}

std::istream& operator>>(std::istream& cin, Vector& vectorObj) {
  for (int i = 0; i < vectorObj.rows; ++i) {
    cin >> vectorObj[i];
  }
  return cin;
}

std::ostream& operator<<(std::ostream& cout, Vector& vectorObj) {
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
  matrix.resize(n, Vector(m));
  for (auto& row : matrix) {
    row = Vector(m);
  }
}

Matrix::Matrix(const Matrix& other) {
  rows = other.rows;
  columns = other.columns;
  matrix = other.matrix;
}

Matrix::Matrix(std::initializer_list<std::vector<double>> init) {
  rows = init.size();
  auto it = init.begin();
  columns = it->size();
  matrix = std::vector<Vector>(rows, Vector(columns));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      matrix[i][j] = it->operator[](j);
    }
    ++it;
  }
}

int Matrix::getRows() const {
  return rows;
}

int Matrix::getColumns() const {
  return columns;
}

Vector& Matrix::operator[](int row) {
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

Vector Matrix::operator*(Vector other) const {
  if (columns != other.size()) {
    throw std::runtime_error("Error: the dimensional problem occurred");
  }

  Vector result(rows);
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
