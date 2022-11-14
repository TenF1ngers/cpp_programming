// Входной файл состоит из следующей последовательности строк. Первая строка содержит
// число N (N ≤ 105) — количество автобусных маршрутов, M (M ≤ 105) — количество
// площадей. Каждая из последующих N строк служит для описания соответствующего
// автобусного маршрута и содержит сначала число k (k ≤ 105), определяющее количество
// элементов маршрута, а затем k + 1 чисел, задающих номера площадей, которые
// последовательно проезжает автобус на этом маршруте. Общая длина маршрутов не более
// 105 улиц. При описании маршрута всегда задаются номера первой и последней площади
// маршрута, причем они всегда совпадают.

#include <iostream>
#include <set>
#include <stack>
#include <vector>

class City {
 private:
  enum Color { White, Gray, Black };

  struct Node {
    std::multiset<int> income_;
    std::multiset<int> outcome_;
  };

  std::vector<Node> vertexes_;
  std::vector<Color> colors_;
  size_t size_;

  void DfsVisit(const int& node, bool& is_euler) {
    colors_[node] = Gray;

    if (vertexes_[node].income_.size() != vertexes_[node].outcome_.size()) {
      is_euler = false;

      return;
    }

    for (auto& neighbor : vertexes_[node].outcome_) {
      if (colors_[neighbor] == White) {
        DfsVisit(neighbor, is_euler);

        if (!is_euler) {
          return;
        }
      }
    }
    for (auto& neighbor : vertexes_[node].income_) {
      if (colors_[neighbor] == White) {
        DfsVisit(neighbor, is_euler);

        if (!is_euler) {
          return;
        }
      }
    }

    colors_[node] = Black;
  }

  void EulerDfsVisit(const int& node, std::stack<int>& way) {
    std::stack<int> passed;

    int next = 0;

    while (!vertexes_[node].outcome_.empty()) {
      next = *vertexes_[node].outcome_.begin();

      passed.push(next);
      vertexes_[node].outcome_.extract(next);

      EulerDfsVisit(next, way);
      way.push(passed.top());
      passed.pop();
    }
  }

 public:
  City(const int& n, const int& m) : size_(m) {
    vertexes_.resize(size_);
    colors_.resize(size_, White);

    int from = 0;
    int to = 0;

    int count = 0;

    for (int i = 0; i < n; ++i) {
      std::cin >> count >> from >> to;
      --from;
      --to;

      vertexes_[from].outcome_.emplace(to);
      vertexes_[to].income_.emplace(from);
      from = to;

      for (int j = 0; j < count - 1; ++j) {
        std::cin >> to;
        --to;

        vertexes_[from].outcome_.emplace(to);
        vertexes_[to].income_.emplace(from);
        from = to;
      }
    }
  }

  bool CheckEuler() {
    bool is_euler = true;
    int start = 0;

    while ((start < static_cast<int>(size_)) && vertexes_[start].outcome_.empty()) {
      ++start;
    }

    for (int i = start; i < static_cast<int>(size_); ++i) {
      if (colors_[i] == White) {

        if ((i > start) && ((!vertexes_[i].income_.empty()) || (!vertexes_[i].outcome_.empty()))) {
          is_euler = false;

          break;
        }

        DfsVisit(i, is_euler);

        if (!is_euler) {
          break;
        }
      }
    }

    if (start == static_cast<int>(size_)) {
      is_euler = false;
    }

    return is_euler;
  }

  std::stack<int> EulerCycle() {
    std::stack<int> way;

    int start = 0;

    while (vertexes_[start].outcome_.empty()) {
      ++start;
    }

    EulerDfsVisit(start, way);

    way.push(start);

    return way;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  City graph(n, m);

  if (graph.CheckEuler()) {
    auto way = std::move(graph.EulerCycle());

    std::cout << way.size() << " ";
    while (!way.empty()) {
      std::cout << way.top() + 1 << " ";

      way.pop();
    }
    std::cout << "\n";
  } else {
    std::cout << 0 << "\n";
  }

  return 0;
}