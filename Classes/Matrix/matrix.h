#ifndef MATRIX__CLASS__HEADER_H
#define MATRIX__CLASS__HEADER_H
#define MATRIX_SQUARE_MATRIX_IMPLEMENTED

#include <cmath>
#include <iostream>
#include <stdexcept>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <class T, size_t N, size_t M>
class Matrix {
 public:
  T matrix[N][M];

  const T At(const size_t& i, const size_t& j) const {
    if ((i < 0) || (i >= N) || (j < 0) || (j >= M)) {
      throw MatrixOutOfRange{};
    }
    return matrix[i][j];
  }

  T& At(const size_t& i, const size_t& j) {
    if ((i < 0) || (i >= N) || (j < 0) || (j >= M)) {
      throw MatrixOutOfRange{};
    }
    return matrix[i][j];
  }

  size_t ColumnsNumber() const {
    return M;
  }

  size_t RowsNumber() const {
    return N;
  }

  const T operator()(const size_t& i, const size_t& j) const {
    return matrix[i][j];
  }

  T& operator()(const size_t& i, const size_t& j) {
    return matrix[i][j];
  }

  Matrix<T, N, M>& operator+=(const Matrix<T, N, M>& second) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] += second(i, j);
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator-=(const Matrix<T, N, M>& second) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] -= second(i, j);
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator*=(const Matrix<T, M, M>& second) {
    Matrix<T, N, M> result = {};
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        for (size_t q = 0; q < M; ++q) {
          result(i, j) += matrix[i][q] * second(q, j);
        }
      }
    }
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] = result(i, j);
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator*=(const int32_t second) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] *= second;
      }
    }
    return *this;
  }

  Matrix<T, N, M>& operator/=(const int32_t second) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        matrix[i][j] /= second;
      }
    }
    return *this;
  }
};

template <class T, size_t N, size_t M>
Matrix<T, M, N> GetTransposed(const Matrix<T, N, M>& m) {
  Matrix<T, M, N> new_m = {};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      new_m(j, i) = m(i, j);
    }
  }
  return new_m;
}

template <class T, size_t N, size_t M>
std::istream& operator>>(std::istream& in, Matrix<T, N, M>& m) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      in >> m(i, j);
    }
  }
  return in;
}

template <class T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& out, Matrix<T, N, M> m) {
  for (size_t i = 0; i < N; ++i) {
    out << m(i, 0);
    for (size_t j = 1; j < M; ++j) {
      out << " " << m(i, j);
    }
    out << "\n";
  }
  return out;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator+(const Matrix<T, N, M>& first, const Matrix<T, N, M>& second) {
  Matrix<T, N, M> result = {};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(i, j) = first(i, j) + second(i, j);
    }
  }
  return result;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator-(const Matrix<T, N, M>& first, const Matrix<T, N, M>& second) {
  Matrix<T, N, M> result = {};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(i, j) = first(i, j) - second(i, j);
    }
  }
  return result;
}

template <class T, size_t N, size_t M, size_t P>
Matrix<T, N, P> operator*(const Matrix<T, N, M>& first, const Matrix<T, M, P>& second) {
  Matrix<T, N, P> result = {};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < P; ++j) {
      for (size_t q = 0; q < M; ++q) {
        result(i, j) += first(i, q) * second(q, j);
      }
    }
  }
  return result;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator*(const Matrix<T, N, M>& first, const int32_t second) {
  Matrix<T, N, M> result = {};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(i, j) += first(i, j) * second;
    }
  }
  return result;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator*(const int32_t second, const Matrix<T, N, M>& first) {
  Matrix<T, N, M> result = {};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(i, j) += first(i, j) * second;
    }
  }
  return result;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator/(const Matrix<T, N, M>& first, const int32_t second) {
  Matrix<T, N, M> result = {};
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result(i, j) += first(i, j) / second;
    }
  }
  return result;
}

template <class T, size_t N, size_t M>
bool operator==(const Matrix<T, N, M>& first, const Matrix<T, N, M>& second) {
  bool flag = true;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (first(i, j) != second(i, j)) {
        flag = false;
        break;
      }
    }
    if (!flag) {
      break;
    }
  }
  return flag;
}

template <class T, size_t N, size_t M>
bool operator!=(const Matrix<T, N, M>& first, const Matrix<T, N, M>& second) {
  bool flag = false;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (first(i, j) != second(i, j)) {
        flag = true;
        break;
      }
    }
    if (flag) {
      break;
    }
  }
  return flag;
}

template <class T, size_t N>
void Transpose(Matrix<T, N, N>& matrix) {
  T temp = matrix(0, 0);
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = i + 1; j < N; ++j) {
      temp = matrix(j, i);
      matrix(j, i) = matrix(i, j);
      matrix(i, j) = temp;
    }
  }
}

template <class T, size_t N>
T Trace(const Matrix<T, N, N>& matrix) {
  T sum = 0;
  for (size_t i = 0; i < N; ++i) {
    sum += matrix(i, i);
  }
  return sum;
}

template <class T>
Matrix<T, 1, 1> Reduction(const Matrix<T, 1, 1> matrix, size_t line, size_t column) {
  for (size_t i = 0; i < line; ++i) {
    for (size_t j = 0; j < column; ++j) {
    }
  }
  return matrix;
}

template <class T, size_t N>
Matrix<T, N - 1, N - 1> Reduction(const Matrix<T, N, N>& matrix, size_t line, size_t column) {
  Matrix<T, N - 1, N - 1> new_matrix = {};
  for (size_t i = 0; i < line; ++i) {
    for (size_t j = 0; j < column; ++j) {
      new_matrix(i, j) = matrix(i, j);
    }
  }
  for (size_t i = line + 1; i < N; ++i) {
    for (size_t j = 0; j < column; ++j) {
      new_matrix(i - 1, j) = matrix(i, j);
    }
  }
  for (size_t i = 0; i < line; ++i) {
    for (size_t j = column + 1; j < N; ++j) {
      new_matrix(i, j - 1) = matrix(i, j);
    }
  }
  for (size_t i = line + 1; i < N; ++i) {
    for (size_t j = column + 1; j < N; ++j) {
      new_matrix(i - 1, j - 1) = matrix(i, j);
    }
  }
  return new_matrix;
}

template <class T, size_t N>
T Determinant(const Matrix<T, N, N>& matrix) {
  if (N == 1) {
    return matrix(0, 0);
  }
  T det = 0;
  int i = 0;
  for (int j = 0; j < N; ++j) {
    if (matrix(i, j) == 0) {
      continue;
    }
    det += pow(-1, i + j) * matrix(i, j) * Determinant(Reduction(matrix, i, j));
  }
  return det;
}

template <class T, size_t N>
Matrix<T, N, N> GetInversed(const Matrix<T, N, N>& matrix) {
  T main_det = Determinant(matrix);
  if (main_det == 0) {
    throw MatrixIsDegenerateError{};
  }
  std::cout << main_det << "\n";
  Matrix<T, N, N> inversed_matrix = {};
  if (N == 1) {
    inversed_matrix(0, 0) = 1 / matrix(0, 0);
  } else {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        inversed_matrix(i, j) = pow(-1, i + j) * Determinant(Reduction(matrix, j, i));
      }
    }
  }
  return inversed_matrix;
}

template <class T, size_t N>
void Inverse(Matrix<T, N, N>& matrix) {
  T main_det = Determinant(matrix);
  if (main_det == 0) {
    throw MatrixIsDegenerateError{};
  }
  std::cout << main_det << "\n";
  Matrix<T, N, N> inversed_matrix = {};
  if (N == 1) {
    inversed_matrix(0, 0) = 1 / matrix(0, 0);
  } else {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        inversed_matrix(i, j) = pow(-1, i + j) * Determinant(Reduction(matrix, j, i));
      }
    }
  }
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix(i, j) = inversed_matrix(i, j);
    }
  }
}

#endif  //  MATRIX__CLASS__HEADER_H