// Входной файл содержит описание операций с деревом семьи, их количество не превышает
// 10^5. В каждой строке находится одна из следующих операций.

// insert x — добавить в дерево члена семьи с настроением x. Если такой уже есть, то ничего делать не надо.

// delete x — удалить из дерева члена семьи с настроением x. Если его там нет, то ничего делать не надо.

// exists x — если имеется член семьи с настроением x, выведите true, иначе, false.

// next x — выведите настроение такого члена семьи, что оно лучше чем x, но минимально
// среди таких или none, если такого нет. Это нужно, чтобы понимать, кого на предстоящую
// гонку можно брать в команду, а кому надо отдохнуть.

// prev x — выведите настроение такого члена семьи, что оно хуже чем x, но максимально 
//среди таких или none, если такого нет.

// kth k — выведите k-ю величину настроения (нумерация с нуля). Если такого не
// существует, то выведите none.

#include <cstdlib>
#include <ctime>
#include <iostream>

template <class T>
struct Node {
  T data_;
  int priority_;
  int size_;

  Node* parent_;
  Node* left_;
  Node* right_;

  Node(const T& data, const int& priority)
      : data_(data), priority_(priority), size_(1), parent_(nullptr), left_(nullptr), right_(nullptr) {
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
      node->size_ = ((node->left_ != nullptr) ? node->left_->size_ : 0) +
                    ((node->right_ != nullptr) ? node->right_->size_ : 0) + 1;
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

      this->FixNode(split_subtree.first);
      this->FixNode(split_subtree.second);

      if (split_subtree.second != nullptr) {
        split_subtree.second->parent_ = walker;
      }
      walker->left_ = split_subtree.second;

      this->FixNode(walker);

      return {split_subtree.first, walker};
    }

    if (walker->data_ < key) {
      split_subtree = this->Split(walker->right_, key);

      this->FixNode(split_subtree.first);
      this->FixNode(split_subtree.second);

      if (split_subtree.first != nullptr) {
        split_subtree.first->parent_ = walker;
      }
      walker->right_ = split_subtree.first;

      this->FixNode(walker);

      return {walker, split_subtree.second};
    }

    split_subtree = {walker->left_, walker};

    if (walker->left_ != nullptr) {
      walker->left_->parent_ = nullptr;
    }
    walker->left_ = nullptr;

    this->FixNode(walker);

    return split_subtree;
  }

 public:
  CartesianTree() : root_(nullptr) {
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

  [[nodiscard]] Node<T>* Exists(Node<T>* walker, const T& value) const {
    while ((walker != nullptr) && (walker->data_ != value)) {
      if (value < walker->data_) {
        walker = walker->left_;
      } else {
        walker = walker->right_;
      }
    }

    return walker;
  }

  void Delete(const T& value) {
    auto found_node = this->Exists(root_, value);

    if (found_node != nullptr) {
      std::pair<Node<T>*, Node<T>*> split_tree = {found_node->left_, found_node->right_};

      Node<T>* parent = found_node->parent_;

      int way = 0;

      if (parent != nullptr) {
        if (found_node == found_node->parent_->left_) {
          way = 1;
        } else {
          way = 2;
        }
      }

      delete found_node;

      if (split_tree.first != nullptr) {
        split_tree.first->parent_ = nullptr;
      }
      if (split_tree.second != nullptr) {
        split_tree.second->parent_ = nullptr;
      }

      Node<T>* new_subtree = this->Merge(split_tree.first, split_tree.second);

      if (new_subtree != nullptr) {
        new_subtree->parent_ = parent;
      }

      if (parent != nullptr) {
        if (way == 1) {
          parent->left_ = new_subtree;
        } else {
          parent->right_ = new_subtree;
        }
        while (parent != nullptr) {
          this->FixNode(parent);

          parent = parent->parent_;
        }
      } else {
        root_ = new_subtree;
      }
    }
  }

  void Next(Node<T>* walker, const T& key) const {
    T min = key;
    int count = 0;

    while ((walker != nullptr) && (count == 0)) {
      if (key < walker->data_) {
        ++count;
        min = walker->data_;
        walker = walker->left_;
      } else if (walker->data_ < key) {
        walker = walker->right_;
      } else {
        ++count;
        walker = walker->right_;
      }
    }

    if (walker == nullptr) {
      if (min != key) {
        std::cout << min << "\n";
      } else {
        std::cout << "none\n";
      }
    } else {
      while (walker != nullptr) {
        if (key < walker->data_) {
          min = walker->data_;
          walker = walker->left_;
        } else {
          walker = walker->right_;
        }
      }

      std::cout << min << "\n";
    }
  }

  void Prev(Node<T>* walker, const T& key) const {
    T max = key;
    int count = 0;

    while ((walker != nullptr) && (count == 0)) {
      if (key > walker->data_) {
        ++count;
        max = walker->data_;
        walker = walker->right_;
      } else if (walker->data_ > key) {
        walker = walker->left_;
      } else {
        ++count;
        walker = walker->left_;
      }
    }

    if (walker == nullptr) {
      if (max != key) {
        std::cout << max << "\n";
      } else {
        std::cout << "none\n";
      }
    } else {
      while (walker != nullptr) {
        if (key > walker->data_) {
          max = walker->data_;
          walker = walker->right_;
        } else {
          walker = walker->left_;
        }
      }

      std::cout << max << "\n";
    }
  }

  [[nodiscard]] int GetSize(Node<T>* node) const {
    if (node != nullptr) {
      return node->size_;
    }

    return 0;
  }

  void Kth(Node<T>* walker, int k) const {
    if (walker != nullptr) {

      if (this->GetSize(walker->left_) == k) {
        std::cout << walker->data_ << "\n";

        return;
      }

      if (this->GetSize(walker->left_) < k) {
        this->Kth(walker->right_, k - this->GetSize(walker->left_) - 1);

        return;
      }

      this->Kth(walker->left_, k);
    } else {
      std::cout << "none\n";
    }
  }

  [[nodiscard]] Node<T>* GetRoot() const noexcept {
    return root_;
  }

  ~CartesianTree() {
    this->Clear(root_);
  }
};

int main() {
  srand(time(nullptr));  //  NOLINT

  CartesianTree<int> ct;

  int value = 0;
  int i = 0;
  int k = 0;

  char command[7];

  while (std::cin >> command) {

    switch (command[0]) {
      case 'i': {
        std::cin >> value;

        i = rand();  //  NOLINT

        ct.Insert(value, i);

        break;
      }
      case 'd': {
        std::cin >> value;

        ct.Delete(value);

        break;
      }
      case 'e': {
        std::cin >> value;

        if (ct.Exists(ct.GetRoot(), value) != nullptr) {
          std::cout << "true\n";
        } else {
          std::cout << "false\n";
        }

        break;
      }
      case 'n': {
        std::cin >> value;

        ct.Next(ct.GetRoot(), value);

        break;
      }
      case 'p': {
        std::cin >> value;

        ct.Prev(ct.GetRoot(), value);

        break;
      }
      case 'k': {
        std::cin >> k;

        ct.Kth(ct.GetRoot(), k);

        break;
      }
    }
  }

  return 0;
}