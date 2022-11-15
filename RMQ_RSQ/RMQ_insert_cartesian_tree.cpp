// Вы уже решали задачу RMQ, даже если есть обновления на отрезке. В этот раз границы
// решения этой задачи будут расширены. А именно, надо разработать структуру данных в
// виде массива, который умеет обрабатывать следующие запросы:

// «? l r» — найти минимум на отрезке [l, r] в 1-индексации;

// «+ i x» — добавить элемент x после i-го (в 1-индексации) элемента. Если i = 0, то 
//вставка идет в начало списка.

// Изначально структура пустая.

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

struct Node {
  int64_t data_;
  int priority_;
  int size_;
  int64_t min_;

  std::weak_ptr<Node> parent_;
  std::shared_ptr<Node> left_;
  std::shared_ptr<Node> right_;

  explicit Node(const int& data, const int& priority)
      : data_(data), priority_(priority), size_(1), min_(data), left_(nullptr), right_(nullptr) {
  }
};

class CartesianTree {
 private:
  std::shared_ptr<Node> root_;

  static void FixNode(std::shared_ptr<Node> node) {
    if (node != nullptr) {
      node->size_ = ((node->left_ != nullptr) ? node->left_->size_ : 0) +
                    ((node->right_ != nullptr) ? node->right_->size_ : 0) + 1;

      if ((node->left_ != nullptr) && (node->right_ != nullptr)) {
        node->min_ = std::min(std::min(node->left_->min_, node->right_->min_), node->data_);
      } else if (node->left_ != nullptr) {
        node->min_ = std::min(node->left_->min_, node->data_);
      } else if (node->right_ != nullptr) {
        node->min_ = std::min(node->right_->min_, node->data_);
      } else {
        node->min_ = node->data_;
      }
    }
  }

  std::shared_ptr<Node> Merge(std::shared_ptr<Node> left_root, std::shared_ptr<Node> right_root) {
    if (left_root == nullptr) {
      return right_root;
    }

    if (right_root == nullptr) {
      return left_root;
    }

    if (left_root->priority_ < right_root->priority_) {
      auto right_subtree = this->Merge(left_root->right_, right_root);

      if (right_subtree != nullptr) {
        right_subtree->parent_ = left_root;
      }
      left_root->right_ = right_subtree;

      FixNode(left_root);

      return left_root;
    }

    auto left_subtree = this->Merge(left_root, right_root->left_);

    if (left_subtree != nullptr) {
      left_subtree->parent_ = right_root;
    }
    right_root->left_ = left_subtree;

    FixNode(right_root);

    return right_root;
  }

  [[nodiscard]] std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> Split(std::shared_ptr<Node> walker,
                                                                              const int& k) {
    if (walker == nullptr) {
      return {nullptr, nullptr};
    }

    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> split_subtree(nullptr, nullptr);

    if (k > GetSize(walker->left_)) {
      split_subtree = this->Split(walker->right_, k - GetSize(walker->left_) - 1);

      if (split_subtree.first != nullptr) {
        split_subtree.first->parent_ = walker;
      }
      walker->right_ = split_subtree.first;

      FixNode(walker);

      return {walker, split_subtree.second};
    }

    if (k < GetSize(walker->left_)) {
      split_subtree = this->Split(walker->left_, k);

      if (split_subtree.second != nullptr) {
        split_subtree.second->parent_ = walker;
      }
      walker->left_ = split_subtree.second;

      FixNode(walker);

      return {split_subtree.first, walker};
    }

    split_subtree = {walker->left_, walker};

    walker->left_ = nullptr;

    FixNode(walker);

    return split_subtree;
  }

 public:
  CartesianTree() : root_(nullptr) {
  }

  void Insert(const int& k, const int64_t& value) {
    auto new_node = std::make_shared<Node>(value, static_cast<int>(rand()));  //  NOLINT

    auto split_by_k = Split(root_, k);
    root_ = Merge(Merge(split_by_k.first, new_node), split_by_k.second);
  }

  [[nodiscard]] int64_t Min(const int& left, const int& right) {
    auto split_by_left = Split(root_, left);
    auto split_by_right = Split(split_by_left.second, right - left + 1);

    auto min = split_by_right.first->min_;

    auto left_subtree = Merge(split_by_left.first, split_by_right.first);
    root_ = Merge(left_subtree, split_by_right.second);

    return min;
  }

  [[nodiscard]] static int GetSize(std::shared_ptr<Node> node) {
    if (node != nullptr) {
      return node->size_;
    }

    return 0;
  }

  [[nodiscard]] std::shared_ptr<Node> GetRoot() const noexcept {
    return root_;
  }

  ~CartesianTree() = default;
};

int main() {
  srand(time(nullptr));  //  NOLINT

  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  CartesianTree ct;

  int n = 0;
  std::cin >> n;

  int i = 0;
  int64_t x = 0;

  int left = 0;
  int right = 0;

  char command;

  while (n != 0) {
    std::cin >> command;

    switch (command) {
      case '+': {
        std::cin >> i >> x;

        ct.Insert(i, x);

        break;
      }
      case '?': {
        std::cin >> left >> right;
        --left;
        --right;

        std::cout << ct.Min(left, right) << "\n";

        break;
      }
    }

    --n;
  }

  return 0;
}