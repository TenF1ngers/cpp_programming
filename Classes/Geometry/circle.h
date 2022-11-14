#pragma once

#include "interface.h"
#include "point.h"

class geometry::Circle : public geometry::IShape {
 public:
  geometry::Point centre;
  int64_t r;

  Circle(const geometry::Point& point, const int64_t& r);
  Circle(const Circle& other);
  ~Circle() final;
  Circle& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& temp_point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  Circle* Clone() const override;
  std::string ToString() const override;
  Circle& operator=(const Circle& other);
};