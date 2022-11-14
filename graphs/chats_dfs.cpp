// Во входном файле записано два числа N — число первокурсников и M — число известных
// вам пар первокурсников, сидящих в одном чате (1 ≤ N ≤ 100000, 0 ≤ M ≤ 100000).
// В следующих M строках записаны по два числа i и j (1 ≤ i, j ≤ N), которые означают,
// что первокурсники с номерами i и j в одном чате.

#include <iostream>
#include <unordered_set>
#include <vector>

class Graph {
 private:
  enum Color { White, Gray, Black };

  struct Node {
    std::unordered_set<int> transitions_;
    Color color_;
    int group_size_;

    Node() : color_(White), group_size_(0) {
    }
  };

  std::vector<Node> vertexes_;
  std::unordered_set<int> key_nodes_;

  void PrintGroups() {
    std::cout << key_nodes_.size() << "\n";

    for (auto& node : vertexes_) {
      node.color_ = White;
    }

    for (auto& node : key_nodes_) {
      std::cout << vertexes_[node].group_size_ << "\n";

      PrintDfs(node);
      std::cout << "\n";
    }
  }

  void PrintDfs(int node) {
    std::cout << node + 1 << " ";

    vertexes_[node].color_ = Gray;

    for (auto neighbor = vertexes_[node].transitions_.begin(); neighbor != vertexes_[node].transitions_.end();
         ++neighbor) {
      if (vertexes_[*neighbor].color_ == White) {
        PrintDfs(*neighbor);
      }
    }

    vertexes_[node].color_ = Black;
  }

 public:
  explicit Graph(const int& n, const int& m) {
    vertexes_.resize(n);

    int first = 0;
    int second = 0;

    for (int i = 0; i < m; ++i) {
      std::cin >> first >> second;
      --first;
      --second;

      vertexes_[first].transitions_.emplace(second);
      vertexes_[second].transitions_.emplace(first);
    }
  }

  void WeaklyComponents() {
    int size = 0;

    for (int i = 0; i < static_cast<int>(vertexes_.size()); ++i) {
      if (vertexes_[i].color_ == White) {
        size = 0;
        NodeProcessing(i, size);

        vertexes_[i].group_size_ = size;
        key_nodes_.emplace(i);
      }
    }

    PrintGroups();
  }

  // using DFS-idiom
  void NodeProcessing(int node, int& size) {
    ++size;

    vertexes_[node].color_ = Gray;

    for (auto neighbor = vertexes_[node].transitions_.begin(); neighbor != vertexes_[node].transitions_.end();
         ++neighbor) {
      if (vertexes_[*neighbor].color_ == White) {
        NodeProcessing(*neighbor, size);
      }
    }

    vertexes_[node].color_ = Black;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  Graph graph(n, m);

  graph.WeaklyComponents();

  return 0;
}