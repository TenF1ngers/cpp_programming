#pragma once

#include <iostream>
#include <vector>
#include <utility>

#include "interface.h"
#include "point.h"

class geometry::Polygon : public geometry::IShape {
 public:
  std::vector<geometry::Point> points{};

  ~Polygon() final;
  Polygon() = default;
  Polygon(const Polygon& other);
  explicit Polygon(std::vector<geometry::Point>&& vector);
  explicit Polygon(const std::vector<geometry::Point>& vector);
  Polygon& Move(const geometry::Vector& vector) override;
  bool ContainsPoint(const geometry::Point& temp_point) const override;
  bool CrossesSegment(const geometry::Segment& segment) const override;
  geometry::Polygon* Clone() const override;
  std::string ToString() const override;
  Polygon& operator=(const Polygon& other);
  bool IsConvexity() const;
  int64_t Area() const;
};

std::vector<geometry::Point> JarvisConvexHull(std::vector<geometry::Point>&& points);