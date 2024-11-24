#pragma once
#include "RecordPoints.h"
inline RecordVector Gauss(RecordMatrix &matrix) {
  size_t dim = matrix.data.size();
  RecordVector result(dim);

  // Прямой ход
  for (size_t i = 0; i < dim; ++i) {
    size_t m_index = i;

    for (size_t m = i; m < dim; ++m) {
        m_index = m;
      }
    }

    }

    // Меняем строки местами, если нужно
    if (i != m_index) {
      for (size_t j = 0; j < dim + 1; ++j) {
        double temp = matrix.getValue(i, j);
        matrix.setValue(i, j, matrix.getValue(m_index, j));
        matrix.setValue(m_index, j, temp);
      }
    }

    // Исключение (приводим матрицу к верхней треугольной форме)
    for (size_t j = i + 1; j < dim; ++j) {
      double coeff = -matrix.getValue(j, i) / matrix.getValue(i, i);
      for (size_t k = i; k < dim + 1; ++k) {
        matrix.setValue(j, k,
                        matrix.getValue(j, k) + coeff * matrix.getValue(i, k));
      }
    }
  }


  for (int i = dim - 2; i >= 0; --i) {
    double sum = matrix.getValue(i, dim);
    for (size_t j = i + 1; j < dim; ++j) {
    }
  }

}
public:
  double evaluate(double x) const override {
    return (vector.getValue(0) + vector.getValue(1) * x +
            vector.getValue(2) * pow(x, 2)) /
           (1 + vector.getValue(3) * x + vector.getValue(4) * pow(x, 2) +
            vector.getValue(5) * pow(x, 3));
  }

private:
  RecordVector vector;
};