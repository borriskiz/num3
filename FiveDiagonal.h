#pragma once
#include "RecordPoints.h"

inline double RandomDouble(double min, double max) {
  return min + (max - min) * (rand() / static_cast<double>(RAND_MAX));
}

inline int RandomInt(int min, int max) {
  return min + rand() % (max - min + 1);
}
inline RecordVector FiveDiagonalMethod(RecordMatrix &matrix) {
  size_t dimension = matrix.data.size();
  if (!matrix.determinant()) {
    return RecordVector(dimension, -1);
  }

  RecordVector alpha(dimension + 3), beta(dimension + 3), gamma(dimension + 3);

  alpha.setValue(1, -matrix.getValue(0, 1) / matrix.getValue(0, 0));
  beta.setValue(1, matrix.getValue(0, 2) / matrix.getValue(0, 0));
  gamma.setValue(1, matrix.getValue(0, dimension) / matrix.getValue(0, 0));

  double delta1 =
      matrix.getValue(1, 1) - (-matrix.getValue(1, 0) * alpha.getValue(1));
  alpha.setValue(2, (-matrix.getValue(1, 2) -
                     beta.getValue(1) * (-matrix.getValue(1, 0))) /
                        delta1);
  gamma.setValue(2, (matrix.getValue(1, dimension) +
                     (-matrix.getValue(1, 0) * gamma.getValue(1))) /
                        delta1);
  beta.setValue(2, matrix.getValue(1, 3) / delta1);

  for (size_t i = 2; i <= dimension - 1; ++i) {
    double delta =
        matrix.getValue(i, i) -
        (i < 2 ? 0 : matrix.getValue(i, i - 2)) * beta.getValue(i - 1) +
        alpha.getValue(i) *
            ((i < 2 ? 0 : matrix.getValue(i, i - 2)) * alpha.getValue(i - 1) -
             (i < 1 ? 0 : -matrix.getValue(i, i - 1)));

    if (i <= dimension - 2) {
      alpha.setValue(
          i + 1,
          ((i > dimension - 2 ? 0 : -matrix.getValue(i, i + 1)) +
           beta.getValue(i) * ((i < 2 ? 0 : matrix.getValue(i, i - 2)) *
                                   alpha.getValue(i - 1) -
                               (i < 1 ? 0 : -matrix.getValue(i, i - 1)))) /
              delta);
    }

    if (i <= dimension - 3) {
      beta.setValue(i + 1, (i > dimension - 3 ? 0 : matrix.getValue(i, i + 2)) /
                               delta);
    }

    gamma.setValue(
        i + 1,
        (matrix.getValue(i, dimension) -
         (i < 2 ? 0 : matrix.getValue(i, i - 2)) * gamma.getValue(i - 1) -
         gamma.getValue(i) *
             ((i < 2 ? 0 : matrix.getValue(i, i - 2)) * alpha.getValue(i - 1) -
              (i < 1 ? 0 : -matrix.getValue(i, i - 1)))) /
            delta);
  }

  RecordVector answer(dimension + 3);
  answer.setValue(dimension - 1, gamma.getValue(dimension));
  answer.setValue(dimension - 2, alpha.getValue(dimension - 1) *
                                         answer.getValue(dimension - 1) +
                                     gamma.getValue(dimension - 1));

  for (int i = static_cast<int>(dimension) - 3; i >= 0; --i) {
    answer.setValue(i, alpha.getValue(static_cast<size_t>(i + 1)) *
                               answer.getValue(static_cast<size_t>(i + 1)) -
                           beta.getValue(static_cast<size_t>(i + 1)) *
                               answer.getValue(static_cast<size_t>(i + 2)) +
                           gamma.getValue(static_cast<size_t>(i + 1)));
  }

  answer.data.pop_back();
  answer.data.pop_back();
  answer.data.pop_back();

  return answer;
}

inline void checkAnswer(RecordMatrix &matrix, const RecordVector &answer) {
  size_t dimension = matrix.data.size();
  for (size_t i = 0; i < dimension; ++i) {
    double sum = 0;
    for (size_t j = 0; j < dimension; ++j) {
      sum += matrix.getValue(i, j) * answer.getValue(j);
    }
    std::cout << "row number = " << i << " direct sum: " << std::fixed
              << std::setw(10) << std::setprecision(5) << sum
              << " b: " << std::fixed << std::setw(10) << std::setprecision(5)
              << matrix.getValue(i, dimension) << std::endl;
  }
}