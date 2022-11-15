// Вот так всегда: для кого-то балласт, а для кого-то сокровище.

// Ромашковая долина наконец дождалась великого дня — робот Биби вернулся из космического
// путешествия во главе целой космической флотилии. По опыту Биби для космоса не 
//существует трехмерной фигуры лучше куба, поэтому его космофлот выглядит как куб с
// длиной стороны N.

// Для организации управления наш герой разделил исходный куб на N^3 кубиков с ребром
// длины 1.

// Биби хочет научиться быстро обрабатывать запросы следующих типов:

// В каком-то секторе изменилось число космолетов;

// Узнать количество космолетов в прямоугольном параллелепипеде.

#include <iostream>
#include <vector>

template <class T>
class FenwickTree {
 private:
  using Vector3D = std::vector<std::vector<std::vector<T> > >;

  Vector3D fenwick_tree_;

 public:
  explicit FenwickTree(const T& size)
      : fenwick_tree_(size, std::vector<std::vector<T> >(size, std::vector<T>(size, 0))){}

            [[nodiscard]] int PrefixSum(const T& x, const T& y, const T& z) const noexcept {
    int sum = 0;

    if ((x < static_cast<int>(fenwick_tree_.size())) && (y < static_cast<int>(fenwick_tree_.size())) &&
        (z < static_cast<int>(fenwick_tree_.size()))) {
      for (int a = x; a >= 0; a = (a & (a + 1)) - 1) {
        for (int b = y; b >= 0; b = (b & (b + 1)) - 1) {
          for (int c = z; c >= 0; c = (c & (c + 1)) - 1) {
            sum += fenwick_tree_[a][b][c];
          }
        }
      }
    }

    return sum;
  }

  void SumArea(const T& x1, const T& y1, const T& z1, const T& x2, const T& y2, const T& z2) const noexcept {
    std::cout << this->PrefixSum(x2, y2, z2) - this->PrefixSum(x2, y1 - 1, z2) - this->PrefixSum(x1 - 1, y2, z2) -
                     this->PrefixSum(x2, y2, z1 - 1) + this->PrefixSum(x2, y1 - 1, z1 - 1) +
                     this->PrefixSum(x1 - 1, y2, z1 - 1) + this->PrefixSum(x1 - 1, y1 - 1, z2) -
                     this->PrefixSum(x1 - 1, y1 - 1, z1 - 1)
              << '\n';
  }

  void Update(const T& x, const T& y, const T& z, const T& k) noexcept {
    auto size = static_cast<int>(fenwick_tree_.size());

    for (int a = x; a < size; a |= a + 1) {
      for (int b = y; b < size; b |= b + 1) {
        for (int c = z; c < size; c |= c + 1) {
          fenwick_tree_[a][b][c] += k;
        }
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  std::cin >> n;

  FenwickTree<int> ft(n);

  int command = 0;
  bool process = true;

  int x1 = 0;
  int y1 = 0;
  int z1 = 0;

  int x2 = 0;
  int y2 = 0;
  int z2 = 0;

  int k = 0;

  while (process) {
    std::cin >> command;

    switch (command) {
      case 1: {
        std::cin >> x1 >> y1 >> z1 >> k;

        ft.Update(x1, y1, z1, k);

        break;
      }
      case 2: {
        std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;

        ft.SumArea(x1, y1, z1, x2, y2, z2);

        break;
      }
      case 3: {
        process = false;

        break;
      }
    }
  }

  return 0;
}