// Дан ориентированный граф, в котором могут быть кратные ребра и петли. Каждое ребро имеет
// вес, выражающийся целым числом (возможно, отрицательным). Гарантируется, что циклы
// отрицательного веса отсутствуют.

// Требуется посчитать длины кратчайших путей от вершины номер 1 до всех остальных вершин.

// Программа получает сначала число N (1 ≤ N ≤ 100) — количество вершин графа и число M
// (0 ≤ M ≤ 10000) — количество ребер. В следующих строках идет M троек чисел, описывающих
// ребра: начало ребра, конец ребра и вес (вес — целое число от -100 до 100).

#include <iostream>
#include <vector>

class WeightedGraph {
 private:
  struct Edge {
    size_t begin_;
    size_t end_;
    size_t weight_;

    Edge(const size_t& beg, const size_t& end, const size_t& w) : begin_(beg), end_(end), weight_(w) {
    }
  };

  std::vector<Edge> edges_;
  size_t vertex_count_;
  size_t edges_count_;

  bool Relax(std::vector<size_t>& dist, const Edge& edge) {
    if ((dist[edge.begin_] != 30000) && (dist[edge.end_] > dist[edge.begin_] + edge.weight_)) {
      dist[edge.end_] = dist[edge.begin_] + edge.weight_;

      return true;
    }

    return false;
  }

 public:
  WeightedGraph(const size_t& n, const size_t& m) : vertex_count_(n), edges_count_(m) {
    edges_.reserve(edges_count_);

    size_t begin = 0;
    size_t end = 0;
    size_t weight = 0;

    for (size_t i = 0; i < edges_count_; ++i) {
      std::cin >> begin >> end >> weight;
      --begin;
      --end;

      edges_.emplace_back(Edge(begin, end, weight));
    }
  }

  // using Bellman-Ford algorithm
  std::vector<size_t> GetDistances(size_t pos) {
    std::vector<size_t> dist(vertex_count_, 30000);
    dist[pos] = 0;

    for (size_t i = 0; i < vertex_count_ - 1; ++i) {
      for (auto& edge : edges_) {
        Relax(dist, edge);
      }
    }

    return dist;
  }
};

int main() {
  size_t n = 0;
  size_t m = 0;
  std::cin >> n >> m;

  WeightedGraph graph(n, m);

  auto dist = std::move(graph.GetDistances(0));

  for (size_t i = 0; i < dist.size(); ++i) {
    std::cout << dist[i] << " ";
  }
  std::cout << "\n";

  return 0;
}