// Нужно по расположению ресторанов Subway узнать для каждого перекрестка минимальное
// расстояние от него до одного из ресторанов. Гарантируется, что хотя бы один ресторан
// имеется в Манхэттене.

#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

class Graph {
 private:
  struct Node {
    int from_;
    int count_;
    bool in_queue_;

    Node() : from_(-1), count_(10000000), in_queue_(false) {
    }
  };

  std::vector<Node> vertexes_;
  std::queue<int> queue_;

  int GetPosition(const int& m, const int& x, const int& y) const {
    return m * x + y;
  }

  int GetX(const int& m, const int& node) const {
    return node / m;
  }

  int GetY(const int& m, const int& node) const {
    return node % m;
  }

  void PrintManhatten(const int& n, const int& m) const {
    int cur_pos = 0;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cur_pos = GetPosition(m, i, j);

        std::cout << vertexes_[cur_pos].count_ << " ";
      }
      std::cout << "\n";
    }
  }

 public:
  explicit Graph(const int& n, const int& m) {
    vertexes_.resize(n * m);

    int cur_pos = 0;
    int value = 0;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cur_pos = GetPosition(m, i, j);

        std::cin >> value;
        if (value == 1) {
          queue_.push(cur_pos);
          vertexes_[cur_pos].in_queue_ = true;
          vertexes_[cur_pos].count_ = 0;
        }
      }
    }
  }

  void BFS(const int& n, const int& m) {
    int node = 0;
    int neighbor = 0;

    int x = 0;
    int y = 0;
    int cur_x = 0;
    int cur_y = 0;

    while (!queue_.empty()) {
      node = queue_.front();
      queue_.pop();

      cur_x = GetX(m, node);
      cur_y = GetY(m, node);

      for (int i = 0; i < 4; ++i) {
        switch (i) {
          case 0: {
            x = cur_x - 1;
            y = cur_y;

            break;
          }
          case 1: {
            x = cur_x;
            y = cur_y + 1;

            break;
          }
          case 2: {
            x = cur_x + 1;
            y = cur_y;

            break;
          }
          case 3: {
            x = cur_x;
            y = cur_y - 1;

            break;
          }
        }

        if ((x >= 0) && (x < n) && (y >= 0) && (y < m)) {
          neighbor = GetPosition(m, x, y);

          if (vertexes_[neighbor].count_ > vertexes_[node].count_ + 1) {
            vertexes_[neighbor].count_ = vertexes_[node].count_ + 1;
            vertexes_[neighbor].from_ = node;

            if (!vertexes_[neighbor].in_queue_) {
              queue_.push(neighbor);
            }
          }
        }
      }
    }

    PrintManhatten(n, m);
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  Graph graph(n, m);

  graph.BFS(n, m);

  return 0;
}