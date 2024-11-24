#pragma once
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

inline int randomInt(int min, int max) {
  int random_num = rand() % (max - min + 1) + min;
  return random_num;
}

inline double randomDouble(double min, double max) {
  double f = (double)rand() / RAND_MAX;
  return min + (double)rand() / RAND_MAX * (max - min);
}

class RecordPoints {
public:
  RecordPoints(const std::string &name) : name(name) {}
  RecordPoints(const std::string &name,
               const std::vector<std::pair<double, double>> &points)
      : name(name), points(points) {}

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

  RecordMatrix(size_t rows, size_t cols, double initialValue = 0.0)
      : data(rows, std::vector<double>(cols, initialValue)) {}

  void printMatrix() const {
    for (const auto &row : data) {
      for (double val : row) {
        std::cout << std::fixed << std::setw(3) << std::setprecision(5) << val
                  << ' ';
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }

  double getValue(size_t row, size_t col) const {
    if (row < 0 || row >= data.size() || col < 0 || col >= data[0].size()) {
      throw std::out_of_range("Index out of matrix");
    }
    return data[row][col];
  }

  void setValue(size_t row, size_t col, double value) {
    if (row < 0 || row >= data.size() || col < 0 || col >= data[0].size()) {
      throw std::out_of_range("Index out of matrix");
    }
    data[row][col] = value;
  }

  void clear() { data.clear(); }
};

class RecordVector {
public:
  std::vector<double> data;
  RecordVector() = default;
  RecordVector(size_t size, double initialValue = 0.0)
      : data(size, initialValue) {}

  void printVector() const {
    for (double val : data) {
      std::cout << std::fixed << std::setw(6) << std::setprecision(5) << val
                << ' ';
    }
    std::cout << "\n";
  }

  double getValue(size_t index) const {
    if (index < 0 || index >= data.size()) {
      throw std::out_of_range("Index out of vector");
    }
    return data[index];
  }

  void setValue(size_t index, double value) {
    if (index < 0 || index >= data.size()) {
      throw std::out_of_range("Index out of vector");
    }
    data[index] = value;
  }

  size_t getSize() const { return data.size(); }

  void addValue(double value) { data.push_back(value); }

  void clear() { data.clear(); }
};