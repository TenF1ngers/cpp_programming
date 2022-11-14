// Найдите точки сочленения в неориентированном графе.

#include <iostream>
#include <set>
#include <vector>

class Graph {
 private:
  enum Color { White, Gray, Black };

  struct Node {
    std::vector<int> transitions_;
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

  void DfsVisit(const int& node, bool is_root, std::set<int, std::less<int> >& points) {
    colors_[node] = Gray;
    vertexes_[node].time_in_ = time_;
    vertexes_[node].time_up_ = time_++;

    int count_children = 0;

    for (auto& neighbor : vertexes_[node].transitions_) {
      if (colors_[neighbor] == Gray) {
        vertexes_[node].time_up_ = std::min(vertexes_[node].time_up_, vertexes_[neighbor].time_in_);
      } else if (colors_[neighbor] == White) {
        ++count_children;

        DfsVisit(neighbor, false, points);

        vertexes_[node].time_up_ = std::min(vertexes_[node].time_up_, vertexes_[neighbor].time_up_);

        if (!is_root && (vertexes_[node].time_in_ <= vertexes_[neighbor].time_up_)) {
          points.emplace(node);
        }
      }
    }

    if (is_root && (count_children > 1)) {
      points.emplace(node);
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

      vertexes_[first].transitions_.emplace_back(second);
      vertexes_[second].transitions_.emplace_back(first);
    }
  }

  std::set<int, std::less<int> > GetArticulationPoints() {
    std::set<int, std::less<int> > points;

    for (int node = 0; node < size_; ++node) {
      if (colors_[node] == White) {
        DfsVisit(node, true, points);
      }
    }

    return points;
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  Graph graph(n, m);

  auto points = std::move(graph.GetArticulationPoints());

  std::cout << points.size() << "\n";
  for (auto& point : points) {
    std::cout << point + 1 << "\n";
  }

  return 0;
}