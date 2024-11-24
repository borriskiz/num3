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

void Plotter::plotDeltaPoints(const std::vector<RecordPoints> &points,
                              const std::string &name, bool toLogscale) const {

  std::ofstream dataFile(name + ".dat");
  if (!dataFile.is_open()) {
    throw std::runtime_error("Error creating data file!");
  }

  for (size_t i = 0; i < points[0].getSize(); i++) {
    dataFile << points[0].getPoint(i).first << " ";
    for (const auto &function : points) {
      dataFile << std::setprecision(std::numeric_limits<double>::max_digits10)
               << function.getPoint(i).second << " ";
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

  for (size_t i = 0; i < points.size(); ++i) {
    gnuplotScript << " '" + name + ".dat' using 1:" << (i + 2)
                  << " with points title '" << points[i].getName() << "'";
    if (i != points.size() - 1) {
      gnuplotScript << ", \\\n";
    }
  }
  gnuplotScript << "\n";

  gnuplotScript.close();

  std::string command = "gnuplot -p " + plotterName + "_point.gp";
  system(command.c_str());
}

void Plotter::plotPointsAndFunction(const RecordPoints &points,
                                    const IFunction &func, double start,
                                    double end, bool toLogscale) const {
  std::ofstream dataFileOver(plotterName + "_points_" + points.getName() +
                             ".dat");
  if (!dataFileOver.is_open()) {
    throw std::runtime_error("Error creating data file!");
  }
  for (size_t i = 0; i < points.getSize(); i++) {
    dataFileOver << points.getPoint(i).first << " ";

    dataFileOver << std::setprecision(std::numeric_limits<double>::max_digits10)
                 << points.getPoint(i).second << " ";

    dataFileOver << "\n";
  }
  dataFileOver.close();

  std::ofstream gnuplotScript(plotterName + ".gp");
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
                << points.getName() << "',\ ";


  std::ofstream dataFile2(plotterName + "_function_" + func.getName() + ".dat");
  if (!dataFile2.is_open()) {
    throw std::runtime_error("Error creating data file!");
  }

  double step = (end - start) / ((nodes)-1);

  for (int i = 0; i < nodes; ++i) {
    double x = start + i * step;
    dataFile2 << x << " " << func.evaluate(x);

    dataFile2 << "\n";
  }

  gnuplotScript << " '" << plotterName << "_function_" << func.getName()
                << ".dat' using 1:2 with lines title 'function'";

  gnuplotScript.close();

  std::string command = "gnuplot -p " + plotterName + ".gp";
  system(command.c_str());
}

std::string Plotter::getLabel(size_t i) { return labels[i]; }
