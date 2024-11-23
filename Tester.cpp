#include "Tester.h"

bool Tester::first() {
  try {
    
  } catch (const std::exception &) {
    return false;
  }
  return true;
}

bool Tester::second() {
  try {
    
  } catch (const std::exception &) {
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
    
  } catch (const std::exception &) {
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
