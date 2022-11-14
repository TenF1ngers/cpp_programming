// traffic-rules

#include <deque>
#include <iostream>
#include <unordered_set>
#include <vector>

class DirectedGraph {
 private:
  struct Node {
    std::unordered_set<int> outcome_;
    std::unordered_set<int> income_;
    int dist_;

    Node() : dist_(10000) {
    }
  };

  std::vector<Node> vertexes_;

  // using BFS-idiom
  int Search(const int start, const int finish) {
    std::deque<int> deque;

    vertexes_[start].dist_ = 0;

    for (auto neighbor = vertexes_[start].outcome_.begin(); neighbor != vertexes_[start].outcome_.end(); ++neighbor) {
      deque.push_front(*neighbor);
      vertexes_[*neighbor].dist_ = 0;
    }

    for (auto neighbor = vertexes_[start].income_.begin(); neighbor != vertexes_[start].income_.end(); ++neighbor) {
      if (vertexes_[*neighbor].dist_ > vertexes_[start].dist_ + 1) {
        deque.push_back(*neighbor);
        vertexes_[*neighbor].dist_ = 1;
      }
    }

    int node = 0;

    while (!deque.empty()) {
      node = deque.front();
      deque.pop_front();

      for (auto neighbor = vertexes_[node].outcome_.begin(); neighbor != vertexes_[node].outcome_.end(); ++neighbor) {
        if (vertexes_[*neighbor].dist_ > vertexes_[node].dist_) {
          vertexes_[*neighbor].dist_ = vertexes_[node].dist_;
          deque.push_front(*neighbor);
        }
      }

      for (auto neighbor = vertexes_[node].income_.begin(); neighbor != vertexes_[node].income_.end(); ++neighbor) {
        if (vertexes_[*neighbor].dist_ > vertexes_[node].dist_ + 1) {
          vertexes_[*neighbor].dist_ = vertexes_[node].dist_ + 1;
          deque.push_back(*neighbor);
        }
      }
    }

    if (vertexes_[finish].dist_ == 10000) {
      return -1;
    }

    return vertexes_[finish].dist_;
  }

 public:
  DirectedGraph(const int &n, const int &m) {
    vertexes_.resize(n);

    int from = 0;
    int to = 0;

    for (int i = 0; i < m; ++i) {
      std::cin >> from >> to;
      --from;
      --to;

      if (from != to) {
        vertexes_[from].outcome_.insert(to);
        vertexes_[to].income_.insert(from);
      }
    }
  }

  void GettingRequests(const int &count, const int &n) {
    int start = 0;
    int finish = 0;
    int min_penalty = 0;

    for (int i = 0; i < count; ++i) {
      for (int j = 0; j < n; ++j) {
        vertexes_[j].dist_ = 10000;
      }

      std::cin >> start >> finish;
      --start;
      --finish;

      min_penalty = this->Search(start, finish);

      std::cout << min_penalty << "\n";
    }
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

  int count = 0;
  std::cin >> count;

  graph.GettingRequests(count, n);

  return 0;
}