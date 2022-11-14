// Вам дан неориентированный граф. Найдите кратчайший путь от вершины a до вершины b.

#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

class Graph {
 private:
  struct Node {
    std::unordered_set<int> transitions_;
    int from_;
    bool passed_;

    Node() : from_(-1), passed_(false) {
    }
  };

  std::vector<Node> vertexes_;

 public:
  Graph(const int& n, const int& m) {
    vertexes_.resize(n);

    int first = 0;
    int second = 0;

    for (int i = 0; i < m; ++i) {
      std::cin >> first >> second;
      --first;
      --second;

      vertexes_[first].transitions_.insert(second);
      vertexes_[second].transitions_.insert(first);
    }
  }

  void BFS(const int& a, const int& b) {
    if (a == b) {
      std::cout << 0 << "\n" << a + 1 << "\n";

      return;
    }

    vertexes_[a].passed_ = true;

    std::queue<int> queue;

    std::vector<int> way_to;
    way_to.resize(vertexes_.size());

    for (auto ptr = vertexes_[a].transitions_.begin(); ptr != vertexes_[a].transitions_.end(); ++ptr) {
      queue.push(*ptr);
      vertexes_[*ptr].from_ = a;
      vertexes_[*ptr].passed_ = true;
      way_to[*ptr] = 1;
    }

    int node = 0;
    bool is_find = false;

    while (!queue.empty()) {
      node = queue.front();

      if (node == b) {
        is_find = true;

        break;
      }

      for (auto ptr = vertexes_[node].transitions_.begin(); ptr != vertexes_[node].transitions_.end(); ++ptr) {
        if (!vertexes_[*ptr].passed_) {
          queue.push(*ptr);
          vertexes_[*ptr].from_ = node;
          vertexes_[*ptr].passed_ = true;
          way_to[*ptr] = way_to[node] + 1;
        }
      }

      queue.pop();
    }

    if (is_find) {
      std::cout << way_to[node] << "\n";

      std::vector<int> road;
      while (node != a) {
        road.emplace_back(node);
        node = vertexes_[node].from_;
      }

      road.emplace_back(node);

      std::cout << road[road.size() - 1] + 1;

      for (auto i = static_cast<int>(road.size() - 2); i >= 0; --i) {
        std::cout << " " << road[i] + 1;
      }
      std::cout << "\n";

    } else {
      std::cout << -1 << "\n";
    }
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  int a = 0;
  int b = 0;
  std::cin >> a >> b;
  --a;
  --b;

  Graph graph(n, m);

  graph.BFS(a, b);

  return 0;
}