#include "Tester.h"

const RecordPoints Tester::initialRecord =
    RecordPoints("Initial Points", {
                                       {-2, 0.28205},
                                       {-1.20, 1.0452},
                                       {-0.400, 2.5052},
                                       {0.400, 1.1723},
                                       {1.20, -0.20842},
                                       {2., -0.28661},
                                   });

bool Tester::first() {
  try {
    Plotter plotter("1");

    size_t dimension = initialRecord.getSize();

    RecordMatrix matrix(dimension, dimension + 1, -1);

    for (int i = 0; i < dimension; ++i) {
      int p = 2;
      int q = 3;
      double x_i = initialRecord.getPoint(i).first;
      double y_i = initialRecord.getPoint(i).second;
      for (size_t j = 0; j < dimension; ++j) {
        if (j <= p) {
          matrix.setValue(i, j, std::pow(x_i, j));
        } else {
          matrix.setValue(i, j, -y_i * std::pow(x_i, j - p));
        }
      }
      matrix.setValue(i, dimension, y_i);
    }

    matrix.printMatrix();

    auto gaussAnswer = Gauss(matrix);
    std::cout << "Gauss answer:\n";
    gaussAnswer.printVector();

    RationalFunction gauss("Gausian");

    gauss.addAnswer(gaussAnswer);

    plotter.plotPointsAndFunction(
        initialRecord, std::make_shared<RationalFunction>(gauss), -2, 2, false);
    std::cout << matrix.determinant() << "\n";

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return false;
  }
  return true;
}

bool Tester::second() {
  try {
    Plotter plotter("2");

    size_t dimension = initialRecord.getSize();

    RecordMatrix matrix(dimension, dimension + 1, -1);

    for (int i = 0; i < dimension; ++i) {
      int p = 2;
      int q = 3;
      double x_i = initialRecord.getPoint(i).first;
      double y_i = initialRecord.getPoint(i).second;
      for (size_t j = 0; j < dimension; ++j) {
        if (j <= p) {
          matrix.setValue(i, j, std::pow(x_i, j));
        } else {
          matrix.setValue(i, j, -y_i * std::pow(x_i, j - p));
        }
      }
      matrix.setValue(i, dimension, y_i);
    }

    matrix.printMatrix();

    auto LuAnswer = LUDecomposition(matrix);
    std::cout << "LU answer:\n";
    LuAnswer.printVector();

    RationalFunction LUrian("LU");
    LUrian.addAnswer(LuAnswer);

    plotter.plotPointsAndFunction(initialRecord,
                                  std::make_shared<RationalFunction>(LUrian),
                                  -2, 2, false);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return false;
  }
  return true;
}

bool Tester::third() {
  try {

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return false;
  }
  return true;
}

bool Tester::fourth() {
  try {
    Plotter plotter("4");

    size_t dimension = 7;

    RecordMatrix matrix(dimension, dimension + 1, 0);

    matrix.data.resize(dimension);
    for (int i = 0; i < dimension; ++i) {
      matrix.data[i].resize(dimension + 1);

      double sum = 0;
      for (int j = 0; j < dimension; ++j) {
        if (std::abs(i - j) <= 2 && i != j) {
          double value = RandomDouble(5, 10);
          matrix.setValue(i, j, value);
          sum += std::abs(value);
        }
      }

      matrix.setValue(i, i, 4 * std::pow(-1, RandomInt(0, 1)) * sum);

      matrix.setValue(i, dimension, RandomDouble(-1, 1));
    }

    matrix.printMatrix();
    auto fiveDiagonalAnswer = FiveDiagonalMethod(matrix);
    std::cout << "fiveDiagonal answer:\n";
    fiveDiagonalAnswer.printVector();
    checkAnswer(matrix, fiveDiagonalAnswer);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return false;
  }
  return true;
}

bool Tester::makeTest(size_t number) {
  switch (number) {
  case 1:
    return first();
  case 2:
    return second();
  case 3:
    return third();
  case 4:
    return fourth();
  default:
    return false;
  }
}