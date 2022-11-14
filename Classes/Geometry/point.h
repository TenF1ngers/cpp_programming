#pragma once

#include <iostream>

#include "interface.h"
#include "vector.h"

class geometry::Point : public geometry::IShape {
 public:
  int64_t x, y;

  ~Point() final;
  Point();
  Point(int64_t first, int64_t second);
  Point(const Point& other);
  Point& Move(const geometry::Vector& vector) override;
  bool ContainsPoint(const geometry::Point& point) const override;
  bool CrossesSegment(const geometry::Segment& segment) const override;
  Point* Clone() const override;
  std::string ToString() const override;
  geometry::Vector operator-(const geometry::Point& point) const;
  Point& operator=(const Point& other);
  double Length(const geometry::Segment& other);
};

bool operator!=(const geometry::Point& first, const geometry::Point& second);
bool operator==(const geometry::Point& first, const geometry::Point& second);
geometry::Point operator+(const geometry::Point& point, const geometry::Vector& vector);