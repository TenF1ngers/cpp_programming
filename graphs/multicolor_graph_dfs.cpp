// Даны N точек, занумерованных числами 1, 2, ... , N . От каждой точки с меньшим
// номером к каждой точке с большим номером ведет стрелка красного или синего цвета.
// Раскраска стрелок называется однотонной, если нет двух таких точек A и B, что от A до
// B можно добраться как только по красным стрелкам, так и только по синим.

// Ваша задача — по заданной раскраске определить, является ли она однотонной.

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class ColorGraph {
 private:
  enum Color { White, Gray, Black };

  std::vector<std::vector<int> > adjacency_;
  std::vector<Color> colors_;
  int size_;

 public:
  explicit ColorGraph(const int& n) : size_(n) {
    adjacency_.resize(n, std::vector<int>(n, 0));
    colors_.resize(n, White);

    std::string edges;

    for (int i = 0; i < n - 1; ++i) {
      std::cin >> edges;

      for (size_t pos = 0; pos < edges.size(); ++pos) {
        if (edges[pos] == 'R') {
          adjacency_[i + 1 + pos][i] = 1;
        } else {
          adjacency_[i][i + 1 + pos] = 1;
        }
      }
    }
  }

  void SearchCycle() {
    bool cyclical = false;

    for (int i = 0; i < size_; ++i) {
      if (colors_[i] == White) {
        NodeProcessing(i, cyclical);

        if (cyclical) {
          break;
        }
      }
    }

    if (!cyclical) {
      std::cout << "YES\n";
    }
  }

  // using DFS-idiom
  void NodeProcessing(int node, bool& cyclical) {
    colors_[node] = Gray;

    for (int neighbor = 0; neighbor < size_; ++neighbor) {
      if (cyclical) {
        break;
      }
      if (adjacency_[node][neighbor] == 1) {
        if (colors_[neighbor] == Gray) {
          std::cout << "NO\n";

          cyclical = true;

          break;
        }

        if (colors_[neighbor] == White) {
          NodeProcessing(neighbor, cyclical);
        }
      }
    }

    colors_[node] = Black;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  std::cin >> n;

  ColorGraph c_graph(n);

  c_graph.SearchCycle();

  return 0;
}