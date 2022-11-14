// Теперь Мише интересно, какое минимальное количество раз необходимо нажать на кнопку
// пульта, чтобы машинка, начав в клетке старта, остановилась в клетке финиша.

#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>

class Graph {
 private:
  struct Node {
    std::unordered_set<int> transitions_;
    bool is_passed_;
    char symbol_;
    int length_;

    Node() : is_passed_(false), symbol_('/'), length_(0) {
    }
  };

  std::vector<Node> vertexes_;
  int start_;
  int finish_;

  int GetPosition(const int& m, const int& i, const int& j) const {
    return m * i + j;
  }

 public:
  Graph(const int& n, const int& m) {
    vertexes_.resize(n * m);

    char value = 0;
    int cur_pos = 0;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        std::cin >> value;

        cur_pos = GetPosition(m, i, j);

        vertexes_[cur_pos].symbol_ = value;

        if (value == 'S') {
          start_ = cur_pos;
        } else if (value == 'T') {
          finish_ = cur_pos;
        }
      }
    }

    int top_wall = 0;
    int bottom_wall = 0;
    int left_wall = 0;
    int right_wall = 0;

    int x_runner = 0;
    int y_runner = 0;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cur_pos = GetPosition(m, i, j);

        if (vertexes_[cur_pos].symbol_ != '#') {
          x_runner = i;
          y_runner = j;

          while ((x_runner >= 0) && (vertexes_[GetPosition(m, x_runner, y_runner)].symbol_ != '#')) {
            --x_runner;
          }
          top_wall = i - x_runner - 1;

          x_runner = i;

          while ((x_runner < n) && (vertexes_[GetPosition(m, x_runner, y_runner)].symbol_ != '#')) {
            ++x_runner;
          }
          bottom_wall = x_runner - i - 1;

          x_runner = i;

          while ((y_runner >= 0) && (vertexes_[GetPosition(m, x_runner, y_runner)].symbol_ != '#')) {
            --y_runner;
          }
          left_wall = j - y_runner - 1;

          y_runner = j;

          while ((y_runner < m) && (vertexes_[GetPosition(m, x_runner, y_runner)].symbol_ != '#')) {
            ++y_runner;
          }
          right_wall = y_runner - j - 1;

          if (top_wall != 0) {
            vertexes_[cur_pos].transitions_.emplace(GetPosition(m, i - top_wall + top_wall / 2, j));
          }
          if (bottom_wall != 0) {
            vertexes_[cur_pos].transitions_.emplace(GetPosition(m, i + bottom_wall - bottom_wall / 2, j));
          }
          if (left_wall != 0) {
            vertexes_[cur_pos].transitions_.emplace(GetPosition(m, i, j - left_wall + left_wall / 2));
          }
          if (right_wall != 0) {
            vertexes_[cur_pos].transitions_.emplace(GetPosition(m, i, j + right_wall - right_wall / 2));
          }
        }
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

  Graph graph(n, m);

  graph.BfsSearch();

  return 0;
}