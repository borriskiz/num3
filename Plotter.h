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
  void addFunction(const std::shared_ptr<IFunction> &func,
                   const std::string &label);
  void clearFunctions();
  void generateData(double start, double end);
  void plot();
  void plotDeltaPoints(const std::vector<RecordPoints> &functions,
                       const std::string &name, bool toLogscale) const;
  void plotComparison(const RecordPoints &pointsOver,
                      const RecordPoints &pointsUnder, const IFunction &func,
                      double start, double end, bool toLogscale) const;

  std::string getLabel(size_t i);
};
