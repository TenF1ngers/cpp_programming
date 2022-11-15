// Доминик решил пересмотреть свой автопарк и организовать информацию о нем. Для этого
// он присвоил каждой машине номер и приоритет. Доминик уверен, что если расположить
// машины как вершины в декартовом дерева поиска, то он сможет подбирать нужную тачку 
//на гонку оптимально.

// Так как Доминик, как и всегда, торопится на встречу с семьей, ему нужно построить
// дерево для хранения информации о машинах за линейное время от числа машин.

// Если Доминик выбрал неверные приоритеты, и дерево построить невозможно, то выведите
// NO. Иначе выведите N строк, каждая из которых должна описывать вершину. Описание
// вершины состоит из трёх чисел: номер предка, номер левого сына и номер правого сына.
// Если у вершины отсутствует предок или какой-либо из сыновей, то выводите на его
// месте число 0.

// Если подходящих деревьев несколько, выведите любое.

#include <iostream>

template <class T>
class CartesianTree {
 private:
  struct Node {
    T data_;
    int priority_;
    int position_;

    Node* parent_;
    Node* left_;
    Node* right_;

    Node(const T& data, const int& priority, int pos)
        : data_(data), priority_(priority), position_(pos), parent_(nullptr), left_(nullptr), right_(nullptr) {
    }
  };

  Node* root_;

 public:
  explicit CartesianTree(int& size) {
    int x = 0;
    int y = 0;

    std::cin >> x >> y;

    root_ = new Node(x, y, 1);

    Node* last_inserted = root_;

    for (int i = 2; i < size + 1; ++i) {
      std::cin >> x >> y;

      auto new_element = new Node(x, y, i);

      while ((last_inserted != nullptr) && (new_element->priority_ < last_inserted->priority_)) {
        last_inserted = last_inserted->parent_;
      }

      if (last_inserted == nullptr) {
        new_element->left_ = root_;
        root_->parent_ = new_element;

        root_ = new_element;
      } else {
        new_element->left_ = last_inserted->right_;

        if (last_inserted->right_ != nullptr) {
          last_inserted->right_->parent_ = new_element;
        }

        new_element->parent_ = last_inserted;
        last_inserted->right_ = new_element;
      }

      last_inserted = new_element;
    }
  }

  void InorderWalk(Node* walker) const noexcept {
    if (walker->left_ == nullptr) {
      if (walker->parent_ == nullptr) {
        std::cout << 0 << " ";
      } else {
        std::cout << walker->parent_->position_ << " ";
      }
      std::cout << 0 << " ";
      if (walker->right_ == nullptr) {
        std::cout << 0 << " ";
      } else {
        std::cout << walker->right_->position_;
      }
      std::cout << "\n";

      if (walker->right_ != nullptr) {
        this->InorderWalk(walker->right_);
      }

      return;
    }

    this->InorderWalk(walker->left_);

    if (walker->parent_ == nullptr) {
      std::cout << 0 << " ";
    } else {
      std::cout << walker->parent_->position_ << " ";
    }
    std::cout << walker->left_->position_ << " ";
    if (walker->right_ == nullptr) {
      std::cout << 0 << " ";
    } else {
      std::cout << walker->right_->position_;
    }
    std::cout << "\n";

    if (walker->right_ != nullptr) {
      this->InorderWalk(walker->right_);
    }
  }

  void Clear(Node* walker) {
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

  [[nodiscard]] Node* GetRoot() const noexcept {
    return root_;
  }

  ~CartesianTree() {
    this->Clear(root_);
  }
};

int main() {
  int n = 0;
  std::cin >> n;

  CartesianTree<int> ct(n);

  std::cout << "YES\n";

  ct.InorderWalk(ct.GetRoot());

  return 0;
}