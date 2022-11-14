// В первой строке находятся два числа N и M — количество студентов и количество пар
// студентов, обменивающихся записками (1 ≤ N ≤ 100, 0 ≤ M ≤ N ⋅ (N - 1) / 2). Далее
// в M строках расположены описания пар студентов: два числа, соответствующие номерам
// студентов, обменивающихся записками (нумерация студентов идёт с 1). Каждая пара студентов
// перечислена не более одного раза.

#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

class Graph {
 private:
  enum category { allowing_write, cheater, neutral };

  struct Node {
    std::unordered_set<int> transitions_;
    int from_;
    bool passed_;
    category cat_;

    Node() : from_(-1), passed_(false), cat_(neutral) {
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

  void BFS() {
    int start = 0;
    bool achievable = true;

    while (start != static_cast<int>(vertexes_.size())) {
      while ((start < static_cast<int>(vertexes_.size())) && (vertexes_[start].passed_)) {
        ++start;
      }

      if (start != static_cast<int>(vertexes_.size())) {
        vertexes_[start].passed_ = true;
        vertexes_[start].cat_ = allowing_write;

        std::queue<int> queue;

        for (auto ptr = vertexes_[start].transitions_.begin(); ptr != vertexes_[start].transitions_.end(); ++ptr) {
          queue.push(*ptr);
          vertexes_[*ptr].from_ = start;
          vertexes_[*ptr].passed_ = true;
          vertexes_[*ptr].cat_ = cheater;
        }

        int node = 0;

        while (!queue.empty()) {
          node = queue.front();

          for (auto ptr = vertexes_[node].transitions_.begin(); ptr != vertexes_[node].transitions_.end(); ++ptr) {
            if (!vertexes_[*ptr].passed_) {
              queue.push(*ptr);
              vertexes_[*ptr].from_ = node;
              vertexes_[*ptr].passed_ = true;

              if (vertexes_[node].cat_ == allowing_write) {
                vertexes_[*ptr].cat_ = cheater;
              } else {
                vertexes_[*ptr].cat_ = allowing_write;
              }
            } else {
              if (vertexes_[node].cat_ == vertexes_[*ptr].cat_) {
                achievable = false;

                break;
              }
            }
          }

          if (!achievable) {
            break;
          }

          queue.pop();
        }
      }
    }

    if (!achievable) {
      std::cout << "NO\n";
    } else {
      std::cout << "YES\n";
    }
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  Graph graph(n, m);

  graph.BFS();

  return 0;
}