// Город будущего застроен небоскребами, для передвижения между которыми и парковки
// транспорта многие тройки небоскребов соединены треугольной подушкой из однополярных
// магнитов. Каждая подушка соединяет ровно 3 небоскреба и вид сверху на нее представляет
// собой треугольник, с вершинами в небоскребах. Это позволяет беспрепятственно
// передвигаться между соответствующими небоскребами. Подушки можно делать на разных
// уровнях, поэтому один небоскреб может быть соединен различными подушками с парами
// других, причем два небоскреба могут соединять несколько подушек (как с разными
// третьими небоскребами, так и с одинаковым). Например, возможны две подушки на разных
// уровнях между небоскребами 1, 2 и 3, и, кроме того, магнитная подушка между 1, 2, 5.
// Система магнитных подушек организована так, что с их помощью можно добираться от
// одного небоскреба, до любого другого в этом городе (с одной подушки на другую можно
// перемещаться внутри небоскреба), но поддержание каждой из них требует больших затрат
// энергии.

// Требуется написать программу, которая определит, какие из магнитных подушек нельзя
// удалять из подушечной системы города, так как удаление даже только этой подушки может
// привести к тому, что найдутся небоскребы из которых теперь нельзя добраться до
// некоторых других небоскребов, и жителям станет очень грустно.

#include <iostream>
#include <vector>
#include <unordered_set>
#include <set>

#include <algorithm>

class Graph {

  enum class Colors { White, Black, Gray };

  std::vector<std::unordered_set<size_t>> n_;
  std::vector<size_t> in_time_;
  std::vector<size_t> up_time_;
  std::vector<Colors> colors_;

  size_t pillow_threshold_;

 public:
  explicit Graph(size_t n, size_t m) : n_(n + m) {
    pillow_threshold_ = n;
  }

  void AddEdge(size_t a, size_t b) {
    n_[a].emplace(b);
    n_[b].emplace(a);
  }

 private:
  std::set<size_t> points_;
  size_t timer_;

  void DFS(size_t i, bool is_root) {
    in_time_[i] = timer_++;
    colors_[i] = Colors::Gray;
    up_time_[i] = in_time_[i];
    size_t num = 0;
    for (const auto &x : n_[i]) {
      if (colors_[x] == Colors::White) {
        ++num;
        DFS(x, false);
        if (up_time_[i] > up_time_[x]) {
          up_time_[i] = up_time_[x];
        }
        if (up_time_[x] >= in_time_[i] && !is_root && i >= pillow_threshold_) {
          points_.emplace(i);
        }
      }
      if (colors_[x] == Colors::Gray) {
        if (up_time_[i] > in_time_[x]) {
          up_time_[i] = in_time_[x];
        }
      }
    }
    if (is_root && num > 1 && i >= pillow_threshold_) {
      points_.emplace(i);
    }
    colors_[i] = Colors::Black;
  }

 public:
  const std::set<size_t> &Points() {
    colors_ = std::vector<Colors>(n_.size(), Colors::White);
    in_time_ = std::vector<size_t>(n_.size());
    up_time_ = std::vector<size_t>(n_.size());
    timer_ = 0;
    for (size_t i = 0; i < n_.size(); ++i) {
      if (colors_[i] == Colors::White) {
        DFS(i, true);
      }
    }
    return points_;
  }
};

int main() {
  size_t n, m;
  std::cin >> n >> m;
  Graph g(n, m);
  for (size_t i = n; i < n + m; ++i) {
    size_t a, b, c;
    std::cin >> a >> b >> c;
    g.AddEdge(i, a - 1);
    g.AddEdge(i, b - 1);
    g.AddEdge(i, c - 1);
  }
  const auto &ref = g.Points();
  std::cout << ref.size();
  for (auto x : ref) {
    std::cout << "\n" << x - n + 1;
  }
  std::cout << std::endl;
  return 0;
}