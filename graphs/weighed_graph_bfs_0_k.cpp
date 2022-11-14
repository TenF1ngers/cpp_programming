// Дан ориентированный взвешенный граф. Найдите кратчайшее расстояние от одной заданной
// вершины до другой.

#include <deque>
#include <iostream>
#include <vector>

class WeighedGraph {
 private:
  enum Color { White, Gray, Black };
  const int k_ = 30;

  struct Node {
    std::vector<std::pair<int, int> > transitions_;
    int distance_;

    Node() : distance_(1000000000) {
    }
  };

  std::vector<Node> vertexes_;
  std::vector<Color> colors_;
  int size_;

  std::vector<std::deque<int> > deques_;

 public:
  WeighedGraph(const int& n, const int& m) : size_(n) {
    vertexes_.resize(n);
    colors_.resize(n, White);
    deques_.resize(k_ + 1);

    int first = 0;
    int second = 0;
    int weight = 0;

    for (int i = 0; i < m; ++i) {
      std::cin >> first >> second >> weight;
      --first;
      --second;

      vertexes_[first].transitions_.emplace_back(std::pair<int, int>(second, weight));
    }
  }

  // using BFS-idiom (0-k)
  int SearchDistance(const int& start, const int& finish) {
    vertexes_[start].distance_ = 0;
    deques_[0].push_back(start);

    int node = 0;

    for (int i = 0; i < k_ + 1; ++i) {
      while (!deques_[i].empty()) {
        node = deques_[i].front();
        deques_[i].pop_front();

        if (colors_[node] == Black) {
          continue;
        }
        colors_[node] = Black;

        for (auto& neighbor : vertexes_[node].transitions_) {
          if (neighbor.second == 0) {
            vertexes_[neighbor.first].distance_ = vertexes_[node].distance_;

            deques_[i].push_front(neighbor.first);
          } else {
            if (vertexes_[node].distance_ + neighbor.second < vertexes_[neighbor.first].distance_) {
              vertexes_[neighbor.first].distance_ = vertexes_[node].distance_ + neighbor.second;

              deques_[vertexes_[neighbor.first].distance_ % (k_ + 1)].push_back(neighbor.first);
            }
          }
        }
      }
    }

    if (vertexes_[finish].distance_ == 1000000000) {
      return -1;
    }

    return vertexes_[finish].distance_;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  int start = 0;
  int finish = 0;
  std::cin >> start >> finish;
  --start;
  --finish;

  WeighedGraph w_graph(n, m);

  std::cout << w_graph.SearchDistance(start, finish) << "\n";

  return 0;
}