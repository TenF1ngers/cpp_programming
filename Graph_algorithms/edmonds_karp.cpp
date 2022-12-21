// Задан ориентированный граф, каждое ребро которого обладает целочисленной пропускной
// способностью. Найдите максимальный поток из вершины с номером 1 в вершину с номером n.

// В этой задаче необходимо реализовать алгоритм Эдмондса-Карпа.

// Первая строка входного файла содержит n и m — количество вершин и количество ребер графа
// (2 ≤ n ≤ 500, 1 ≤ m ≤ 10000). Следующие m строк содержат по три числа: номера вершин,
// которые соединяет соответствующее ребро графа и его пропускную способность. Пропускные
// способности не превосходят 109.

// В выходной файл выведите одно число - величину максимального потока из вершины с номером
// 1 в вершину с номером n.

#include <iostream>
#include <map>
#include <queue>
#include <vector>

class System {
 private:
  enum Color { White, Gray, Black };

  std::vector<std::map<int64_t, int64_t, std::greater<int64_t> > > vertexes_;
  int64_t size_;

  bool BfsWalk(const int64_t& start, int64_t& min_flow, const int64_t& finish) {
    std::vector<Color> colors(size_, White);
    colors[start] = Gray;

    std::queue<int64_t> queue;
    queue.push(start);

    std::vector<int64_t> prev(size_, -1);
    std::vector<int64_t> flows(size_, -1);
    flows[start] = 100000000000;

    int64_t element = 0;

    while (!queue.empty()) {
      element = queue.front();
      queue.pop();

      for (auto& edge : vertexes_[element]) {
        if ((colors[edge.first] == White) && (vertexes_[element][edge.first] > 0)) {
          colors[edge.first] = Gray;

          prev[edge.first] = element;

          if (edge.second < flows[element]) {
            flows[edge.first] = edge.second;
          } else {
            flows[edge.first] = flows[element];
          }

          if (colors[finish] == Gray) {
            break;
          }

          queue.push(edge.first);
        }
      }

      if (colors[finish] == Gray) {
        break;
      }
    }

    if (colors[finish] != Gray) {
      return false;
    }

    min_flow = flows[finish];

    auto runner = prev[finish];
    auto next = finish;

    while (runner != -1) {
      vertexes_[runner][next] -= min_flow;
      vertexes_[next][runner] += min_flow;

      next = runner;
      runner = prev[runner];
    }

    return true;
  }

 public:
  System(const int64_t& n, const int64_t& m) : size_(n) {
    vertexes_.resize(size_);

    int64_t begin = 0;
    int64_t end = 0;
    int64_t throughput = 0;

    for (int64_t i = 0; i < m; ++i) {
      std::cin >> begin >> end >> throughput;
      --begin;
      --end;

      vertexes_[begin][end] = throughput;

      if (vertexes_[end].find(begin) == vertexes_[end].end()) {
        vertexes_[end][begin] = 0;
      }
    }
  }

  void GetMaxFlow(const int64_t& start, const int64_t& finish) {
    int64_t max = 0;
    int64_t min_flow = 0;

    while (BfsWalk(start, min_flow, finish)) {
      max += min_flow;
    }

    std::cout << max << "\n";
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;

  System system(n, m);

  system.GetMaxFlow(0, n - 1);

  return 0;
}