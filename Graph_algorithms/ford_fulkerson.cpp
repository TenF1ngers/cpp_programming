// Задан ориентированный граф, каждое ребро которого обладает целочисленной пропускной
// способностью. Найдите максимальный поток из вершины с номером 1 в вершину с номером n.

// В этой задаче необходимо реализовать алгоритм Форда-Фалкерсона.

// Первая строка входного файла содержит n и m — количество вершин и количество ребер графа
// (2 ≤ n ≤ 100, 1 ≤ m ≤ 1000). Следующие m строк содержат по три числа: номера вершин,
// которые соединяет соответствующее ребро графа и его пропускную способность. Пропускные
// способности не превосходят 105.

// В выходной файл выведите одно число — величину максимального потока из вершины с номером
// 1 в вершину с номером n.

#include <iostream>
#include <map>
#include <vector>

class System {
 private:
  enum Color { White, Gray, Black };

  std::vector<std::map<int, int, std::greater<int> > > vertexes_;
  std::vector<Color> colors_;
  int size_;

  bool DfsVisit(const int& current, int& min_flow, const int& finish, std::vector<int>& key_v) {
    colors_[current] = Gray;

    for (auto& edge : vertexes_[current]) {
      if ((colors_[edge.first] == White) && (edge.second > 0)) {
        if (edge.second < min_flow) {
          min_flow = edge.second;
        }

        if (edge.first == finish) {
          edge.second -= min_flow;
          vertexes_[edge.first][current] += min_flow;

          colors_[current] = White;

          return true;
        }

        if (DfsVisit(edge.first, min_flow, finish, key_v)) {
          edge.second -= min_flow;
          vertexes_[edge.first][current] += min_flow;

          colors_[current] = White;

          return true;
        }
      }
    }

    colors_[current] = Black;
    key_v.emplace_back(current);

    return false;
  }

 public:
  System(const int& n, const int& m) : size_(n) {
    vertexes_.resize(size_);
    colors_.resize(size_, White);

    int begin = 0;
    int end = 0;
    int throughput = 0;

    for (int i = 0; i < m; ++i) {
      std::cin >> begin >> end >> throughput;
      --begin;
      --end;

      vertexes_[begin][end] = throughput;

      if (vertexes_[end].find(begin) == vertexes_[end].end()) {
        vertexes_[end][begin] = 0;
      }
    }
  }

  // using Ford-Fulkerson algorithm
  void GetMaxFlow(const int& start, const int& finish) {
    int max = 0;
    int min_flow = 100000000;

    std::vector<int> key_v;

    while (DfsVisit(start, min_flow, finish, key_v)) {
      max += min_flow;

      for (size_t i = 0; i < key_v.size(); ++i) {
        colors_[key_v[i]] = White;
      }
      key_v.resize(0);

      min_flow = 100000000;
    }

    std::cout << max << "\n";
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  System system(n, m);

  system.GetMaxFlow(0, n - 1);

  return 0;
}