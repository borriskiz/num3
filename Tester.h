#include "Constants.h"
#include "Gauss.h"
#include "Plotter.h"
#include "RecordPoints.h"
#include <iomanip>
#include <iostream>
#include <sstream>

#pragma once
class Tester {
private:
  static bool first();
  static bool second();
  static bool third();
  static bool fourth();
  static const RecordPoints initialRecord;

public:
  static bool makeTest(size_t number);
};
