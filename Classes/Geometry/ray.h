#pragma once

#include "interface.h"
#include "point.h"

class geometry::Ray : public geometry::IShape {
 public:
  geometry::Point point;
  geometry::Vector guide;

  Ray();
  Ray(const geometry::Point& first, const geometry::Point& second);
  Ray(const Ray& other);
  ~Ray() final;
  Ray& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& temp_point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  Ray* Clone() const override;
  std::string ToString() const override;
  Ray& operator=(const Ray& other);
};