// Я тебя породить, я тебе и говорить «до свидания»! Auf Wiedersehen!

// Пин готовится к технологической выставке, продумывая лучшую расстановку экспонатов.
// По мнению пингвина, расстановка будет наилучшей, если все его механизмы будут 
//расположены вдоль одной прямой.

// Теперь Пин ищет, а как лучше распределить устройства вдоль стенда, чтобы произвести
// впечатление на комиссию. Он попросил вас, как лучшего программиста Ромашковой долины,
// написать программу, которая сможет отвечать на два типа запросов:

// slr" — узнать суммарную технологическую сложность устройств, расположенных на отрезке 
// [l,r] в 1-индексации;

// uiv" — переставить приборы так, чтобы в позиции с индексом i технологическая сложность стала 
// v. Считайте, что он просто заменяет технологическую сложность на позиции i на 
// сложность v. Не задумывайтесь, как Пин это делает, - его гениальность нам не постижима.


#include <iostream>
#include <vector>

template <class T>
class FenwickTree {
 private:
  std::vector<T> fenwick_tree_;

 public:
  FenwickTree(std::vector<T> prefix_sum, const int& size) {
    fenwick_tree_.reserve(size);

    fenwick_tree_.emplace_back(prefix_sum[0]);

    for (int i = 1; i < size; ++i) {
      if ((i & (i + 1)) - 1 < 0) {
        fenwick_tree_.emplace_back(prefix_sum[i]);
      } else {
        fenwick_tree_.emplace_back(prefix_sum[i] - prefix_sum[(i & (i + 1)) - 1]);
      }
    }
  }

  void Sum(const int& left, const int& right) {
    std::cout << this->PrefixSum(right) - this->PrefixSum(left - 1) << " ";
  }

  [[nodiscard]] T PrefixSum(const int& right) {
    T sum = 0;

    for (int i = right; i >= 0; i = (i & (i + 1)) - 1) {
      sum += fenwick_tree_[i];
    }

    return sum;
  }

  void Update(std::vector<int>& stand, const int& pos, const int& new_value) {
    int difference = new_value - stand[pos];

    auto size = static_cast<int>(stand.capacity());
    for (int i = pos; i < size; i |= i + 1) {
      fenwick_tree_[i] += difference;
    }

    stand[pos] = new_value;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  std::cin >> n;

  std::vector<int> stand;
  stand.reserve(n);

  std::vector<int64_t> prefix_sum;
  prefix_sum.reserve(n);

  int complexity = 0;
  std::cin >> complexity;
  stand.emplace_back(complexity);
  prefix_sum.emplace_back(complexity);

  for (int i = 1; i < n; ++i) {
    std::cin >> complexity;
    stand.emplace_back(complexity);
    prefix_sum.emplace_back(prefix_sum[i - 1] + complexity);
  }

  FenwickTree<int64_t> ft(prefix_sum, n);

  int m = 0;
  std::cin >> m;

  int left = 0;
  int right = 0;

  int pos = 0;
  int new_value = 0;

  char command;

  while (m != 0) {
    std::cin >> command;

    switch (command) {
      case 's': {
        std::cin >> left >> right;
        --left;
        --right;

        ft.Sum(left, right);

        break;
      }
      case 'u': {
        std::cin >> pos >> new_value;
        --pos;

        ft.Update(stand, pos, new_value);

        break;
      }
    }

    --m;
  }

  return 0;
}