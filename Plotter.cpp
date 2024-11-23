#include "Plotter.h"

Plotter::Plotter(const std::string &name) : plotterName(name) {
  labels = std::vector<std::string>();
  functions = std::vector<std::shared_ptr<IFunction>>();
}

void Plotter::addFunction(const std::shared_ptr<IFunction> &func,
                          const std::string &label) {
  functions.push_back(func);
  labels.push_back(label);
}

void Plotter::clearFunctions() {
  functions.clear();
  labels.clear();
}

void Plotter::generateData(double start, double end) {
  std::ofstream dataFile(plotterName + ".dat");
  if (!dataFile.is_open()) {
    throw std::runtime_error("Error creating data file!");
  }

  double step = (end - start) / (nodes - 1);

  for (int i = 0; i < nodes; ++i) {
    double x = start + i * step;
    dataFile << x;

    for (const auto &func : functions) {
      dataFile << " " << func->evaluate(x);
    }
    dataFile << "\n";
  }

  dataFile.close();
}

void Plotter::plot() {
  std::string filename = plotterName + ".gp";
  std::ofstream gnuplotScript(filename);
  if (!gnuplotScript.is_open()) {
    throw std::runtime_error("Error creating gnuplot script!");
  }

  gnuplotScript << "set title '" + plotterName + "\n ";
  gnuplotScript << "set grid\n";
  gnuplotScript << "set xlabel 'x'\n";
  gnuplotScript << "set ylabel 'y'\n";
  gnuplotScript << "set format y '%.3e'\n";
  gnuplotScript << "plot";

  for (size_t i = 0; i < functions.size(); ++i) {
    gnuplotScript << " '" + plotterName + ".dat' using 1:" << (i + 2)
                  << " with lines title '" << labels[i] << "'";
    if (i != functions.size() - 1) {
      gnuplotScript << ", \\\n";
    }
  }

  gnuplotScript << "\n";
  gnuplotScript.close();

  // Вызов gnuplot для построения графика
  std::string command = "gnuplot -p " + plotterName + ".gp";
  system(command.c_str());
}

void Plotter::plotDeltaPoints(const std::vector<RecordPoints> &functions,
                              const std::string &name, bool toLogscale) const {

  std::ofstream dataFile(name + ".dat");
  if (!dataFile.is_open()) {
    throw std::runtime_error("Error creating data file!");
  }

  for (size_t i = 0; i < functions[0].getPoints().size(); i++) {
    dataFile << functions[0].getPoints()[i].first << " ";
    for (const auto &function : functions) {
      dataFile << std::setprecision(std::numeric_limits<double>::max_digits10)
               << function.getPoints()[i].second << " ";
    }
    dataFile << "\n";
  }
  dataFile.close();

  std::ofstream gnuplotScript(plotterName + "_point.gp");
  if (!gnuplotScript.is_open()) {
    throw std::runtime_error("Error creating gnuplot script!");
  }

  gnuplotScript << "set title '" + name + "'\n";
  gnuplotScript << "set grid\n";
  if (toLogscale) {
    gnuplotScript << "set logscale y\n";
  }

  gnuplotScript << "set xlabel 'n'\n";
  gnuplotScript << "set ylabel 'delta'\n";
  gnuplotScript << "set format y '%.3e'\n";
  gnuplotScript << "set pointsize 1\n";
  gnuplotScript << "plot";

  for (size_t i = 0; i < functions.size(); ++i) {
    gnuplotScript << " '" + name + ".dat' using 1:" << (i + 2)
                  << " with points title '" << functions[i].getName() << "'";
    if (i != functions.size() - 1) {
      gnuplotScript << ", \\\n";
    }
  }
  gnuplotScript << "\n";

  gnuplotScript.close();

  std::string command = "gnuplot -p " + plotterName + "_point.gp";
  system(command.c_str());
}

void Plotter::plotComparison(const RecordPoints &pointsOver,
                             const RecordPoints &pointsUnder,
                             const IFunction &func, double start, double end,
                             bool toLogscale) const {
  std::ofstream dataFileOver(plotterName + "_comparison_over.dat");
  if (!dataFileOver.is_open()) {
    throw std::runtime_error("Error creating data file!");
  }
  for (size_t i = 0; i < pointsOver.getPoints().size(); i++) {
    dataFileOver << pointsOver.getPoints()[i].first << " ";

    dataFileOver << std::setprecision(std::numeric_limits<double>::max_digits10)
                 << pointsOver.getPoints()[i].second << " ";

    dataFileOver << "\n";
  }
  dataFileOver.close();

  std::ofstream dataFileUnder(plotterName + "_comparison_under.dat");
  if (!dataFileUnder.is_open()) {
    throw std::runtime_error("Error creating data file!");
  }
  for (size_t i = 0; i < pointsUnder.getPoints().size(); i++) {
    dataFileUnder << pointsUnder.getPoints()[i].first << " ";

    dataFileUnder << std::setprecision(
                         std::numeric_limits<double>::max_digits10)
                  << pointsUnder.getPoints()[i].second << " ";

    dataFileUnder << "\n";
  }
  dataFileUnder.close();

  std::ofstream gnuplotScript(plotterName + "_comparison.gp");
  if (!gnuplotScript.is_open()) {
    throw std::runtime_error("Error creating gnuplot script!");
  }

  gnuplotScript << "set title 'MonteCarlo'\n";
  gnuplotScript << "set grid\n";
  if (toLogscale) {
    gnuplotScript << "set logscale y\n";
  }

  gnuplotScript << "set xlabel 'n'\n";
  gnuplotScript << "set ylabel 'delta'\n";
  gnuplotScript << "set format y '%.3e'\n";
  gnuplotScript << "set pointsize 1\n";
  gnuplotScript << "plot";

  gnuplotScript << " '" << plotterName
                << "_comparison_over.dat' using 1 : 2 with points title '"
                << pointsOver.getName() << "',\ ";
  gnuplotScript << " '" << plotterName
                << "_comparison_under.dat' using 1 : 2 with points title '"
                << pointsUnder.getName() << "',\ ";

  std::ofstream dataFile2(plotterName + "_comparison_function.dat");
  if (!dataFile2.is_open()) {
    throw std::runtime_error("Error creating data file!");
  }

  double step = (end - start) / ((nodes)-1);

  for (int i = 0; i < nodes; ++i) {
    double x = start + i * step;
    dataFile2 << x << " " << func.evaluate(x);

    dataFile2 << "\n";
  }

  gnuplotScript
      << " '" << plotterName
      << "_comparison_function.dat' using 1:2 with lines title 'function'";

  gnuplotScript.close();

  std::string command = "gnuplot -p " + plotterName + "_comparison.gp";
  system(command.c_str());
}


std::string Plotter::getLabel(size_t i) { return labels[i]; }
