// Вы — глава агенства, в котором работает N сотрудников — шпионы с кодовыми номерами от 1 до
// N. Шпионы были посланы в различные страны и получили кусочки важной информации. Ваша задача
// состоит в следующем:

// Организовать встречи между некоторыми шпионами. На каждой такой встрече ровно два шпиона
// оказываются в одном месте и обмениваются всей информацией, которую получили сами или узнали
// от других шпионов на предыдущих встречах. Каждую из возможных встреч сложно и затратно
// организовать, поэтому вам известны все стоимости.

// После того, как все встречи состоялись, выбирается группа шпионов, и они посылаются на
// задание по спасению мира. Для каждого шпиона известно, сколько денег он изведет, если его
// включить в эту группу. Задание должно быть выполнено, поэтому очень важно, чтобы выбранные
// шпионы все вместе обладали всей информацией, полученной агенством.

// Найдите минимальную цену, за которую можно спасти мир.

// Первая строка содержит натуральное число N — количество шпионов (2 ≤ N ≤ 1000). Каждая из
// следующих строк содержит N натуральных чисел, не превосходящих 106. Число в k-й строке и
// m-м столбце обозначает стоимость встречи между шпионами k и m и совпадает с числом в m-й
// строке и k-м столбце (если k = m, то соответствующее число будет равно 0). Следующая строка
// содержит N чисел, i-е из них равно стоимости послать i-го шпиона на задание. Все стоимости
// являются положительными целыми числами.

#include <iostream>
#include <vector>

class DSU {  // Disjoint set union
 private:
  struct Node {
    size_t parent_;
    size_t deep_;

    Node(const size_t& parent, const size_t& deep) : parent_(parent), deep_(deep) {
    }
  };

  std::vector<Node> parents_;
  size_t disjoint_count_;

 public:
  explicit DSU(const size_t& n) : disjoint_count_(n) {
    parents_.reserve(disjoint_count_);

    for (size_t i = 0; i < disjoint_count_; ++i) {
      parents_.emplace_back(Node(i, 0));
    }
  }

  size_t FindSet(const size_t& x) {
    if (parents_[x].parent_ == x) {
      return x;
    }

    return parents_[x].parent_ = FindSet(parents_[x].parent_);
  }

  void Bind(const size_t& root, const size_t& other) {
    if (parents_[root].deep_ < parents_[other].deep_) {
      parents_[root].parent_ = other;
    } else {
      parents_[other].parent_ = root;
      parents_[root].deep_ = std::max(parents_[other].deep_ + 1, parents_[root].deep_);
    }

    --disjoint_count_;
  }

  size_t GetCount() const {
    return disjoint_count_;
  }
};

class WeightedGraph {
 private:
  struct Edge {
    size_t begin_;
    size_t end_;
    size_t weight_;

    Edge(const size_t& beg, const size_t& end, const size_t& w) : begin_(beg), end_(end), weight_(w) {
    }

    bool operator<(const Edge& other) const {
      if ((weight_ == other.weight_) && (begin_ == other.begin_)) {
        return end_ < other.end_;
      }

      if (weight_ == other.weight_) {
        return begin_ < other.begin_;
      }

      return weight_ < other.weight_;
    }
  };

  std::vector<Edge> edges_;
  size_t size_;

 public:
  explicit WeightedGraph(const std::vector<std::vector<int> >& matrix)
      : size_(matrix.size() * (matrix.size() - 1) / 2) {
    edges_.reserve(size_);

    size_t begin = 0;
    size_t end = 0;
    size_t weight = 0;

    for (size_t i = 0; i < matrix.size() - 1; ++i) {
      for (size_t j = i + 1; j < matrix.size(); ++j) {
        begin = i;
        end = j;
        weight = matrix[i][j];

        if (end < begin) {
          std::swap(begin, end);
        }

        edges_.emplace_back(Edge(begin, end, weight));
      }
    }

    auto new_vertex = matrix.size();
    size_t value = 0;

    for (size_t i = 0; i < matrix.size(); ++i) {
      std::cin >> value;

      edges_.emplace_back(Edge(i, new_vertex, value));
    }
  }

  // using Boruvka algorithm
  size_t GetMinSpanningTreeWeight(size_t count) {
    size_t sum = 0;

    DSU unions(count);

    size_t first = 0;
    size_t second = 0;

    while (unions.GetCount() != 1) {
      std::vector<Edge> min_edges(count, Edge(0, 0, SIZE_MAX));

      for (auto& edge : edges_) {
        first = unions.FindSet(edge.begin_);
        second = unions.FindSet(edge.end_);

        if (first != second) {
          if (edge < min_edges[first]) {
            min_edges[first] = edge;
          }

          if (edge < min_edges[second]) {
            min_edges[second] = edge;
          }
        }
      }

      for (auto& edge : min_edges) {
        if (edge.weight_ == SIZE_MAX) {
          continue;
        }

        first = unions.FindSet(edge.begin_);
        second = unions.FindSet(edge.end_);

        if (first != second) {
          sum += edge.weight_;

          unions.Bind(first, second);
        }
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
  std::cin >> n;

  std::vector<std::vector<int> > matrix(n, std::vector<int>(n, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> matrix[i][j];
    }
  }

  WeightedGraph graph(matrix);

  std::cout << graph.GetMinSpanningTreeWeight(n + 1) << "\n";

  return 0;
}