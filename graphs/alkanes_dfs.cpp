// Если вы дочитали до сюда, то алканы — углеводороды, то есть соединения, состоящие из
// атомов углерода и водорода, не содержащие связей водород–водород, причём каждый
// углерод соединен ровно с четырьмя другими атомами, а каждый водород соединен ровно с
// одним другим атомом. При этом алкан является связным соединением, а также молекула
// алкана не является цикличной (для каждых двух атомов существует единственный способ
// добраться из одного в другой по связям между атомами).

// Задание такое же простое как и условие - по данной молекуле определить, является ли
// она алканом.

#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

class Graph {
 private:
  enum Color { White, Gray, Black };

  struct Node {
    std::set<std::pair<int, int> > transitions_;
    int parent_;
    char symbol;
  };

  std::vector<Node> vertexes_;
  std::vector<Color> colors_;
  size_t size_;

  void DfsVisit(const int& node, bool& is_alkane) {
    colors_[node] = Gray;

    bool is_h = false;

    if (vertexes_[node].symbol == 'H') {
      is_h = true;
    }

    int n_neighbors = 0;

    std::unordered_set<int> passed;

    for (auto& neighbor : vertexes_[node].transitions_) {
      if ((neighbor.first == node) || (passed.find(neighbor.first) != passed.end())) {
        is_alkane = false;

        break;
      }

      passed.emplace(neighbor.first);

      if (!is_alkane) {
        break;
      }

      ++n_neighbors;
      if (is_h && (n_neighbors > 1)) {
        is_alkane = false;

        break;
      }

      if (!is_h && (n_neighbors > 4)) {
        is_alkane = false;

        break;
      }

      if ((colors_[neighbor.first] == Gray) && (neighbor.first != vertexes_[node].parent_)) {
        is_alkane = false;

        break;
      }

      if (is_h && (vertexes_[neighbor.first].symbol == 'H')) {
        is_alkane = false;

        break;
      }

      if (colors_[neighbor.first] == White) {
        vertexes_[neighbor.first].parent_ = node;

        DfsVisit(neighbor.first, is_alkane);

        if (!is_alkane) {
          break;
        }
      }
    }

    if (is_h && (n_neighbors != 1)) {
      is_alkane = false;
    }
    if (!is_h && (n_neighbors != 4)) {
      is_alkane = false;
    }

    colors_[node] = Black;
  }

 public:
  Graph(const std::string& chain, const int& m, bool& is_alkane) : size_(chain.size()) {
    vertexes_.resize(size_);
    colors_.resize(size_, White);

    int count_c = 0;
    int count_h = 0;

    for (size_t i = 0; i < size_; ++i) {
      if (chain[i] == 'C') {
        ++count_c;
      } else {
        ++count_h;
      }

      vertexes_[i].symbol = chain[i];
    }

    if ((count_c == 0) || (count_h == 0)) {
      is_alkane = false;
    }

    int first = 0;
    int second = 0;

    for (int i = 0; i < m; ++i) {
      std::cin >> first >> second;
      --first;
      --second;

      vertexes_[first].transitions_.emplace(std::pair<int, int>(second, i));
      vertexes_[second].transitions_.emplace(std::pair<int, int>(first, i));
    }
  }

  void DetectAlkane() {
    bool is_alkane = true;

    for (size_t i = 0; i < size_; ++i) {
      if (colors_[i] == White) {
        if (i > 0) {
          is_alkane = false;

          break;
        }

        DfsVisit(i, is_alkane);

        if (!is_alkane) {
          break;
        }
      }
    }

    if (is_alkane) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
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

  std::string chain;
  std::cin >> chain;

  bool is_alkane = true;

  Graph graph(chain, m, is_alkane);

  if (!is_alkane) {
    std::cout << "NO\n";
  } else {
    graph.DetectAlkane();
  }

  return 0;
}