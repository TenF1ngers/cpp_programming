#include <string>

#include "../vector.h"
#include "../segment.h"

geometry::Point::~Point() = default;

geometry::Point::Point() : x(0), y(0) {
}

geometry::Point::Point(int64_t first, int64_t second) : x(first), y(second) {
}

geometry::Point::Point(const geometry::Point& other) : x(other.x), y(other.y) {
}

geometry::Point& geometry::Point::Move(const Vector& vector) {
  this->x += vector.x;
  this->y += vector.y;
  return *this;
}

bool geometry::Point::ContainsPoint(const geometry::Point& point) const {
  bool flag = false;
  if ((this->x == point.x) && (this->y == point.y)) {
    flag = true;
  }
  return flag;
}

bool geometry::Point::CrossesSegment(const Segment& segment) const {
  bool flag = false;
  if (segment.first == segment.second) {
    if (segment.first == *this) {
      flag = true;
    }
  } else {
    Vector guide_one(segment.first.x, segment.first.y, segment.second.x, segment.second.y);
    Vector guide_two(segment.second.x, segment.second.y, segment.first.x, segment.first.y);
    Vector temp_one(segment.first.x, segment.first.y, this->x, this->y);
    Vector temp_two(segment.second.x, segment.second.y, this->x, this->y);
    if ((VectorProduct(guide_one, temp_one) == 0) && (ScalarProduct(guide_one, temp_one) >= 0) &&
        (ScalarProduct(guide_two, temp_two) >= 0)) {
      flag = true;
    }
  }
  return flag;
}

geometry::Point* geometry::Point::Clone() const {
  auto* new_point = new Point(this->x, this->y);
  return new_point;
}

std::string geometry::Point::ToString() const {
  auto x_str = std::to_string(this->x);
  auto y_str = std::to_string(this->y);
  auto message = "Point(" + x_str + ", " + y_str + ")";
  return message;
}

geometry::Vector geometry::Point::operator-(const geometry::Point& point) const {
  Vector vector(point, *this);
  return vector;
}

geometry::Point operator+(const geometry::Point& point, const geometry::Vector& vector) {
  return geometry::Point(point.x + vector.x, point.y + vector.y);
}

bool operator==(const geometry::Point& first, const geometry::Point& second) {
  bool flag = false;
  if ((first.x == second.x) && (first.y == second.y)) {
    flag = true;
  }
  return flag;
}

geometry::Point& geometry::Point::operator=(const Point& other) {
  this->x = other.x;
  this->y = other.y;
  return *this;
}

bool operator!=(const geometry::Point& first, const geometry::Point& second) {
  bool flag = false;
  if ((first.x != second.x) || (first.y != second.y)) {
    flag = true;
  }
  return flag;
}

double geometry::Point::Length(const geometry::Segment& other) {
  double segment_len = 0.;
  if (ScalarProduct(geometry::Vector(other.first, other.second), geometry::Vector(other.first, *this)) <= 0.) {
    segment_len = LengthOfVector(geometry::Vector(other.first, *this));
  } else if (ScalarProduct(geometry::Vector(other.second, other.first), geometry::Vector(other.second, *this)) <= 0.) {
    segment_len = LengthOfVector(geometry::Vector(other.second, *this));
  } else {
    segment_len =
        std::abs(VectorProduct(geometry::Vector(other.first, other.second), geometry::Vector(other.first, *this))) /
        LengthOfVector(geometry::Vector(other.first, other.second));
  }
  return segment_len;
}