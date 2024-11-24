#pragma once
#include "Constants.h"
#include "IFunction.h"
#include "RecordPoints.h"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

class Plotter {
private:
  std::string plotterName;
  std::vector<std::shared_ptr<IFunction>> functions;
  std::vector<std::string> labels;

public:
  Plotter(const std::string &name);

  void plotDeltaPoints(const std::vector<RecordPoints> &functions,
                       const std::string &name, bool toLogscale) const;
  void plotPointsAndFunction(const RecordPoints &points,
                             std::shared_ptr<IFunction> func, double start,
                             double end, bool toLogscale) const;

  std::string getLabel(size_t i);
};
