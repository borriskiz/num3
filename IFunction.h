#pragma once
#include "Constants.h"
#include <cmath>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

class IFunction {
protected:
  std::vector<std::pair<double, double>> points;
  std::string name;

public:
  virtual double evaluate(double x) const = 0;
  // double supDelta(double start, double end, const IFunction &func) const;
  int degree() const { return static_cast<int>(points.size()) - 1; }
  const std::string &getName() const { return name; }
};
