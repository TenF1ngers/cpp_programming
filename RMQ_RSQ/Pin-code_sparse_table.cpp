// Очень трудно жить, думая о каждой ошибке, которую ты совершил, поэтому всё плохое
// забываешь, а помнишь только хорошее — очень удобно, но от себя не уйдёшь.

// Для новой серии научно-популярного шоу смешарикам необходимо найти в творческой
// команде самого сообразительного смешарика, принявшего участие в наименьшем количестве
// выпусков. Командой может быть любая шеренга смешариков. Вам нужно помочь нашим героям
// для каждой команды, которую они попросят, найти самого редкого гостя на экране.

#include <cmath>
#include <iostream>
#include <vector>

template <class T>
class SparseTable {
 private:
  std::vector<std::vector<T> > sparse_table_;

 public:
  SparseTable(const std::vector<T>& attendance, const int& size) {
    int power_of_two = 32 - __builtin_clz(size) - 1;

    sparse_table_.resize(size, std::vector<T>(power_of_two + 1));

    for (int i = 0; i < size; ++i) {
      sparse_table_[i][0] = attendance[i];
    }

    int limit = 0;

    for (int j = 1; j < power_of_two + 1; ++j) {
      limit = size - static_cast<int>(pow(2, j));

      for (int i = 0; i < limit + 1; ++i) {
        sparse_table_[i][j] =
            std::min(sparse_table_[i][j - 1],
                     sparse_table_[i + static_cast<int>(pow(2, j)) - static_cast<int>(pow(2, j - 1))][j - 1]);
      }
    }
  }

  void Min(const int& l, const int& r) {
    int power = 32 - __builtin_clz(r - l + 1) - 1;

    std::cout << std::min(sparse_table_[l - 1][power], sparse_table_[r - static_cast<int>(pow(2, power))][power])
              << "\n";
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  std::cin >> n;

  int q = 0;
  std::cin >> q;

  std::vector<int> attendance;
  attendance.reserve(n);

  auto capacity = static_cast<int>(attendance.capacity());
  int score = 0;

  for (int i = 0; i < capacity; ++i) {
    std::cin >> score;

    attendance.emplace_back(score);
  }

  SparseTable<int> st(attendance, n);

  int l = 0;
  int r = 0;

  while (q-- != 0) {
    std::cin >> l >> r;

    st.Min(l, r);
  }

  return 0;
}