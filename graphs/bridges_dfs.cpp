// Дан неориентированный граф. Требуется найти все мосты в нем.

#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

class Graph {
 private:
  enum Color { White, Gray, Black };

  struct Node {
    std::set<std::pair<int, int> > transitions_;
    Color color_;
    int time_in_;
    int time_up_;

    Node() : color_(White), time_in_(-1), time_up_(-1) {
    }
  };

  std::vector<Color> colors_;
  std::vector<Node> vertexes_;
  int size_;
  int time_;

  void DfsVisit(const int& node, int from, std::vector<bool>& bridges, int& count) {
    colors_[node] = Gray;
    vertexes_[node].time_in_ = time_;
    vertexes_[node].time_up_ = time_++;

    for (auto& neighbor : vertexes_[node].transitions_) { 
      if ((colors_[neighbor.first] == Gray) && (neighbor.first != node) && (neighbor.first != from)) {
        vertexes_[node].time_up_ = std::min(vertexes_[node].time_up_, vertexes_[neighbor.first].time_in_);
      } else if (colors_[neighbor.first] == White) {
        DfsVisit(neighbor.first, node, bridges, count);

        vertexes_[node].time_up_ = std::min(vertexes_[node].time_up_, vertexes_[neighbor.first].time_up_);

        if (vertexes_[node].time_in_ < vertexes_[neighbor.first].time_up_) {
          int edge_count = 0;

          for (auto& pair : vertexes_[node].transitions_) {
            if (pair.first == neighbor.first) {
              ++edge_count;
            }
          }
          if (edge_count != 2) {
            bridges[neighbor.second] = true;

            ++count;
          }
        }
      }
    }

    colors_[node] = Black;
  }

 public:
  Graph(const int& n, const int& m) : size_(n), time_(0) {
    vertexes_.resize(n);
    colors_.resize(n);

    int first = 0;
    int second = 0;

    for (int i = 0; i < m; ++i) {
      std::cin >> first >> second;
      --first;
      --second;

      vertexes_[first].transitions_.emplace(std::pair<int, int>(second, i));
      vertexes_[second].transitions_.emplace(std::pair<int, int>(first, i));
    }
  }

  std::pair<std::vector<bool>, int> GetBridges(const int& m) {
    std::vector<bool> bridges;
    bridges.resize(m, false);
    int count = 0;

    for (int node = 0; node < size_; ++node) {
      if (colors_[node] == White) {
        DfsVisit(node, node, bridges, count);
      }
    }

    return {bridges, count};
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  Graph graph(n, m);

  auto pair = std::move(graph.GetBridges(m));

  std::cout << pair.second << "\n";
  for (size_t i = 0; i < pair.first.size(); ++i) {
    if (pair.first[i]) {
      std::cout << i + 1 << "\n";
    }
  }

  return 0;
}