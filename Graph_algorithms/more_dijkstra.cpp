// Дан ориентированный граф, рёбрам которого приписаны некоторые неотрицательные веса (длины).
// Найти длину кратчайшего пути из вершины s в вершину t.

// В первой строке заданы три числа: число вершин в графе N (N ≤ 2 ⋅ 103), номера вершин s и
// t. Далее идёт матрица смежности графа, то есть N строк, в каждой из которых записано N
// чисел. j-е число в i-й строке матрицы смежности задает длину ребра, ведущего из i-й вершину
// в j-ю. Длины могут принимать любые значения от 0 до 106, число -1 означает отсутствие
// соответствующего ребра. Гарантируется, что на главной диагонали матрицы стоят нули.

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
  size_t finish_;

 public:
  explicit WeightedGraph(const size_t& n) : size_(n) {
    std::cin >> start_ >> finish_;
    --start_;
    --finish_;

    vertexes_.resize(size_);

    int weight = 0;

    for (size_t i = 0; i < size_; ++i) {
      for (size_t j = 0; j < size_; ++j) {
        std::cin >> weight;

        if ((i != j) && (weight != -1)) {
          vertexes_[i].transitions_.emplace_back(static_cast<size_t>(weight), j);
        }
      }
    }
  }

  // using Dijkstra algorithm
  ssize_t GetDistance() {
    if (start_ == finish_) {
      return 0;
    }

    std::unordered_set<size_t> passed;
    passed.emplace(start_);

    std::vector<size_t> dist(size_, SIZE_MAX);
    dist[start_] = 0;

    for (auto& edge : vertexes_[start_].transitions_) {
      dist[edge.second] = edge.first;
    }

    size_t id_min = 0;
    size_t count_min = SIZE_MAX;

    while (passed.size() != size_) {
      count_min = SIZE_MAX;

      for (size_t i = 0; i < size_; ++i) {
        if ((passed.find(i) == passed.end()) && (dist[i] <= count_min)) {
          id_min = i;
          count_min = dist[i];
        }
      }

      passed.emplace(id_min);

      if (dist[id_min] == SIZE_MAX) {
        break;
      }

      for (auto& edge : vertexes_[id_min].transitions_) {
        if (passed.find(edge.second) == passed.end()) {
          if (dist[edge.second] > dist[id_min] + edge.first) {
            dist[edge.second] = dist[id_min] + edge.first;
          }
        }
      }
    }

    if (dist[finish_] == SIZE_MAX) {
      return -1;
    }

    return dist[finish_];
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t n = 0;
  std::cin >> n;

  WeightedGraph graph(n);

  std::cout << graph.GetDistance() << "\n";

  return 0;
}