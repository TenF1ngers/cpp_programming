// Выведите единственное число: минимальное количество копилок, которые необходимо
// разбить.

#include <iostream>
#include <unordered_set>
#include <vector>

class Graph {
 private:
  enum Color { White, Gray, Black };

  struct Node {
    std::unordered_set<int> transitions_;
    Color color_;

    Node() : color_(White) {
    }
  };

  std::vector<Node> vertexes_;

 public:
  explicit Graph(const int& n) {
    vertexes_.resize(n);

    int from = 0;

    for (int to = 0; to < n; ++to) {
      std::cin >> from;
      --from;

      vertexes_[from].transitions_.emplace(to);
      vertexes_[to].transitions_.emplace(from);
    }
  }

  void CountWeaklyComponents() {
    int count = 0;

    for (int i = 0; i < static_cast<int>(vertexes_.size()); ++i) {
      if (vertexes_[i].color_ == White) {
        NodeProcessing(i);

        ++count;
      }
    }

    std::cout << count << "\n";
  }

  // using DFS-idiom
  void NodeProcessing(int node) {
    vertexes_[node].color_ = Gray;

    for (auto neighbor = vertexes_[node].transitions_.begin(); neighbor != vertexes_[node].transitions_.end();
         ++neighbor) {
      if (vertexes_[*neighbor].color_ == White) {
        NodeProcessing(*neighbor);
      }
    }

    vertexes_[node].color_ = Black;
  }
};

int main() {
  int n = 0;
  std::cin >> n;

  Graph graph(n);

  graph.CountWeaklyComponents();

  return 0;
}