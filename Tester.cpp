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
    std::cout << "\n";
    RationalFunction gauss("Gausian");

    gauss.addAnswer(gaussAnswer);

    plotter.plotPointsAndFunction(
        initialRecord, std::make_shared<RationalFunction>(gauss), -2, 2, false);

    checkAnswer(matrix, gaussAnswer);
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
    std::cout << "\n";

    RationalFunction LUrian("LU");
    LUrian.addAnswer(LuAnswer);

    plotter.plotPointsAndFunction(initialRecord,
                                  std::make_shared<RationalFunction>(LUrian),
                                  -2, 2, false);
    checkAnswer(matrix, LuAnswer);
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

    size_t dimension = 10;

    RecordMatrix matrix(dimension, dimension, 0);

    matrix.data.resize(dimension);

    for (int i = 0; i < dimension; ++i) {
      matrix.data[i].resize(dimension + 1);

      for (int j = 0; j < dimension; ++j) {
        if (std::abs(i - j) == 0) {
          double value = RandomDouble(50, 90);
          matrix.setValue(i, j, value);
        } else if (std::abs(i - j) == 1) {
          double value = RandomDouble(20, 50);
          matrix.setValue(i, j, value);
        } else if (std::abs(i - j) == 2) {

          double value = RandomDouble(5, 10);
          matrix.setValue(i, j, value);
        } else {
          matrix.setValue(i, j, 0);
        }
      }
      matrix.setValue(i, dimension, RandomDouble(-1, 1));
    }

    matrix.printMatrix();
    auto fiveDiagonalAnswer = FiveDiagonalMethod(matrix);

    std::cout << "fiveDiagonal answer:\n";
    fiveDiagonalAnswer.printVector();
    std::cout << "\n";

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