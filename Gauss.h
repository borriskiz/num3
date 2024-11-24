#pragma once
#include "RecordPoints.h"
#include "IFunction.h"
inline RecordVector Gauss(RecordMatrix &matrix) {
  size_t dim = matrix.data.size();
  RecordVector result(dim);

  for (size_t i = 0; i < dim; ++i) {
    double main = 0;
    size_t m_index = i;

    for (size_t m = i; m < dim; ++m) {
      if (std::abs(matrix.getValue(m, i)) > main) {
        main = std::abs(matrix.getValue(m, i));
        m_index = m;
      }
    }

    if (main == 0) {
      std::cout << "There is no solution" << std::endl;
      return RecordVector(dim, -1);
    }

    if (i != m_index) {
      for (size_t j = 0; j < dim + 1; ++j) {
        double temp = matrix.getValue(i, j);
        matrix.setValue(i, j, matrix.getValue(m_index, j));
        matrix.setValue(m_index, j, temp);
      }
    }

    for (size_t j = i + 1; j < dim; ++j) {
      double coeff = -matrix.getValue(j, i) / matrix.getValue(i, i);
      for (size_t k = i; k < dim + 1; ++k) {
        matrix.setValue(j, k,
                        matrix.getValue(j, k) + coeff * matrix.getValue(i, k));
      }
    }
  }

  result.setValue(dim - 1, matrix.getValue(dim - 1, dim) /
                               matrix.getValue(dim - 1, dim - 1));

  for (int i = dim - 2; i >= 0; --i) {
    double sum = matrix.getValue(i, dim);
    for (size_t j = i + 1; j < dim; ++j) {
      sum -= matrix.getValue(i, j) * result.getValue(j);
    }
    result.setValue(i, sum / matrix.getValue(i, i));
  }

  return result;
}

inline RecordVector LUDecomposition(const RecordMatrix &matrix) {
  size_t dim = matrix.data.size();
  RecordMatrix L(dim, dim);
  RecordMatrix U(dim, dim);

  for (size_t i = 0; i < dim; ++i) {
    L.setValue(i, i, 1);
    for (size_t j = 0; j < dim; ++j) {
      if (i <= j) {
        U.setValue(i, j, matrix.getValue(i, j));
        for (size_t k = 0; k < i; ++k) {
          U.setValue(i, j,
                     U.getValue(i, j) - L.getValue(i, k) * U.getValue(k, j));
        }
      } else {
        L.setValue(i, j, matrix.getValue(i, j));
        for (size_t k = 0; k < j; ++k) {
          L.setValue(i, j,
                     L.getValue(i, j) - L.getValue(i, k) * U.getValue(k, j));
        }
        L.setValue(i, j, L.getValue(i, j) / U.getValue(j, j));
      }
    }
  }

  std::cout << "L matrix:" << std::endl;
  L.printMatrix();
  std::cout << "U matrix:" << std::endl;
  U.printMatrix();

  RecordVector y(dim);
  for (size_t i = 0; i < dim; ++i) {
    y.setValue(i, matrix.getValue(i, dim));
    for (size_t k = 0; k < i; ++k) {
      y.setValue(i, y.getValue(i) - L.getValue(i, k) * y.getValue(k));
    }
  }

  RecordVector result(dim);
  for (int i = dim - 1; i >= 0; --i) {
    result.setValue(i, y.getValue(i));
    for (size_t k = i + 1; k < dim; ++k) {
      result.setValue(i, result.getValue(i) -
                             U.getValue(i, k) * result.getValue(k));
    }
    result.setValue(i, result.getValue(i) / U.getValue(i, i));
  }

  return result;
}

class RationalFunction : public IFunction {
public:
  RationalFunction(const std::string &newName) { name = newName; }
  void addAnswer(const RecordVector &answer) { vector = answer; }
  double evaluate(double x) const override {
    return (vector.getValue(0) + vector.getValue(1) * x +
            vector.getValue(2) * pow(x, 2)) /
           (1 + vector.getValue(3) * x + vector.getValue(4) * pow(x, 2) +
            vector.getValue(5) * pow(x, 3));
  }

private:
  RecordVector vector;
};