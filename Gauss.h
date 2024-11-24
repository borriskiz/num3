#pragma once
#include "RecordPoints.h"
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
class RationalFunctionGauss : public IFunction {
public:
  RationalFunctionGauss(const std::string &newName) { name = newName; }
  void addGaussAnswer(const RecordVector &answer) { vector = answer; }
  double evaluate(double x) const override {
    return (vector.getValue(0) + vector.getValue(1) * x +
            vector.getValue(2) * pow(x, 2)) /
           (1 + vector.getValue(3) * x + vector.getValue(4) * pow(x, 2) +
            vector.getValue(5) * pow(x, 3));
  }

private:
  RecordVector vector;
};