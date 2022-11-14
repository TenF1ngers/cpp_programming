// Дан ориентированный невзвешенный граф. Необходимо определить есть ли в нём циклы,
// и если есть, то вывести любой из них.

#include <iostream>
#include <unordered_set>
#include <vector>

class DirectedGraph {
 private:
  enum Color { White, Gray, Black };

  struct Node {
    std::unordered_set<int> transitions_;
    Color color_;
    int parent_;

    Node() : color_(White), parent_(-1) {
    }
  };

  std::vector<Node> vertexes_;

  void PrintCycle(const int& begin, int end) {
    std::vector<int> way;

    while (end != begin) {
      way.emplace_back(end + 1);

      end = vertexes_[end].parent_;
    }

    way.emplace_back(begin + 1);

    for (ssize_t i = way.size() - 1; i >= 0; --i) {
      std::cout << way[i] << " ";
    }
    std::cout << "\n";
  }

 public:
  DirectedGraph(const int& n, const int& m) {
    vertexes_.resize(n);

    int from = 0;
    int to = 0;

    for (int i = 0; i < m; ++i) {
      std::cin >> from >> to;
      --from;
      --to;

      vertexes_[from].transitions_.emplace(to);
    }
  }

  void SearchCycle() {
    bool cyclical = false;

    for (int i = 0; i < static_cast<int>(vertexes_.size()); ++i) {
      if (vertexes_[i].color_ == White) {
        NodeProcessing(i, cyclical);

        if (cyclical) {
          break;
        }
      }
    }

    if (!cyclical) {
      std::cout << "NO\n";
    }
  }

  // using DFS-idiom
  void NodeProcessing(int node, bool& cyclical) {
    vertexes_[node].color_ = Gray;

    for (auto neighbor = vertexes_[node].transitions_.begin(); neighbor != vertexes_[node].transitions_.end();
         ++neighbor) {
      if (cyclical) {
        break;
      }

      if (vertexes_[*neighbor].color_ == Gray) {
        std::cout << "YES\n";

        PrintCycle(*neighbor, node);

        cyclical = true;

        break;
      }

      if (vertexes_[*neighbor].color_ == White) {
        vertexes_[*neighbor].parent_ = node;

        NodeProcessing(*neighbor, cyclical);
      }
    }

    vertexes_[node].color_ = Black;
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  DirectedGraph graph(n, m);

  graph.SearchCycle();

  return 0;
}