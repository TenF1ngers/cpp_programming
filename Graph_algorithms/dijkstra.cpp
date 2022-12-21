// Напишите программу, которая будет находить расстояния в неориентированном взвешенном
// графе с неотрицательными длинами ребер, от указанной вершины до всех остальных. Программа
// должна работать быстро для больших разреженных графов.

// В первой строке входных данных задано число NUM — количество различных запусков алгоритма
// Дейкстры (на разных графах). Далее следуют NUM блоков, каждый из которых имеет следующую
// структуру.

// Первая строка блока содержит два числа N и M, разделенные пробелом — количество вершин и
// количество ребер графа. Далее следуют M строк, каждая из которых содержит по три целых
// числа, разделенные пробелами. Первые два из них в пределах от 0 до N - 1 каждое и обозначают
// концы соответствующего ребра, третье — в пределах от 0 до 20000 и обозначает длину этого
// ребра. Далее, в последней строке блока, записанное единственное число от 0 до N - 1 —
// вершина, расстояния от которой надо искать.

// Количество различных графов в одном тесте NUM не превышает 5. Количество вершин не
// превышает 60000, рёбер — 200000.

#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>

class WeightedGraph {
 private:
  struct Node {
    std::vector<std::pair<size_t, size_t> > transitions_;
  };

  std::vector<Node> vertexes_;
  size_t size_;
  size_t start_;

 public:
  WeightedGraph(const size_t& n, const size_t& m) : size_(n) {
    vertexes_.resize(n);

    size_t begin = 0;
    size_t end = 0;
    size_t weight = 0;

    for (size_t i = 0; i < m; ++i) {
      std::cin >> begin >> end >> weight;

      vertexes_[begin].transitions_.emplace_back(std::pair<size_t, size_t>(weight, end));
      vertexes_[end].transitions_.emplace_back(std::pair<size_t, size_t>(weight, begin));
    }

    std::cin >> start_;
  }

  // using Dijkstra algorithm
  std::vector<size_t> GetDistance() {
    std::vector<bool> passed(size_, false);
    passed[start_] = true;

    std::vector<size_t> dist(size_, 2009000999);
    dist[start_] = 0;

    for (auto& edge : vertexes_[start_].transitions_) {
      dist[edge.second] = edge.first;
    }

    std::multimap<size_t, size_t, std::less<size_t> > map;
    for (size_t i = 0; i < size_; ++i) {
      if (i != start_) {
        map.emplace(dist[i], i);
      }
    }

    size_t id_min = 0;
    size_t weight = 0;

    while (!map.empty()) {
      id_min = map.begin()->second;
      weight = map.begin()->first;
      map.erase(map.begin());

      if (dist[id_min] != weight) {
        continue;
      }

      passed[id_min] = true;

      for (auto& edge : vertexes_[id_min].transitions_) {
        if ((!passed[edge.second]) && (dist[edge.second] > dist[id_min] + edge.first)) {
          dist[edge.second] = dist[id_min] + edge.first;

          map.emplace(dist[edge.second], edge.second);
        }
      }
    }

    return dist;
  }
};

int main() {
  size_t num = 0;
  std::cin >> num;

  size_t n = 0;
  size_t m = 0;

  while (num-- != 0) {
    std::cin >> n >> m;

    WeightedGraph graph(n, m);

    auto dist = std::move(graph.GetDistance());

    for (size_t i = 0; i < n; ++i) {
      std::cout << dist[i] << " ";
    }
    std::cout << "\n";
  }

  return 0;
}