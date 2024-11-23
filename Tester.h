#include <iomanip>
#include <sstream>
#include <iostream>
#pragma once
class Tester {
private:
  static bool first();
  static bool second();
  static bool third();
  static bool fourth();

public:
  static bool makeTest(size_t number);
};
