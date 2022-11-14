// На шахматной доске N × N в клетке (x1, y1) стоит голодный шахматный конь. Он хочет
// попасть в клетку (x2, y2), где растет вкусная шахматная трава. Какое наименьшее
// количество ходов он должен для этого сделать?

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
    int count_;

    Node() : from_(-1), passed_(false), count_(0) {
    }
  };

  std::vector<Node> vertexes_;

  int GetPosition(const int& n, const int& x, const int& y) {
    return (n + 4) * x + y;
  }

  int GetX(const int& n, const int& node) {
    return node / (n + 4);
  }

  int GetY(const int& n, const int& node) {
    return node % (n + 4);
  }

  void PrintWay(int n, int node) {
    std::cout << vertexes_[node].count_ << "\n";

    std::vector<int> way;
    way.reserve(vertexes_[node].count_ + 1);

    while (vertexes_[node].count_ != 0) {
      way.emplace_back(node);

      node = vertexes_[node].from_;
    }
    way.emplace_back(node);

    for (ssize_t i = way.size() - 1; i >= 0; --i) {
      std::cout << GetX(n, way[i]) - 1 << " " << GetY(n, way[i]) - 1 << "\n";
    }
  }

 public:
  explicit Graph(const int& n) {
    vertexes_.resize((n + 4) * (n + 4));

    int cur_pos = 0;
    for (int i = 2; i < n + 2; ++i) {
      for (int j = 2; j < n + 2; ++j) {
        cur_pos = GetPosition(n, i, j);

        vertexes_[cur_pos].transitions_.insert(GetPosition(n, i - 2, j - 1));
        vertexes_[cur_pos].transitions_.insert(GetPosition(n, i - 2, j + 1));
        vertexes_[cur_pos].transitions_.insert(GetPosition(n, i - 1, j - 2));
        vertexes_[cur_pos].transitions_.insert(GetPosition(n, i - 1, j + 2));
        vertexes_[cur_pos].transitions_.insert(GetPosition(n, i + 1, j - 2));
        vertexes_[cur_pos].transitions_.insert(GetPosition(n, i + 1, j + 2));
        vertexes_[cur_pos].transitions_.insert(GetPosition(n, i + 2, j - 1));
        vertexes_[cur_pos].transitions_.insert(GetPosition(n, i + 2, j + 1));

        vertexes_[GetPosition(n, i - 2, j - 1)].transitions_.insert(cur_pos);
        vertexes_[GetPosition(n, i - 2, j + 1)].transitions_.insert(cur_pos);
        vertexes_[GetPosition(n, i - 1, j - 2)].transitions_.insert(cur_pos);
        vertexes_[GetPosition(n, i - 1, j + 2)].transitions_.insert(cur_pos);
        vertexes_[GetPosition(n, i + 1, j - 2)].transitions_.insert(cur_pos);
        vertexes_[GetPosition(n, i + 1, j + 2)].transitions_.insert(cur_pos);
        vertexes_[GetPosition(n, i + 2, j - 1)].transitions_.insert(cur_pos);
        vertexes_[GetPosition(n, i + 2, j + 1)].transitions_.insert(cur_pos);
      }
    }
  }

  void BFS(const int& n, const int& x1, const int& y1, const int& x2, const int& y2) {
    auto start = GetPosition(n, x1, y1);

    vertexes_[start].passed_ = true;

    std::queue<int> queue;

    int node = 0;
    int x = 0;
    int y = 0;

    for (auto ptr = vertexes_[start].transitions_.begin(); ptr != vertexes_[start].transitions_.end(); ++ptr) {
      x = GetX(n, *ptr);
      y = GetY(n, *ptr);

      if ((x >= 0) && (x <= n + 1) && (y >= 0) && (y <= n + 1)) {
        queue.push(*ptr);
        vertexes_[*ptr].from_ = start;
        vertexes_[*ptr].passed_ = true;
        vertexes_[*ptr].count_ = 1;
      }
    }

    while (!queue.empty()) {
      node = queue.front();

      x = GetX(n, node);
      y = GetY(n, node);

      if ((x == x2) && (y == y2)) {
        break;
      }

      for (auto ptr = vertexes_[node].transitions_.begin(); ptr != vertexes_[node].transitions_.end(); ++ptr) {
        if (!vertexes_[*ptr].passed_) {
          x = GetX(n, *ptr);
          y = GetY(n, *ptr);

          if ((x >= 0) && (x <= n + 1) && (y >= 0) && (y <= n + 1)) {
            queue.push(*ptr);

            vertexes_[*ptr].from_ = node;
            vertexes_[*ptr].passed_ = true;
            vertexes_[*ptr].count_ = vertexes_[node].count_ + 1;
          }
        }
      }

      queue.pop();
    }

    PrintWay(n, node);
  }
};

int main() {
  int n = 0;
  int x1 = 0;
  int y1 = 0;
  int x2 = 0;
  int y2 = 0;

  std::cin >> n >> x1 >> y1 >> x2 >> y2;
  x1 += 1;
  y1 += 1;
  x2 += 1;
  y2 += 1;

  if ((x1 == x2) && (y1 == y2)) {
    std::cout << 0 << "\n";

    std::cout << x1 - 1 << " " << y1 - 1 << "\n";
  } else {
    Graph graph(n);

    graph.BFS(n, x1, y1, x2, y2);
  }

  return 0;
}