#pragma once

#include "interface.h"
#include "point.h"

class geometry::Vector {
 public:
  int64_t x, y;

  ~Vector() = default;
  Vector();
  Vector(const int64_t& beg_x, const int64_t& beg_y, const int64_t& end_x, const int64_t& end_y);
  Vector(const geometry::Point& begin, const geometry::Point& end);
  Vector(const Vector& other) = default;
  Vector operator+();
  Vector operator-();
  Vector operator+(const Vector& second) const;
  Vector operator-(const Vector& second) const;
  Vector operator*(const int64_t& value) const;
  Vector operator/(const int64_t& value) const;
  Vector& operator+=(const Vector& second);
  Vector& operator-=(const Vector& second);
  Vector& operator*=(const int64_t& value);
  Vector& operator/=(const int64_t& value);
  bool operator==(const Vector& second) const;
  Vector& operator=(const Vector& other) = default;
  std::string ToString() const;
};

long double LengthOfVector(const geometry::Vector& vector);
int64_t ScalarProduct(const geometry::Vector& first, const geometry::Vector& second);
int64_t VectorProduct(const geometry::Vector& first, const geometry::Vector& second);
double AreaOfTreangle(const geometry::Vector& first, const geometry::Vector& second);
std::istream& operator>>(std::istream& is, geometry::Vector& vector);
std::ostream& operator<<(std::ostream& os, geometry::Vector vector);