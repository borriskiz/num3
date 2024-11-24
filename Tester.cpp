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
    plotter.plotDeltaPoints({initialRecord}, "test",false);
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