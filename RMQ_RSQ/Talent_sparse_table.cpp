// Вальсы, твисты, ламбады... Мода меняется. Но моё сердце бьётся только в ритме диско!

// Бараш тоже решил поруководить толпой и заодно попасть на Шаровидение. Он выстроил
// всех смешариков так, чтобы любой подотрезок шеренги был ансамблем песни и пляски.

// Тонко чувствующему поэту позвонили с телевидения и сказали, что общая талантливость
// ансамбля равна НОДу талантов смешариков, состоящих в нем.

// Вам нужно снова помочь одному из наших героев. Напишите программу, которая сможет
// отвечать на запросы о талантливости ансамблей.

#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

template <class T>
class SparseTable {
 private:
  std::vector<std::vector<T> > sparse_table_;

 public:
  explicit SparseTable(const int& size) {
    int power_of_two = 32 - __builtin_clz(size) - 1;

    sparse_table_.resize(size, std::vector<T>(power_of_two + 1));

    for (int i = 0; i < size; ++i) {
      std::cin >> sparse_table_[i][0];
    }

    int power = 0;

    for (int j = 1; j < power_of_two + 1; ++j) {
      power = static_cast<int>(pow(2, j));

      for (int i = 0; i < size - power + 1; ++i) {
        sparse_table_[i][j] =
            std::gcd(sparse_table_[i][j - 1],
                     sparse_table_[i + static_cast<int>(pow(2, j)) - static_cast<int>(pow(2, j - 1))][j - 1]);
      }
    }
  }

  void Gcd(const int& left, const int& right) const noexcept {
    auto power = 32 - __builtin_clz(right - left + 1) - 1;

    std::cout << std::gcd(sparse_table_[left - 1][power], sparse_table_[right - static_cast<int>(pow(2, power))][power])
              << "\n";
  }
};

int main() {
  int n = 0;
  std::cin >> n;

  SparseTable<int> st(n);

  int k = 0;
  std::cin >> k;

  int left = 0;
  int right = 0;

  while (k != 0) {
    std::cin >> left >> right;

    st.Gcd(left, right);

    --k;
  }

  return 0;
}