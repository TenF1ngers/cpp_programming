#include "../interface.h"
#include "../vector.h"
#include "../segment.h"

bool Crossing(const geometry::Segment& first, const geometry::Segment& second) {
  geometry::Vector guide(first.first, first.second);
  int64_t a = guide.y, b = -guide.x, c = -(first.first.x * a) - (first.first.y * b);
  bool flag = false;
  if (((a * second.first.x + b * second.first.y + c > 0) && (a * second.second.x + b * second.second.y + c < 0)) ||
      ((a * second.first.x + b * second.first.y + c < 0) && (a * second.second.x + b * second.second.y + c > 0)) ||
      (a * second.first.x + b * second.first.y + c == 0) || (a * second.second.x + b * second.second.y + c == 0)) {
    flag = true;
  }
  return flag;
}

geometry::Segment::~Segment() = default;

geometry::Segment::Segment(const geometry::Point& first, const geometry::Point& second) : first(first), second(second) {
}

geometry::Segment::Segment(const geometry::Segment& other) : first(other.first), second(other.second) {
}

geometry::Segment& geometry::Segment::Move(const Vector& vector) {
  this->first.x += vector.x;
  this->first.y += vector.y;
  this->second.x += vector.x;
  this->second.y += vector.y;
  return *this;
}

bool geometry::Segment::ContainsPoint(const geometry::Point& point) const {
  bool flag = false;
  if (point.CrossesSegment(*this)) {
    flag = true;
  }
  return flag;
}

bool geometry::Segment::CrossesSegment(const geometry::Segment& segment) const {
  bool flag = false;
  if (this->first == this->second) {
    if (this->first.CrossesSegment(segment)) {
      flag = true;
    }
  } else if (segment.first == segment.second) {
    if (segment.first.CrossesSegment(*this)) {
      flag = true;
    }
  } else {
    bool first_line_with_second = Crossing(*this, segment);
    bool second_line_with_first = Crossing(segment, *this);
    if (first_line_with_second && second_line_with_first) {
      if (VectorProduct(geometry::Vector(this->first, this->second), geometry::Vector(segment.first, segment.second)) ==
          0) {
        if (this->first.y == this->second.y) {
          geometry::Point first_left = (this->first.x <= this->second.x) ? this->first : this->second;
          geometry::Point second_left = (segment.first.x <= segment.second.x) ? segment.first : segment.second;
          geometry::Point first_right = (this->first.x > this->second.x) ? this->first : this->second;
          geometry::Point second_right = (segment.first.x > segment.second.x) ? segment.first : segment.second;
          geometry::Point left_max = (std::max(first_left.x, second_left.x) == first_left.x) ? first_left : second_left;
          geometry::Point right_min =
              (std::min(first_right.x, second_right.x) == second_right.x) ? second_right : first_right;
          if ((left_max.CrossesSegment(*this) && left_max.CrossesSegment(segment)) ||
              (right_min.CrossesSegment(*this) && right_min.CrossesSegment(segment))) {
            flag = true;
          }
        } else {
          geometry::Point first_left = (this->first.y <= this->second.y) ? this->first : this->second;
          geometry::Point second_left = (segment.first.y <= segment.second.y) ? segment.first : segment.second;
          geometry::Point first_right = (this->first.y > this->second.y) ? this->first : this->second;
          geometry::Point second_right = (segment.first.y > segment.second.y) ? segment.first : segment.second;
          geometry::Point left_max = (std::max(first_left.y, second_left.y) == first_left.y) ? first_left : second_left;
          geometry::Point right_min =
              (std::min(first_right.y, second_right.y) == second_right.y) ? second_right : first_right;
          if ((left_max.CrossesSegment(*this) && left_max.CrossesSegment(segment)) ||
              (right_min.CrossesSegment(*this) && right_min.CrossesSegment(segment))) {
            flag = true;
          }
        }
      } else {
        flag = true;
      }
    }
  }
  return flag;
}

geometry::Segment* geometry::Segment::Clone() const {
  auto* new_segment = new Segment(this->first, this->second);
  return new_segment;
}

std::string geometry::Segment::ToString() const {
  std::string message = "Segment(" + this->first.ToString() + ", " + this->second.ToString() + ")";
  return message;
}

geometry::Segment& geometry::Segment::operator=(const geometry::Segment& other) {
  this->first = other.first;
  this->second = other.second;
  return *this;
}
