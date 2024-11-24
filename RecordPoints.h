#pragma once
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int randomInt(int min, int max) {
  int random_num = rand() % (max - min + 1) + min;
  return random_num;
}

double randomDouble(double min, double max) {
  double f = (double)rand() / RAND_MAX;
  return min + (double)rand() / RAND_MAX * (max - min);
}

class RecordPoints {
public:
  RecordPoints(const std::string &name) : name(name) {}

  void addPoint(double x, double y) { points.emplace_back(x, y); }
  void clearPoints() { points.clear(); }

  const std::vector<std::pair<double, double>> &getVectorPoints() const {
    return points;
  }
  const size_t getSize() const { return points.size(); }
  const std::pair<double, double> &getPoint(size_t index) const {
    return points[index];
  }
  const std::string &getName() const { return name; }

private:
  std::vector<std::pair<double, double>> points;
  std::string name;
};
class RecordMatrix {
public:
  std::vector<std::vector<double>> data;

  RecordMatrix(int rows, int cols, double initialValue = 0.0)
      : data(rows, std::vector<double>(cols, initialValue)) {}

  void print() const {
    for (const auto &row : data) {
      for (double val : row) {
        std::cout << std::fixed << std::setprecision(5) << val << "\t";
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }

  double get(int row, int col) const {
    if (row < 0 || row >= data.size() || col < 0 || col >= data[0].size()) {
      throw std::out_of_range("Индекс за пределами матрицы");
    }
    return data[row][col];
  }

  void set(int row, int col, double value) {
    if (row < 0 || row >= data.size() || col < 0 || col >= data[0].size()) {
      throw std::out_of_range("Индекс за пределами матрицы");
    }
    data[row][col] = value;
  }
};