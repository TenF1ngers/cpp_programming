// Алгоритм Грэхема

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>

#include "vector.h"
#include "point.h"
#include "segment.h"
#include "ray.h"
#include "line.h"
#include "circle.h"
#include "polygon.h"

class Node {
 public:
  geometry::Point point;
  Node* next;

  explicit Node(const geometry::Point& new_point) : point(new_point), next(nullptr) {
  }
};

class Stack {
 public:
  Node* begin;
  Node* end;
  int64_t size;

  Stack() : begin(nullptr), end(nullptr), size(0) {
  }

  void Push(const geometry::Point& point) {
    Node* new_node = new Node(point);
    if (begin == nullptr) {
      begin = end = new_node;
      ++size;
    } else {
      new_node->next = begin;
      begin = new_node;
      ++size;
    }
  }

  void Pop() {
    if (begin != nullptr) {
      Node* tmp = begin;
      begin = begin->next;
      delete tmp;
      --size;
    }
  }

  void Clear() {
    if (begin != nullptr) {
      Node* tmp = begin;
      while (size != 0) {
        begin = begin->next;
        delete tmp;
        --size;
        tmp = begin;
      }
    }
    delete this;
  }
};

template <class T>
void Swap(T& first, T& second) {
  T tmp = std::move(first);
  first = std::move(second);
  second = std::move(tmp);
}

bool operator<(const geometry::Vector& first, const geometry::Vector& second) {
  bool flag = false;
  if (VectorProduct(first, second) > 0) {
    flag = true;
  }
  return flag;
}

bool operator>(const geometry::Vector& first, const geometry::Vector& second) {
  bool flag = false;
  if (VectorProduct(first, second) < 0) {
    flag = true;
  }
  return flag;
}

void QuickSort(geometry::Point* points, int64_t size, const geometry::Point& key_point) {
  geometry::Vector pivot(key_point, points[size / 2]);
  int64_t i = 0, j = size - 1;
  do {
    while (geometry::Vector(key_point, points[i]) < pivot) {
      ++i;
    }
    while (geometry::Vector(key_point, points[j]) > pivot) {
      --j;
    }
    if (i <= j) {
      Swap(points[i], points[j]);
      ++i;
      --j;
    }
  } while (i <= j);
  if (j > 0) {
    QuickSort(&points[0], j + 1, key_point);
  }
  if (i < size) {
    QuickSort(&points[i], size - i, key_point);
  }
}

Stack* GrahamConvexHull(geometry::Point* points, int64_t size) {
  geometry::Point lower_point = points[0];
  int64_t pos = 0;
  for (int64_t i = 1; i < size; ++i) {
    if (points[i].y < lower_point.y) {
      lower_point = points[i];
      pos = i;
    } else if (points[i].y == lower_point.y) {
      if (points[i].x < lower_point.x) {
        lower_point = points[i];
        pos = i;
      }
    }
  }
  Swap(points[size - 1], points[pos]);
  QuickSort(points, size - 1, lower_point);
  auto* convex_hull = new Stack;
  convex_hull->Push(lower_point);
  int64_t id_of_max_len = 0;
  for (int64_t i = 0; i < size - 1; ++i) {
    id_of_max_len = i;
    if ((i != 0) && (points[i] == points[i - 1])) {
      continue;
    }
    while ((i + 1 != size - 1) && (geometry::Line(lower_point, points[id_of_max_len]).ContainsPoint(points[i + 1]))) {
      geometry::Vector first(lower_point, points[i + 1]);
      geometry::Vector second(lower_point, points[id_of_max_len]);
      if ((ScalarProduct(second, first) > 0) && ((first.x * first.x + first.y * first.y) > (second.x * second.x + second.y * second.y))) {
        id_of_max_len = i + 1;
      }
      ++i;
    }
    convex_hull->Push(points[id_of_max_len]);
    while (VectorProduct(geometry::Vector(convex_hull->begin->next->point, convex_hull->begin->point),
                         geometry::Vector(convex_hull->begin->point, points[i + 1])) <= 0) {
      convex_hull->Pop();
      ++i;
      id_of_max_len = i;
      while ((i + 1 != size - 1) && (geometry::Line(lower_point, points[id_of_max_len]).ContainsPoint(points[i + 1]))) {
        geometry::Vector first(lower_point, points[i + 1]);
        geometry::Vector second(lower_point, points[id_of_max_len]);
        if ((first.x * first.x + first.y * first.y) > (second.x * second.x + second.y * second.y)) {
          id_of_max_len = i + 1;
        }
        ++i;
      }
      while (VectorProduct(geometry::Vector(convex_hull->begin->next->point, convex_hull->begin->point),
                           geometry::Vector(convex_hull->begin->point, points[id_of_max_len])) < 0) {
        convex_hull->Pop();
      }
      convex_hull->Push(points[id_of_max_len]);
    }
    int64_t tmp = i;
    while (VectorProduct(geometry::Vector(convex_hull->begin->next->point, convex_hull->begin->point),
                         geometry::Vector(convex_hull->begin->point, points[tmp + 1])) == 0) {
      convex_hull->Pop();
      ++tmp;
      ++i;
      convex_hull->Push(points[tmp]);
    }
    if (convex_hull->begin->next != convex_hull->end) {
      while ((VectorProduct(geometry::Vector(convex_hull->begin->point, convex_hull->begin->next->point),
                            geometry::Vector(convex_hull->begin->next->point, convex_hull->begin->next->next->point)) == 0) ||
             (VectorProduct(geometry::Vector(convex_hull->begin->next->next->point, convex_hull->begin->next->point),
                            geometry::Vector(convex_hull->begin->next->point, convex_hull->begin->point)) < 0)) {
        Node* temp = convex_hull->begin;
        convex_hull->begin = convex_hull->begin->next;
        convex_hull->begin->point = temp->point;
        delete temp;
        --convex_hull->size;
      }
    }
  }
  return convex_hull;
}

int64_t Area(Stack* convex_hull, const int64_t& size);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  std::cin >> n;
  auto* points = new geometry::Point[n];
  int64_t x = 0, y = 0;
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> x >> y;
    points[i].x = x;
    points[i].y = y;
  }
  Stack* convex_hull = GrahamConvexHull(points, n);
  std::cout << convex_hull->size << "\n";
  Node *left = convex_hull->end, *tmp = convex_hull->begin;
  for (int64_t i = 0; i < convex_hull->size - 1; ++i) {
    if (tmp->point.x >= convex_hull->end->point.x) {
      break;
    }
    if (tmp->point.x < left->point.x) {
      left = tmp;
    }
    tmp = tmp->next;
  }
  tmp = left;
  while (tmp != nullptr) {
    std::cout << tmp->point.x << " " << tmp->point.y << "\n";
    tmp = tmp->next;
  }
  tmp = convex_hull->begin;
  while (tmp != left) {
    std::cout << tmp->point.x << " " << tmp->point.y << "\n";
    tmp = tmp->next;
  }
  int64_t area = Area(convex_hull, convex_hull->size);
  std::cout << area / 2 << "." << (area % 2) * 5 << "\n";
  convex_hull->Clear();
  delete[] points;
  return 0;
}

int64_t Area(Stack* convex_hull, const int64_t& size) {
  int64_t area = 0;
  geometry::Point point(0, 0);
  Node* tmp = convex_hull->begin;
  for (int64_t i = 0; i < size - 1; ++i) {
    area += VectorProduct(geometry::Vector(point, tmp->point), geometry::Vector(point, tmp->next->point));
    tmp = tmp->next;
  }
  area += VectorProduct(geometry::Vector(point, tmp->point), geometry::Vector(point, convex_hull->begin->point));
  return std::abs(area);
}