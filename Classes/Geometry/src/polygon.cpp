#include <iostream>

#include "../interface.h"
#include "../segment.h"
#include "../ray.h"
#include "../polygon.h"

geometry::Polygon::~Polygon() = default;

geometry::Polygon::Polygon(std::vector<Point>&& vector) : points(std::move(vector)) {
}

geometry::Polygon::Polygon(const std::vector<geometry::Point>& vector) : points(vector) {
}

geometry::Polygon::Polygon(const geometry::Polygon& other) : points(other.points) {
}

geometry::Polygon& geometry::Polygon::Move(const Vector& vector) {
  auto length = static_cast<int64_t>(this->points.size());
  for (int64_t i = 0; i < length; ++i) {
    this->points[i].x += vector.x;
    this->points[i].y += vector.y;
  }
  return *this;
}

bool geometry::Polygon::ContainsPoint(const Point& temp_point) const {
  bool flag = false;
  auto length = static_cast<int64_t>(this->points.size());
  int64_t count = 0;
  Vector guide(temp_point.x, temp_point.y, temp_point.x + 1, temp_point.y);
  Ray ray(temp_point, temp_point + guide);
  for (int64_t i = 0; i < length - 1; ++i) {
    if (temp_point.CrossesSegment(geometry::Segment(this->points[i], this->points[i + 1]))) {
      flag = true;
    }
    if (!flag) {
      if (ray.CrossesSegment(Segment(this->points[i], this->points[i + 1]))) {
        if (VectorProduct(ray.guide, geometry::Vector(this->points[i], this->points[i + 1])) != 0.) {
          if (this->points[i].y < this->points[i + 1].y) {
            if (!ray.ContainsPoint(this->points[i])) {
              ++count;
            }
          } else {
            if (!ray.ContainsPoint(this->points[i + 1])) {
              ++count;
            }
          }
        }
      }
    }
  }
  if (temp_point.CrossesSegment(geometry::Segment(this->points[length - 1], this->points[0]))) {
    flag = true;
  }
  if (!flag) {
    if (VectorProduct(ray.guide, geometry::Vector(this->points[length - 1], this->points[0])) != 0.) {
      if (ray.CrossesSegment(Segment(this->points[length - 1], this->points[0]))) {
        if (this->points[length - 1].y < this->points[0].y) {
          if (!ray.ContainsPoint(this->points[length - 1])) {
            ++count;
          }
        } else {
          if (!ray.ContainsPoint(this->points[0])) {
            ++count;
          }
        }
      }
    }
  }
  if (!flag) {
    if (count % 2 != 0) {
      flag = true;
    }
  }
  return flag;
}

bool geometry::Polygon::CrossesSegment(const Segment& segment) const {
  bool flag = false;
  auto length = static_cast<int64_t>(this->points.size());
  for (int64_t i = 0; i < length - 1; ++i) {
    if (Segment(this->points[i], this->points[i + 1]).CrossesSegment(segment)) {
      flag = true;
      break;
    }
  }
  if (Segment(this->points[length - 1], this->points[0]).CrossesSegment(segment)) {
    flag = true;
  }
  return flag;
}

geometry::Polygon* geometry::Polygon::Clone() const {
  auto* new_polygon = new geometry::Polygon;
  new_polygon->points = this->points;
  return new_polygon;
}

std::string geometry::Polygon::ToString() const {
  auto length = static_cast<int64_t>(this->points.size());
  std::string message = "Polygon(" + this->points[0].ToString();
  for (int64_t i = 1; i < length; ++i) {
    message += ", " + this->points[i].ToString();
  }
  message += ")";
  return message;
}

geometry::Polygon& geometry::Polygon::operator=(const geometry::Polygon& other) {
  this->points = other.points;
  return *this;
}

bool geometry::Polygon::IsConvexity() const {
  bool flag = true;
  char sign_of_angle = '.';
  auto len = static_cast<int64_t>(this->points.size());
  int64_t j = 0;
  double temp_vector_product = 0.;
  do {
    temp_vector_product = VectorProduct(geometry::Vector(this->points[j], this->points[j + 1]),
                                        geometry::Vector(this->points[j + 1], this->points[j + 2]));
    ++j;
  } while ((temp_vector_product == 0.) && (j < len - 2));
  if (temp_vector_product > 0) {
    sign_of_angle = '+';
  } else {
    sign_of_angle = '-';
  }
  for (int64_t i = j; i < len - 2; ++i) {
    if (VectorProduct(geometry::Vector(this->points[i], this->points[i + 1]),
                      geometry::Vector(this->points[i + 1], this->points[i + 2])) == 0.) {
      continue;
    }
    switch (sign_of_angle) {
      case '+': {
        if (VectorProduct(geometry::Vector(this->points[i], this->points[i + 1]),
                          geometry::Vector(this->points[i + 1], this->points[i + 2])) < 0) {
          flag = false;
        }
        break;
      }
      case '-': {
        if (VectorProduct(geometry::Vector(this->points[i], this->points[i + 1]),
                          geometry::Vector(this->points[i + 1], this->points[i + 2])) > 0) {
          flag = false;
        }
        break;
      }
    }
    if (!flag) {
      break;
    }
  }
  if (flag) {
    if (VectorProduct(geometry::Vector(this->points[len - 2], this->points[len - 1]),
                      geometry::Vector(this->points[len - 1], this->points[0])) != 0.) {
      switch (sign_of_angle) {
        case '+': {
          if (VectorProduct(geometry::Vector(this->points[len - 2], this->points[len - 1]),
                            geometry::Vector(this->points[len - 1], this->points[0])) < 0.) {
            flag = false;
          }
          break;
        }
        case '-': {
          if (VectorProduct(geometry::Vector(this->points[len - 2], this->points[len - 1]),
                            geometry::Vector(this->points[len - 1], this->points[0])) > 0.) {
            flag = false;
          }
          break;
        }
      }
    }
  }
  if (flag) {
    if (VectorProduct(geometry::Vector(this->points[len - 1], this->points[0]),
                      geometry::Vector(this->points[0], this->points[1])) != 0.) {
      switch (sign_of_angle) {
        case '+': {
          if (VectorProduct(geometry::Vector(this->points[len - 1], this->points[0]),
                            geometry::Vector(this->points[0], this->points[1])) < 0.) {
            flag = false;
          }
          break;
        }
        case '-': {
          if (VectorProduct(geometry::Vector(this->points[len - 1], this->points[0]),
                            geometry::Vector(this->points[0], this->points[1])) > 0.) {
            flag = false;
          }
          break;
        }
      }
    }
  }
  return flag;
}

int64_t geometry::Polygon::Area() const {
  int64_t area = 0.;
  auto len = static_cast<int64_t>(this->points.size());
  geometry::Point point(0, 0);
  for (int64_t i = 0; i < len - 1; ++i) {
    area += VectorProduct(geometry::Vector(point, this->points[i]), geometry::Vector(point, this->points[i + 1]));
  }
  area += VectorProduct(geometry::Vector(point, this->points[len - 1]), geometry::Vector(point, this->points[0]));
  return std::abs(area);
}

std::vector<geometry::Point> JarvisConvexHull(std::vector<geometry::Point>&& points) {
  geometry::Point lower_point = points[0];
  for (int64_t i = 1; i < static_cast<int64_t>(points.size()); ++i) {
    if (points[i].y < lower_point.y) {
      lower_point = points[i];
    } else if (points[i].y == lower_point.y) {
      if (points[i].x < lower_point.x) {
        lower_point = points[i];
      }
    }
  }
  std::vector<geometry::Point> convex_hull{};
  convex_hull.push_back(lower_point);
  geometry::Point temp_point, point_of_min_angle = points[0], current_point = lower_point;
  geometry::Vector guide(current_point.x, current_point.y, current_point.x + 1, current_point.y);
  do {
    temp_point = current_point;
    for (int64_t i = 0; i < static_cast<int64_t>(points.size()); ++i) {
      if (points[i] == current_point) {
        continue;
      }
      if (geometry::Ray(current_point, current_point + guide).ContainsPoint(points[i])) {
        current_point = points[i];
        for (int64_t j = i + 1; j < static_cast<int64_t>(points.size()); ++j) {
          if (points[j] == current_point) {
            continue;
          }
          if (geometry::Ray(current_point, current_point + guide).ContainsPoint(points[j])) {
            current_point = points[j];
          }
        }
        convex_hull.push_back(current_point);
        break;
      }
      geometry::Vector first = geometry::Vector(current_point, points[i]);
      geometry::Vector second = geometry::Vector(current_point, point_of_min_angle);
      if (VectorProduct(first, second) == 0) {
        if ((first.x * first.x + first.y * first.y) > (second.x * second.x + second.y * second.y)) {
          point_of_min_angle = points[i];
        }
      } else if (VectorProduct(first, second) > 0) {
        point_of_min_angle = points[i];
      }
    }
    if (current_point == temp_point) {
      convex_hull.push_back(point_of_min_angle);
      guide = geometry::Vector(current_point, point_of_min_angle);
      current_point = point_of_min_angle;
    }
  } while (convex_hull[convex_hull.size() - 1] != lower_point);
  convex_hull.pop_back();
  return convex_hull;
}
