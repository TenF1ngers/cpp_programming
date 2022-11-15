// Если ты не можешь бросить старый зонтик, то как мы можем бросить тебя — старого
// друга? Ты ведь тоже часть нашей биографии.

// Наконец-то к популярному среди старшего поколения явлению потянулась и перспективная
// молодежь. Крош изучает тренды Шар-Тока и пытается найти лучших кандидатов для
// совместного видео. Чтобы видео залетело в тренды, нашему другу нужно знать, сколько
// именно смешариков в конкретном творческом объединении имеет максимальное число
// подписчиков.

// Если вы вдруг забыли, то напомним, что все выборы в Шарараме примечательны тем, что
// любой подотрезок ряда является творческим объединением.

#include <cmath>
#include <iostream>
#include <vector>

template <class T>
class SegmentTree {
 private:
  std::vector<std::pair<T, int64_t> > segment_tree_;
  int size_;

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

  explicit SegmentTree(const int& real_size) {
    int power_of_two = 32 - __builtin_clz(real_size);

    if (real_size == static_cast<int>(pow(2, power_of_two - 1))) {
      --power_of_two;
    }

    size_ = static_cast<int>(pow(2, power_of_two));

    segment_tree_.resize(2 * size_, std::pair<T, int64_t>());

    for (int i = size_; i < size_ + real_size; ++i) {
      std::cin >> segment_tree_[i].first;
      segment_tree_[i].second = 1;
    }

    for (int i = size_ + real_size; i < 2 * size_; ++i) {
      segment_tree_[i].first = 0;
      segment_tree_[i].second = 0;
    }

    for (int i = size_ - 1; i > 0; --i) {
      segment_tree_[i].first = std::max(segment_tree_[LeftChild(i)].first, segment_tree_[RightChild(i)].first);

      segment_tree_[i].second = 0;

      segment_tree_[i].second +=
          ((segment_tree_[LeftChild(i)].first == segment_tree_[i].first) ? segment_tree_[LeftChild(i)].second : 0);

      segment_tree_[i].second +=
          ((segment_tree_[RightChild(i)].first == segment_tree_[i].first) ? segment_tree_[RightChild(i)].second : 0);
    }
  }

  [[nodiscard]] std::pair<T, int64_t> Query(int& left, int& right) const noexcept {
    std::pair<T, int64_t> left_res{0, 1};
    std::pair<T, int64_t> right_res{0, 1};

    while (left < right) {

      if (left == RightChild(Parent(left))) {
        left_res = Max(left_res, segment_tree_[left]);
      }

      left = Parent(left + 1);

      if (right == LeftChild(Parent(right))) {
        right_res = Max(right_res, segment_tree_[right]);
      }

      right = Parent(right - 1);
    }

    if (left == right) {
      left_res = Max(left_res, segment_tree_[left]);
    }

    return Max(left_res, right_res);
  }
};

int main() {
  int n = 0;
  std::cin >> n;

  SegmentTree<int> st(n);

  int k = 0;
  std::cin >> k;

  int left = 0;
  int right = 0;

  std::pair<int, int64_t> max(0, 0);

  while (k-- != 0) {
    std::cin >> left >> right;
    left += st.GetSize() - 1;
    right += st.GetSize() - 1;

    max = st.Query(left, right);

    std::cout << max.first << " " << max.second << "\n";
  }

  return 0;
}