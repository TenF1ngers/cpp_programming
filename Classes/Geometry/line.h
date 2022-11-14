#pragma once

#include "interface.h"
#include "vector.h"
#include "point.h"

class geometry::Line : public geometry::IShape {
 public:
  geometry::Point point;
  geometry::Vector guide;

  Line(const geometry::Point& first, const geometry::Point& second);
  Line(const Line& other);
  ~Line() final;
  Line& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& temp_point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  Line* Clone() const override;
  std::string ToString() const override;
  Line& operator=(const Line& other);
};

long double IntersectionX(const geometry::Line& first, const geometry::Line& second);