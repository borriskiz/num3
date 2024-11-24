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
    gaussAnswer.printVector();

    RationalFunctionGauss gauss("Gausian");
    gauss.addGaussAnswer(gaussAnswer);

    plotter.plotPointsAndFunction(
        initialRecord, std::make_shared<RationalFunctionGauss>(gauss), -2, 2,
        false);

    //plotter.plotDeltaPoints({initialRecord}, "1", false);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return false;
  }
  return true;
}

bool Tester::second() {
  try {

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