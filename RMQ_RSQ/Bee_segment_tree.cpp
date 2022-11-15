// Ёлки-иголки, да что же это такое тут происходит?

// После ударного дачного сезона Копатыч расставил свои ульи в ряд, чтобы определить
// лучшую пчелиную семью (подотрезок ряда).

// Качество пчелиной семьи Копатыч определяет по наибольшему количеству собранного меда
// в одном улье. Периодически Копатыч собирает дополнительный мед из того или иного улья.

// Необходимо помочь Копатычу определить качество каждой пчелиной семьи и разобраться в
// его отношениях со сбором меда.

// В первой строке вводится одно натуральное число N (1≤N≤100000) — количество ульев в ряду.
// Во второй строке вводятся N чисел от 0 до 100000 — количество собранного меда с каждого улья в начальный момент.
// В третьей строке вводится одно натуральное число M (1≤M≤30000) — количество запросов Копатыча.
// Каждая из следующих M строк представляет собой описание запроса. Сначала вводится одна буква, кодирующая вид запроса (
// m — найти наибольшее число собранного меда в семье, a — увеличить число собранного меда у пчелиной семьи).
// Следом за m вводятся два числа — левая и правая граница ряда.
// Следом за a вводятся три числа — левый и правый концы ряда и число add, на которое
// нужно увеличить количество собранного меда у каждого улья данной пчелиной семьи (0≤add≤100000).


#include <cmath>
#include <iostream>
#include <vector>

template <class T>
class SegmentTree {
 private:
  struct Node {
    T data_;
    int promise_;

    Node(const T& new_data, const int& new_promise) : data_(new_data), promise_(new_promise) {
    }
  };

  std::vector<Node> segment_tree_;
  int size_;
  int real_size_;

 public:
  [[nodiscard]] std::pair<T, int64_t> Max(const std::pair<T, int64_t>& first,
                                          const std::pair<T, int64_t>& second) const {
    if (first.first == second.first) {
      return {first.first, first.second + second.second};
    }
    if (first.first > second.first) {
      return first;
    }
    return second;
  }

  [[nodiscard]] int LeftChild(const int& pos) const {
    return pos << 1;
  }

  [[nodiscard]] int RightChild(const int& pos) const {
    return (pos << 1) + 1;
  }

  [[nodiscard]] int Parent(const int& pos) const {
    return pos / 2;
  }

  [[nodiscard]] int GetSize() const noexcept {
    return size_;
  }

  explicit SegmentTree(const int& real_size) : real_size_(real_size) {
    int power_of_two = 32 - __builtin_clz(real_size);

    if (real_size == static_cast<int>(pow(2, power_of_two - 1))) {
      --power_of_two;
    }

    size_ = static_cast<int>(pow(2, power_of_two));

    segment_tree_.resize(2 * size_, Node(0, 0));

    int score = 0;

    for (int i = size_; i < size_ + real_size; ++i) {
      std::cin >> score;
      segment_tree_[i].data_ = score;
    }

    for (int i = size_ - 1; i > 0; --i) {
      segment_tree_[i].data_ =
          std::max(segment_tree_[this->LeftChild(i)].data_, segment_tree_[this->RightChild(i)].data_);
    }
  }

  [[nodiscard]] int64_t Max(const int& left, const int& right, int start, int begin, int end) noexcept {
    if (left - right + 1 == real_size_) {
      return segment_tree_[start].data_ + segment_tree_[start].promise_;
    }

    if ((begin >= left) && (end <= right)) {
      return segment_tree_[start].data_ + segment_tree_[start].promise_;
    }

    if ((begin > right) || (end < left)) {
      return 0;
    }

    Push(start);

    int64_t left_res = this->Max(left, right, this->LeftChild(start), begin, (begin + end) / 2);
    int64_t right_res = this->Max(left, right, this->RightChild(start), (begin + end) / 2 + 1, end);

    return std::max(left_res, right_res);
  }

  void Push(const int& pos) {
    segment_tree_[pos].data_ += segment_tree_[pos].promise_;
    segment_tree_[this->LeftChild(pos)].promise_ += segment_tree_[pos].promise_;
    segment_tree_[this->RightChild(pos)].promise_ += segment_tree_[pos].promise_;

    segment_tree_[pos].promise_ = 0;
  }

  void Update(int& left, int& right, int&& start, int begin, int end, const int& add) {
    if (left - right + 1 == real_size_) {
      segment_tree_[start].promise_ += add;

      return;
    }

    if ((begin >= left) && (end <= right)) {
      segment_tree_[start].promise_ += add;

      return;
    }

    if ((begin > right) || (end < left)) {
      return;
    }

    this->Push(start);

    Update(left, right, this->LeftChild(start), begin, (begin + end) / 2, add);
    Update(left, right, this->RightChild(start), (begin + end) / 2 + 1, end, add);

    segment_tree_[start].data_ =
        std::max(this->Max(begin, (begin + end) / 2, this->LeftChild(start), begin, (begin + end) / 2),
                 this->Max((begin + end) / 2 + 1, end, this->RightChild(start), (begin + end) / 2 + 1, end));
  }
};

int main() {
  int n = 0;
  std::cin >> n;

  SegmentTree<int64_t> st(n);

  int m = 0;
  std::cin >> m;

  int left = 0;
  int right = 0;
  int add = 0;

  int64_t max = 0;

  int begin = 0;
  int end = 0;

  char command;

  while (m != 0) {
    std::cin >> command;

    switch (command) {
      case 'm': {
        std::cin >> left >> right;
        left += st.GetSize() - 1;
        right += st.GetSize() - 1;

        begin = st.GetSize();
        end = 2 * st.GetSize() - 1;

        max = st.Max(left, right, 1, begin, end);

        std::cout << max << " ";
        break;
      }
      case 'a': {
        std::cin >> left >> right >> add;
        left += st.GetSize() - 1;
        right += st.GetSize() - 1;

        st.Update(left, right, 1, st.GetSize(), 2 * st.GetSize() - 1, add);

        break;
      }
    }

    --m;
  }

  return 0;
}