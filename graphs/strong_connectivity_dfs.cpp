// Вам задан ориентированный граф с N вершинами и M ребрами (1 ≤ N ≤ 20000, 1 ≤ M ≤ 200000).
// Найдите компоненты сильной связности заданного графа и топологически отсортируйте
// его конденсацию.

#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>

class DirectedGraph {
 private:
  enum Color { White, Gray, Black };

  std::vector<std::vector<int> > nodes_;
  std::vector<Color> colors_;
  int size_;

  struct Group {
    std::vector<int> combination_;
    std::unordered_set<int> transitions_;
  };

  std::vector<Group> connectivities_;
  int strong_con_count_;

  void StrongNodeProcess(const int& start, std::stack<int>& stack) {
    colors_[start] = Gray;

    for (auto& neighbor : nodes_[start]) {
      if (colors_[neighbor] == White) {
        StrongNodeProcess(neighbor, stack);
      }
    }

    colors_[start] = Black;
    stack.push(start);
  }

  void ClearColors() {
    for (int i = 0; i < size_; ++i) {
      colors_[i] = White;
    }
  }

  void FindStrongNodeProcess(const int& node) {
    nodes_[node].emplace_back(strong_con_count_ - 1);
    colors_[node] = Gray;

    for (size_t to = 0; to < nodes_[node].size() - 1; ++to) {
      if (colors_[nodes_[node][to]] == White) {
        FindStrongNodeProcess(nodes_[node][to]);
      }
    }

    colors_[node] = Black;
  }

  void NodeProcess(const int& start, std::vector<Color>& strong_colors, int& tmp_count) {
    strong_colors[start] = Gray;

    for (auto& neighbor : connectivities_[start].transitions_) {
      if (strong_colors[neighbor] == White) {
        NodeProcess(neighbor, strong_colors, tmp_count);
      }
    }

    strong_colors[start] = Black;

    for (auto& node : connectivities_[start].combination_) {
      nodes_[node][nodes_[node].size() - 1] = tmp_count - 1;
    }
    --tmp_count;
  }

 public:
  DirectedGraph(const int& n, const int& m) : size_(n), strong_con_count_(-1) {
    nodes_.resize(size_, std::vector<int>());
    colors_.resize(size_, White);

    int from = 0;
    int to = 0;

    for (int i = 0; i < m; ++i) {
      std::cin >> from >> to;
      --from;
      --to;

      nodes_[from].emplace_back(to);
    }
  }

  // Strong connectivity sorting using the DFS-idiom
  std::stack<int> StrongTopologicalSort() {
    std::stack<int> stack;

    for (int i = 0; i < size_; ++i) {
      if (colors_[i] == White) {
        StrongNodeProcess(i, stack);
      }
    }

    ClearColors();

    return stack;
  }

  void Reverse() {
    std::vector<std::vector<int> > tmp(size_, std::vector<int>());

    for (int from = 0; from < size_; ++from) {
      for (auto& to : nodes_[from]) {
        tmp[to].emplace_back(from);
      }
    }

    for (int from = 0; from < size_; ++from) {
      nodes_[from] = std::move(tmp[from]);
    }
  }

  void FindStrongConnectivities(std::stack<int>& stack) {
    strong_con_count_ = 0;
    int node = 0;

    while (!stack.empty()) {
      node = stack.top();
      stack.pop();

      if (colors_[node] == White) {
        ++strong_con_count_;

        FindStrongNodeProcess(node);
      }
    }

    connectivities_.resize(strong_con_count_);
    int neighbor = 0;

    for (int from = 0; from < size_; ++from) {
      connectivities_[nodes_[from][nodes_[from].size() - 1]].combination_.emplace_back(from);

      for (size_t to = 0; to < nodes_[from].size() - 1; ++to) {
        neighbor = nodes_[from][to];

        if (nodes_[from][nodes_[from].size() - 1] != nodes_[neighbor][nodes_[neighbor].size() - 1]) {
          connectivities_[nodes_[neighbor][nodes_[neighbor].size() - 1]].transitions_.emplace(
              nodes_[from][nodes_[from].size() - 1]);
        }
      }
    }
  }

  void TopologicalSort() {
    std::vector<Color> strong_colors(strong_con_count_, White);
    int tmp_count = strong_con_count_;

    for (int i = 0; i < strong_con_count_; ++i) {
      if (strong_colors[i] == White) {
        NodeProcess(i, strong_colors, tmp_count);
      }
    }

    std::cout << strong_con_count_ << "\n";
    for (int i = 0; i < size_; ++i) {
      std::cout << nodes_[i][nodes_[i].size() - 1] + 1 << " ";
    }
    std::cout << "\n";
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  DirectedGraph graph(n, m);

  auto stack = std::move(graph.StrongTopologicalSort());

  graph.Reverse();

  graph.FindStrongConnectivities(stack);

  graph.TopologicalSort();

  return 0;
}