// Дан ориентированный взвешенный граф. Найдите кратчайшее расстояние от одной заданной
// вершины до другой.

#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>

class DirectedGraph {
 private:
  struct Node {
    std::unordered_set<int> transitions_;
    bool is_passed_;
    int length_;

    Node() : is_passed_(false), length_(0) {
    }
  };

  std::vector<Node> vertexes_;
  int start_;
  int finish_;

 public:
  DirectedGraph(const int& n, const int& m, const int& start, const int& finish) {
    start_ = start;
    finish_ = finish;
    --start_;
    --finish_;

    vertexes_.resize(n);

    int from = 0;
    int to = 0;
    int weight = 0;

    int runner = 0;

    for (int i = 0; i < m; ++i) {
      std::cin >> from >> to >> weight;
      --from;
      --to;

      if (weight > 1) {
        for (int j = 0; j < weight - 1; ++j) {
          vertexes_.emplace_back(Node());
        }

        runner = static_cast<int>(vertexes_.size() - weight + 1);

        vertexes_[from].transitions_.insert(runner);
        while (runner != static_cast<int>(vertexes_.size() - 1)) {
          vertexes_[runner].transitions_.insert(runner + 1);
          ++runner;
        }
        vertexes_[runner].transitions_.insert(to);
      } else {
        vertexes_[from].transitions_.insert(to);
      }
    }
  }

  void BfsSearch() {
    if (start_ == finish_) {
      std::cout << 0 << "\n";
    } else {
      int runner = start_;

      std::queue<int> queue;

      vertexes_[runner].is_passed_ = true;

      for (auto iter = vertexes_[runner].transitions_.begin(); iter != vertexes_[runner].transitions_.end(); ++iter) {
        vertexes_[*iter].length_ = vertexes_[runner].length_ + 1;
        vertexes_[*iter].is_passed_ = true;
        queue.push(*iter);
      }

      int node = 0;

      bool is_find = false;

      while (!queue.empty()) {
        node = queue.front();
        queue.pop();

        if (node == finish_) {
          is_find = true;

          break;
        }

        for (auto iter = vertexes_[node].transitions_.begin(); iter != vertexes_[node].transitions_.end(); ++iter) {
          if (!vertexes_[*iter].is_passed_) {
            vertexes_[*iter].is_passed_ = true;
            vertexes_[*iter].length_ = vertexes_[node].length_ + 1;

            queue.push(*iter);
          }
        }
      }

      if (!is_find) {
        std::cout << -1 << "\n";
      } else {
        std::cout << vertexes_[finish_].length_ << "\n";
      }
    }
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  int start = 0;
  int finish = 0;
  std::cin >> start >> finish;

  DirectedGraph graph(n, m, start, finish);

  graph.BfsSearch();

  return 0;
}