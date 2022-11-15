// Реализуйте структуру данных, которая поддерживает множество S целых чисел, с 
//которым разрешается производить следующие операции:

// add(i) — добавить в множество S число i (если оно там уже есть, то множество не 
// меняется);

// sum(l, r) — вывести сумму всех элементов x из S, которые удовлетворяют неравенству
// l ≤ x ≤ r.

#include <cstdlib>
#include <ctime>
#include <iostream>

template <class T>
struct Node {
  T data_;
  int priority_;
  int64_t sum_;

  Node* parent_;
  Node* left_;
  Node* right_;

  Node(const T& data, const int& priority)
      : data_(data), priority_(priority), sum_(data), parent_(nullptr), left_(nullptr), right_(nullptr) {
  }
};

template <class T>
class CartesianTree {
 private:
  Node<T>* root_;

  void Clear(Node<T>* walker) {
    if (walker != nullptr) {
      if (walker->left_ == nullptr) {
        if (walker->right_ == nullptr) {
          delete walker;
        } else {
          this->Clear(walker->right_);

          delete walker;
        }

        return;
      }

      this->Clear(walker->left_);

      if (walker->right_ == nullptr) {
        delete walker;
      } else {
        this->Clear(walker->right_);

        delete walker;

        return;
      }
    }
  }

  void FixNode(Node<T>* node) {
    if (node != nullptr) {
      node->sum_ = ((node->left_ != nullptr) ? node->left_->sum_ : 0) +
                   ((node->right_ != nullptr) ? node->right_->sum_ : 0) + node->data_;
    }
  }

  Node<T>* Merge(Node<T>* left_root, Node<T>* right_root) {
    if (left_root == nullptr) {
      return right_root;
    }

    if (right_root == nullptr) {
      return left_root;
    }

    if (left_root->priority_ < right_root->priority_) {
      Node<T>* right_subtree = this->Merge(left_root->right_, right_root);

      if (right_subtree != nullptr) {
        right_subtree->parent_ = left_root;
      }
      left_root->right_ = right_subtree;

      this->FixNode(left_root);

      return left_root;
    }

    Node<T>* left_subtree = this->Merge(left_root, right_root->left_);

    if (left_subtree != nullptr) {
      left_subtree->parent_ = right_root;
    }
    right_root->left_ = left_subtree;

    this->FixNode(right_root);

    return right_root;
  }

  [[nodiscard]] std::pair<Node<T>*, Node<T>*> Split(Node<T>* walker, const T& key) {
    if (walker == nullptr) {
      return std::pair<Node<T>*, Node<T>*>(nullptr, nullptr);
    }

    std::pair<Node<T>*, Node<T>*> split_subtree(nullptr, nullptr);

    if (key < walker->data_) {
      split_subtree = this->Split(walker->left_, key);

      if (split_subtree.second != nullptr) {
        split_subtree.second->parent_ = walker;
      }
      walker->left_ = split_subtree.second;

      this->FixNode(walker);

      if (split_subtree.first != nullptr) {
        split_subtree.first->parent_ = nullptr;

        if (split_subtree.first->parent_ != nullptr) {
          (split_subtree.first->parent_->left_ == split_subtree.first) ? split_subtree.first->parent_->left_ = nullptr
                                                                       : split_subtree.first->parent_->right_ = nullptr;
        }
      }

      return {split_subtree.first, walker};
    }

    if (walker->data_ < key) {
      split_subtree = this->Split(walker->right_, key);

      if (split_subtree.first != nullptr) {
        split_subtree.first->parent_ = walker;
      }
      walker->right_ = split_subtree.first;

      this->FixNode(walker);

      if (split_subtree.second != nullptr) {
        split_subtree.second->parent_ = nullptr;

        if (split_subtree.second->parent_ != nullptr) {
          (split_subtree.second->parent_->left_ == split_subtree.second)
              ? split_subtree.second->parent_->left_ = nullptr
              : split_subtree.second->parent_->right_ = nullptr;
        }
      }

      return {walker, split_subtree.second};
    }

    split_subtree = {walker->left_, walker};

    if (walker->left_ != nullptr) {
      walker->left_->parent_ = nullptr;
    }
    walker->left_ = nullptr;

    if (walker->parent_ != nullptr) {
      (split_subtree.second->parent_->left_ == walker) ? split_subtree.second->parent_->left_ = nullptr
                                                       : split_subtree.second->parent_->right_ = nullptr;
    }
    walker->parent_ = nullptr;

    this->FixNode(walker);

    return split_subtree;
  }

 public:
  CartesianTree()
      : root_(nullptr){}

            [[nodiscard]] Node<T> *
      Exists(Node<T> * walker, const T& value) const {
    while ((walker != nullptr) && (walker->data_ != value)) {
      if (value < walker->data_) {
        walker = walker->left_;
      } else {
        walker = walker->right_;
      }
    }

    return walker;
  }

  void Insert(const T& value, const int& priority) {
    auto tmp = this->Exists(root_, value);
    if (tmp == nullptr) {
      std::pair<Node<T>*, Node<T>*> split_tree = this->Split(root_, value);

      auto new_node = new Node<T>(value, priority);

      auto left_subtree = this->Merge(split_tree.first, new_node);

      root_ = this->Merge(left_subtree, split_tree.second);
    }
  }

  T Sum(const T& left, const T& right) {
    auto by_left = this->Split(root_, left);
    auto by_right = this->Split(by_left.second, right + 1);

    int64_t sum = 0;

    if (by_right.first != nullptr) {
      sum = by_right.first->sum_;
    }

    Node<T>* right_subtree = this->Merge(by_right.first, by_right.second);
    root_ = this->Merge(by_left.first, right_subtree);

    return sum;
  }

  [[nodiscard]] int GetSize(Node<T>* node) const {
    if (node != nullptr) {
      return node->size_;
    }

    return 0;
  }

  [[nodiscard]] Node<T>* GetRoot() const noexcept {
    return root_;
  }

  ~CartesianTree() {
    this->Clear(root_);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  srand(time(nullptr));  //  NOLINT

  int n = 0;
  std::cin >> n;

  CartesianTree<int64_t> ct;

  int64_t value = 0;
  int64_t left = 0;
  int64_t right = 0;

  int64_t sum = 0;

  char command;

  while (n != 0) {
    std::cin >> command;

    switch (command) {
      case '+': {
        std::cin >> value;

        ct.Insert(value, rand());  //  NOLINT

        break;
      }
      case '?': {
        std::cin >> left >> right;

        sum = ct.Sum(left, right);

        std::cout << sum << "\n";

        break;
      }
    }

    --n;
  }

  return 0;
}