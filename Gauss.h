#pragma once
#include "RecordPoints.h"
inline RecordVector Gauss(RecordMatrix &matrix) {
  size_t dim = matrix.data.size();
  RecordVector x(dim); // Вектор решения, инициализируем нулями

  // Прямой ход
  for (size_t i = 0; i < dim; ++i) {
    // Выбор главного элемента
    double max = 0;
    size_t m_index = i;

    for (size_t m = i; m < dim; ++m) {
      if (std::abs(matrix.getValue(m, i)) > max) {
        max = std::abs(matrix.getValue(m, i));
        m_index = m;
      }
    }

    if (max == 0) {
      std::cout << "There is no single solution" << std::endl;
      return RecordVector(dim, -1); // Нет решения
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

  // Обратный ход
  x.setValue(dim - 1,
             matrix.getValue(dim - 1, dim) / matrix.getValue(dim - 1, dim - 1));

  for (int i = dim - 2; i >= 0; --i) {
    double sum = matrix.getValue(i, dim);
    for (size_t j = i + 1; j < dim; ++j) {
      sum -= matrix.getValue(i, j) * x.getValue(j);
    }
    x.setValue(i, sum / matrix.getValue(i, i));
  }

  return x; // Возвращаем решение как объект RecordVector
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