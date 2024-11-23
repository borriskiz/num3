#pragma once
#include <map>
#include <string>
#include <vector>
class RecordPoints {
public:
  RecordPoints(const std::string &name) : name(name) {}

  void addPoint(double x, double y) { points.emplace_back(x, y); }
  void clearPoints() { points.clear(); }

  const std::vector<std::pair<double, double>> &getPoints() const {
    return points;
  }

  const std::string &getName() const { return name; }

private:
  std::vector<std::pair<double, double>> points;
  std::string name;
};
