#pragma once
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>


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
        std::cout << std::fixed << std::setw(10) << std::setprecision(5) << val
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
  double determinant() const {
    size_t dim = data.size();

    RecordMatrix mat(*this);

    for (size_t i = 0; i < dim; ++i) {
      size_t maxRow = i;
      for (size_t k = i + 1; k < dim; ++k) {
        if (std::abs(mat.getValue(k, i)) > std::abs(mat.getValue(maxRow, i))) {
          maxRow = k;
        }
      }

      if (i != maxRow) {
        for (size_t j = 0; j < dim; ++j) {
          double temp = mat.getValue(i, j);
          mat.setValue(i, j, mat.getValue(maxRow, j));
          mat.setValue(maxRow, j, temp);
        }
      }

      if (mat.getValue(i, i) == 0) {
        return 0.0;
      }

      for (size_t j = i + 1; j < dim; ++j) {
        double coeff = -mat.getValue(j, i) / mat.getValue(i, i);
        for (size_t k = i; k < dim; ++k) {
          mat.setValue(j, k, mat.getValue(j, k) + coeff * mat.getValue(i, k));
        }
      }
    }

    double det = 1.0;
    for (size_t i = 0; i < dim; ++i) {
      det *= mat.getValue(i, i);
    }

    return det;
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
      std::cout << std::fixed << std::setw(10) << std::setprecision(5) << val
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