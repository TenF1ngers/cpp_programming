// Дан связный неориентированный граф, в котором надо найти остовное дерево минимального
// веса с помощью алгоритма Борувки.

// В первой строке идут два натуральных числа N и M (2 ≤ N ≤ 5 ⋅ 104, 1 ≤ M ≤ 2 ⋅ 106).
// Далее идет M строк — описания ребер в формате u, v, w (1 ≤ u < v ≤ N, 1 ≤ w ≤ 109) — ребро
// между вершинами u и v веса w.

#include <iostream>
#include <unordered_set>
#include <vector>
#include <map>

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
  explicit WeightedGraph(const size_t& m) : size_(m) {
    edges_.reserve(size_);

    size_t begin = 0;
    size_t end = 0;
    size_t weight = 0;

    for (size_t i = 0; i < size_; ++i) {
      std::cin >> begin >> end >> weight;
      --begin;
      --end;

      if (end < begin) {
        std::swap(begin, end);
      }

      edges_.emplace_back(Edge(begin, end, weight));
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

  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;

  WeightedGraph graph(m);

  std::cout << graph.GetMinSpanningTreeWeight(n) << "\n";

  return 0;
}