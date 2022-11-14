#include <cmath>
#include <iostream>

#include "../interface.h"
#include "../vector.h"
#include "../segment.h"
#include "../circle.h"

geometry::Circle::~Circle() = default;

geometry::Circle::Circle(const geometry::Point& point, const int64_t& value) : centre(point), r(value) {
}

geometry::Circle::Circle(const geometry::Circle& other) : centre(other.centre), r(other.r) {
}

geometry::Circle& geometry::Circle::Move(const Vector& vector) {
  this->centre.x += vector.x;
  this->centre.y += vector.y;
  return *this;
}

bool geometry::Circle::ContainsPoint(const Point& temp_point) const {
  bool flag = false;
  if (pow(temp_point.x - this->centre.x, 2) + pow(temp_point.y - this->centre.y, 2) <= pow(this->r, 2)) {
    flag = true;
  }
  return flag;
}

bool geometry::Circle::CrossesSegment(const Segment& segment) const {
  long double distance = 0.;
  bool flag = false;
  if ((pow(segment.first.x - this->centre.x, 2) + pow(segment.first.y - this->centre.y, 2) == pow(this->r, 2)) ||
      (pow(segment.second.x - this->centre.x, 2) + pow(segment.second.y - this->centre.y, 2) == pow(this->r, 2))) {
    flag = true;
  } else if ((pow(segment.first.x - this->centre.x, 2) + pow(segment.first.y - this->centre.y, 2) > pow(this->r, 2)) &&
             ((pow(segment.second.x - this->centre.x, 2) + pow(segment.second.y - this->centre.y, 2) >
               pow(this->r, 2)))) {
    if (ScalarProduct(Vector(segment.first, segment.second), Vector(segment.first, this->centre)) < 0) {
      distance = LengthOfVector(Vector(segment.first, this->centre));
    } else if (ScalarProduct(Vector(segment.second, segment.first), Vector(segment.second, this->centre)) < 0) {
      distance = LengthOfVector(Vector(segment.second, this->centre));
    } else {
      distance = static_cast<long double>(std::abs(VectorProduct(Vector(segment.first, segment.second), Vector(segment.first, this->centre)))) /
                 LengthOfVector(Vector(segment.first, segment.second));
    }
    if (distance <= static_cast<long double>(this->r)) {
      flag = true;
    }
  } else if ((pow(segment.first.x - this->centre.x, 2) + pow(segment.first.y - this->centre.y, 2) > pow(this->r, 2)) ||
             (pow(segment.second.x - this->centre.x, 2) + pow(segment.second.y - this->centre.y, 2) >
              pow(this->r, 2))) {
    flag = true;
  }
  return flag;
}

geometry::Circle* geometry::Circle::Clone() const {
  auto new_circle = new Circle(this->centre, this->r);
  return new_circle;
}

std::string geometry::Circle::ToString() const {
  std::string message = "Circle(" + this->centre.ToString() + ", " + std::to_string(this->r) + ")";
  return message;
}

geometry::Circle& geometry::Circle::operator=(const geometry::Circle& other) {
  this->centre = other.centre;
  this->r = other.r;
  return *this;
}
