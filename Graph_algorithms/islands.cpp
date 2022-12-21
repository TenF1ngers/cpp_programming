// Одно разбросанное на островах Океании государство решило создать сеть автомобильных дорог
// (вернее, мостов) По каждому мосту можно перемещаться в обе стороны. Был разработан план
// очередности строительства мостов и известно, что после постройки всех мостов можно будет
// проехать по ним с каждого острова на каждый (возможно, через некоторые промежуточные
// острова).

// Однако, этот момент может наступить до того, как будут построены все мосты. Ваша задача
// состоит в определении такого минимального количества мостов, после постройки которого
// (в порядке строительства по плану) можно будет попасть с любого острова на любой другой.

// Первая строка содержит два числа: N — число островов (1 ≤ N ≤ 100000) и M — количество
// мостов в плане (1 ≤ M ≤ 200000). В каждой следующей строке содержится описание моста —
// два числа x и y (0 ≤ x, y < N) — номера соединяемых островов.

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
  int count_disjoint_;

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
    if (count_disjoint_ == 1) {
      return false;
    }

    auto first = FindSet(begin);
    auto second = FindSet(end);

    if (first != second) {
      Bind(first, second);

      --count_disjoint_;
    }

    return true;
  }

 public:
  explicit DSU(const int& n) : count_disjoint_(n) {
    parents_.reserve(n);

    for (int i = 0; i < n; ++i) {
      parents_.emplace_back(Node(i, 0));
    }
  }

  void Create(const int& m) {
    int begin = 0;
    int end = 0;

    int count = 0;

    for (int i = 0; i < m; ++i) {
      std::cin >> begin >> end;

      if (!AddEdge(begin, end)) {
        break;
      }

      ++count;
    }

    std::cout << count << "\n";
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  DSU set_unions(n);

  set_unions.Create(m);

  return 0;
}