// В неориентированный взвешенный граф добавляют ребра. Напишите программу, которая в
// некоторые моменты находит сумму весов ребер в компоненте связности.

// В первой строке записано два числа n и m (1 ≤ n, m ≤ 106) — количество вершин в графе 
// и количество производимых добавлений и запросов. Далее следует m строк с описанием
// добавления или запроса. Каждая строка состоит из двух или четырех чисел.

// Первое из чисел обозначает код операции. Если первое число 1, то за ним следует еще три
// числа x, y, w. Это означает, что в граф добавляется ребро xy веса w (1 ≤ x < y ≤ n,
// 1 ≤ w ≤ 1000). Кратные ребра допустимы.

// Если первое число 2, то за ним следует ровно одно число x. Это означает, что необходимо
// ответить на вопрос, какова сумма весов ребер в компоненте связности, которой принадлежит
// вершина x (1 ≤ x ≤ n).

#include <iostream>
#include <vector>

class DSU { // Disjoint set union
 private:
  struct Node {
    int parent_;
    int deep_;
    int64_t weight_;

    Node(const int& parent, const int& deep, const int64_t& weight) : parent_(parent), deep_(deep), weight_(weight) {
    }
  };

  std::vector<Node> parents_;

  int FindSet(const int& x) {
    if (parents_[x].parent_ == x) {
      return x;
    }

    return parents_[x].parent_ = FindSet(parents_[x].parent_);
  }

  void Bind(const int& first, const int& second, const int64_t& weight) {
    if (parents_[first].deep_ < parents_[second].deep_) {
      parents_[first].parent_ = second;

      parents_[second].weight_ += parents_[first].weight_ + weight;
    } else {
      parents_[second].parent_ = first;

      parents_[first].deep_ = std::max(parents_[second].deep_ + 1, parents_[first].deep_);

      parents_[first].weight_ += parents_[second].weight_ + weight;
    }
  }

 public:
  explicit DSU(const int& n) {
    parents_.reserve(n);

    for (int i = 0; i < n; ++i) {
      parents_.emplace_back(Node(i, 0, 0));
    }
  }

  void AddEdge(const int& begin, const int& end, const int64_t& weight) {
    if (begin != end) {
      auto first = FindSet(begin);
      auto second = FindSet(end);

      if (first != second) {
        Bind(first, second, weight);
      } else {
        parents_[first].weight_ += weight;
      }
    }
  }

  void GetWeight(const int& x) {
    auto root_id = FindSet(x);

    std::cout << parents_[root_id].weight_ << "\n";
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

  int id = 0;

  int begin = 0;
  int end = 0;
  int weight = 0;

  int x = 0;

  for (int i = 0; i < m; ++i) {
    std::cin >> id;

    switch (id) {
      case 1: {
        std::cin >> begin >> end >> weight;
        --begin;
        --end;

        set_unions.AddEdge(begin, end, weight);

        break;
      }
      case 2: {
        std::cin >> x;
        --x;

        set_unions.GetWeight(x);

        break;
      }
    }
  }

  return 0;
}