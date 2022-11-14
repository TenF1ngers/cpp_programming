#pragma once

#include "interface.h"
#include "point.h"

class geometry::Segment : public geometry::IShape {
 public:
  geometry::Point first, second;

  ~Segment() final;
  Segment() = default;
  Segment(const geometry::Point& first, const geometry::Point& second);
  Segment(const Segment& other);
  Segment& Move(const Vector& vector) override;
  bool ContainsPoint(const geometry::Point& point) const override;
  bool CrossesSegment(const geometry::Segment& segment) const override;
  Segment* Clone() const override;
  std::string ToString() const override;
  Segment& operator=(const Segment& other);
};

bool Crossing(const geometry::Segment& first, const geometry::Segment& second);