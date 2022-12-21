// Дан связный неориентированный граф, в котором надо найти остовное дерево минимального
// веса с помощью алгоритма Краскала. Гарантируется, что ребра будут отсортированы по весу
// по неубыванию.

// В первой строке идут два натуральных числа N и M (2 ≤ N ≤ 5 ⋅ 104, 1 ≤ M ≤ 2 ⋅ 106).
// Далее идет M строк — описания ребер в формате u, v, w (1 ≤ u < v ≤ N, 1 ≤ w ≤ 104) — ребро
// между вершинами u и v веса w.

#include <iostream>
#include <vector>

class DSU { // Disjoint set union
 private:
  struct Node {
    int parent_;
    int deep_;

    Node(const int& parent, const int& deep) : parent_(parent), deep_(deep) {
    }
  };

  std::vector<Node> parents_;

  int FindSet(const int& x) {
    if (parents_[x].parent_ == x) {
      return x;
    }

    return parents_[x].parent_ = FindSet(parents_[x].parent_);
  }

  void Bind(const int& first, const int& second) {
    if (parents_[first].deep_ < parents_[second].deep_) {
      parents_[first].parent_ = second;
    } else {
      parents_[second].parent_ = first;

      parents_[first].deep_ = std::max(parents_[second].deep_ + 1, parents_[first].deep_);
    }
  }

  bool AddEdge(const int& begin, const int& end) {
    auto first = FindSet(begin);
    auto second = FindSet(end);

    if (first != second) {
      Bind(first, second);

      return true;
    }

    return false;
  }

 public:
  explicit DSU(const int& n) {
    parents_.reserve(n);

    for (int i = 0; i < n; ++i) {
      parents_.emplace_back(Node(i, 0));
    }
  }

  // using Kruskal algorithm
  int64_t GetMinSpanningTreeWeight(const int& m) {
    int64_t sum = 0;

    int begin = 0;
    int end = 0;
    int weight = 0;

    for (int i = 0; i < m; ++i) {
      std::cin >> begin >> end >> weight;
      --begin;
      --end;

      if (AddEdge(begin, end)) {
        sum += weight;
      }
    }

    return sum;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  DSU set_unions(n);

  std::cout << set_unions.GetMinSpanningTreeWeight(m) << "\n";

  return 0;
}