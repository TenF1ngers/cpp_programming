// Дан ориентированный невзвешенный граф. Необходимо его топологически отсортировать.

#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>

class DirectedGraph {
 private:
  enum Color { White, Gray, Black };

  struct Node {
    std::unordered_set<int> transitions_;
    Color color_;

    Node() : color_(White) {
    }
  };

  std::vector<Node> vertexes_;

  void NodeProcess(const int& start, std::stack<int>& stack, bool& cyclical) {
    vertexes_[start].color_ = Gray;

    for (auto& neighbor : vertexes_[start].transitions_) {
      if (vertexes_[neighbor].color_ == Gray) {
        cyclical = true;

        break;
      }

      if (vertexes_[neighbor].color_ == White) {
        NodeProcess(neighbor, stack, cyclical);

        if (cyclical) {
          break;
        }
      }
    }

    if (cyclical) {
      return;
    }

    vertexes_[start].color_ = Black;
    stack.push(start);
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

  // using DFS-idiom
  std::stack<int> TopologicalSort() {
    std::stack<int> stack;
    bool cyclical = false;

    for (size_t i = 0; i < vertexes_.size(); ++i) {
      if (vertexes_[i].color_ == White) {
        NodeProcess(i, stack, cyclical);

        if (cyclical) {
          break;
        }
      }
    }

    if (cyclical) {
      std::cout << -1 << "\n";

      return std::stack<int>();
    }

    return stack;
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  DirectedGraph graph(n, m);

  auto stack = std::move(graph.TopologicalSort());

  while (!stack.empty()) {
    std::cout << stack.top() + 1 << " ";

    stack.pop();
  }
  std::cout << "\n";

  return 0;
}