#include <cmath>
#include <iostream>

#include "../line.h"
#include "../segment.h"

geometry::Line::~Line() = default;

geometry::Line::Line(const geometry::Point& first, const geometry::Point& second)
    : point(first), guide(second - first) {
}

geometry::Line::Line(const geometry::Line& other) {
  this->point = other.point;
  this->guide = other.guide;
}

geometry::Line& geometry::Line::Move(const Vector& vector) {
  this->point.x += vector.x;
  this->point.y += vector.y;
  return *this;
}

bool geometry::Line::ContainsPoint(const Point& temp_point) const {
  Vector temp(this->point, temp_point);
  bool flag = false;
  if (VectorProduct(guide, temp) == 0) {
    flag = true;
  }
  return flag;
}

bool geometry::Line::CrossesSegment(const Segment& segment) const {
  bool flag = false;
  if (Crossing(Segment(this->point, this->point + this->guide), segment)) {
    flag = true;
  }
  return flag;
}

geometry::Line* geometry::Line::Clone() const {
  Line* new_line = new Line(this->point, this->point + guide);
  return new_line;
}

std::string geometry::Line::ToString() const {
  int64_t a = -this->guide.y, b = this->guide.x;
  int64_t c = -(a * this->point.x) - (b * this->point.y);
  std::string message = "Line(" + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + ")";
  return message;
}

long double IntersectionX(const geometry::Line& first, const geometry::Line& second) {
  int64_t a1 = -first.guide.y, b1 = first.guide.x, c1 = -(a1 * first.point.x) - b1 * first.point.y;
  int64_t a2 = -second.guide.y, b2 = second.guide.x, c2 = -(a2 * second.point.x) - b2 * second.point.y;
  long double x = 0., y = 0.;
  if ((a1 == 0) && (b1 != 0)) {
    y = -c1 / b1;
    x = (-b2 * y - c2) / a2;
  } else if ((a1 != 0) && (b1 == 0)) {
    x = -c1 / a1;
    y = (-a2 * x - c2) / b2;
  } else {
    if ((a2 == 0) && (b2 != 0)) {
      y = -c2 / b2;
      x = (-b1 * y - c1) / a1;
    } else if ((a2 != 0) && (b2 == 0)) {
      x = -c2 / a2;
      y = (-a1 * x - c1) / b1;
    } else {
      y = (a2 * c1 / a1 - c2) / (b2 - a2 * b1 / a1);
      x = (-b1 * y - c1) / a1;
    }
  }
  return x;
}

geometry::Line& geometry::Line::operator=(const geometry::Line& other) {
  this->guide = other.guide;
  this->point = other.point;
  return *this;
}
