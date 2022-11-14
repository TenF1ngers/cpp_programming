#include <iostream>
#include <cmath>
#include "../vector.h"

geometry::Vector::Vector() : x(0), y(0) {
}

geometry::Vector::Vector(const int64_t& beg_x, const int64_t& beg_y, const int64_t& end_x, const int64_t& end_y)
    : x(end_x - beg_x), y(end_y - beg_y) {
}

geometry::Vector::Vector(const geometry::Point& begin, const geometry::Point& end)
    : x(end.x - begin.x), y(end.y - begin.y) {
}

geometry::Vector geometry::Vector::operator+() {
  return *this;
}

geometry::Vector geometry::Vector::operator-() {
  x = -x;
  y = -y;
  return *this;
}

geometry::Vector geometry::Vector::operator+(const geometry::Vector& second) const {
  geometry::Vector temp;
  temp.x = this->x + second.x;
  temp.y = this->y + second.y;
  return temp;
}

geometry::Vector geometry::Vector::operator-(const geometry::Vector& second) const {
  geometry::Vector temp;
  temp.x = this->x - second.x;
  temp.y = this->y - second.y;
  return temp;
}

geometry::Vector geometry::Vector::operator*(const int64_t& value) const {
  geometry::Vector temp(0, 0, x, y);
  temp.x *= value;
  temp.y *= value;
  return temp;
}

geometry::Vector geometry::Vector::operator/(const int64_t& value) const {
  geometry::Vector temp(0, 0, x, y);
  temp.x /= value;
  temp.y /= value;
  return temp;
}

geometry::Vector& geometry::Vector::operator+=(const geometry::Vector& second) {
  this->x += second.x;
  this->y += second.y;
  return *this;
}

geometry::Vector& geometry::Vector::operator-=(const geometry::Vector& second) {
  this->x -= second.x;
  this->y -= second.y;
  return *this;
}

geometry::Vector& geometry::Vector::operator*=(const int64_t& value) {
  this->x *= value;
  this->y *= value;
  return *this;
}

geometry::Vector& geometry::Vector::operator/=(const int64_t& value) {
  this->x /= value;
  this->y /= value;
  return *this;
}

bool geometry::Vector::operator==(const geometry::Vector& second) const {
  bool flag = false;
  if ((this->x == second.x) && (this->y == second.y)) {
    flag = true;
  }
  return flag;
}

std::string geometry::Vector::ToString() const {
  std::string message = "Vector(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
  return message;
}

long double LengthOfVector(const geometry::Vector& vector) {
  auto len = static_cast<long double>(sqrt(pow(vector.x, 2) + pow(vector.y, 2)));
  return len;
}

int64_t ScalarProduct(const geometry::Vector& first, const geometry::Vector& second) {
  auto result = first.x * second.x + first.y * second.y;
  return result;
}

int64_t VectorProduct(const geometry::Vector& first, const geometry::Vector& second) {
  auto result = first.x * second.y - first.y * second.x;
  return result;
}

double AreaOfTreangle(const geometry::Vector& first, const geometry::Vector& second) {
  return std::abs(VectorProduct(first, second) / 2);
}

std::istream& operator>>(std::istream& is, geometry::Vector& vector) {
  int64_t beg_x = 0, beg_y = 0, end_x = 0, end_y = 0;
  is >> beg_x >> beg_y >> end_x >> end_y;
  vector.x = end_x - beg_x;
  vector.y = end_y - beg_y;
  return is;
}

std::ostream& operator<<(std::ostream& os, geometry::Vector vector) {
  os << vector.x << " " << vector.y;
  return os;
}
