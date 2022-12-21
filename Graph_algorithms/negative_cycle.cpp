// Дан ориентированный граф. Определить, есть ли в нем цикл отрицательного веса, и если да,
// то вывести его.

// В первой строке содержится число N (1 ≤ N ≤ 100) — количество вершин графа. В следующих N
// строках находится по N чисел — матрица смежности графа. Веса ребер по модулю меньше 100000.
// Если ребра нет, соответствующее значение равно 100000.

// В первой строке выведите YES, если цикл существует, или NO, в противном случае.

// При наличии цикла выведите во второй строке количество вершин в нем (считая одинаковые —
// первую и последнюю), а в третьей строке — вершины, входящие в этот цикл, в порядке обхода.
// Если циклов несколько, то выведите любой из них.

#include <iostream>
#include <map>
#include <vector>

class WeightedGraph {
 private:
  struct Node {
    std::vector<std::pair<int, int> > transitions_;
  };

  std::vector<Node> vertexes_;
  int vertex_count_;
  int edges_count_;

  bool Relax(std::vector<int>& dist, const int& begin, const std::pair<int, int>& edge) {
    if ((dist[begin] != 100000) && (dist[edge.second] > dist[begin] + edge.first)) {
      dist[edge.second] = dist[begin] + edge.first;

      return true;
    }

    return false;
  }

 public:
  explicit WeightedGraph(const int& n) : vertex_count_(n) {
    vertexes_.resize(vertex_count_);

    int weight = 0;

    for (int i = 0; i < vertex_count_; ++i) {
      vertexes_[i].transitions_.reserve(vertex_count_);

      for (int j = 0; j < vertex_count_; ++j) {
        std::cin >> weight;

        if (weight != 100000) {
          vertexes_[i].transitions_.emplace_back(weight, j);
        }
      }
    }
  }

  // using Dijkstra and Bellman-Ford algorithms
  void GetNegativeCycle() {
    std::vector<bool> passed(vertex_count_, false);
    std::vector<int> dist(vertex_count_, 100000);
    std::vector<int> prev(vertex_count_, -1);

    int id_min = 0;
    int weight = 0;

    for (int i = 0; i < vertex_count_; ++i) {
      if (!passed[i]) {
        passed[i] = true;
        dist[i] = 0;

        for (auto& edge : vertexes_[i].transitions_) {
          if (!passed[edge.second]) {
            dist[edge.second] = edge.first;
            prev[edge.second] = i;
          }
        }

        std::multimap<int, int, std::less<int> > map;
        for (int i = 0; i < vertex_count_; ++i) {
          if (!passed[i]) {
            map.emplace(dist[i], i);
          }
        }

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
              prev[edge.second] = id_min;

              map.emplace(dist[edge.second], edge.second);
            }
          }
        }
      }
    }

    int beg = -1;
    int end = 0;

    for (int v = 0; v < vertex_count_; ++v) {
      for (auto& edge : vertexes_[v].transitions_) {
        if (Relax(dist, v, edge)) {
          beg = v;
          end = edge.second;

          break;
        }
      }

      if (beg != -1) {
        break;
      }
    }

    if (beg != -1) {
      std::cout << "YES\n";

      std::vector<int> cycle;
      cycle.reserve(vertex_count_ + 1);

      cycle.emplace_back(end + 1);
      cycle.emplace_back(beg + 1);

      while (beg != end) {
        beg = prev[beg];

        cycle.emplace_back(beg + 1);
      }

      std::cout << cycle.size() << "\n";

      for (int i = static_cast<int>(cycle.size()) - 1; i >= 0; --i) {
        std::cout << cycle[i] << " ";
      }
      std::cout << "\n";
    } else {
      std::cout << "NO\n";
    }
  }
};

int main() {
  int n = 0;
  std::cin >> n;

  WeightedGraph graph(n);

  graph.GetNegativeCycle();

  return 0;
}