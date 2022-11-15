// Реализуйте структуру данных, которая поддерживает множество S целых чисел, с котором
// разрешается производить следующие операции:

// add(i) — добавить в множество S число i (если он там уже есть, то множество не 
//меняется);

// next(i) — вывести минимальный элемент множества, не меньший i. Если искомый элемент
// в структуре отсутствует, необходимо вывести -1.

#include <iostream>

struct Node {
  Node* parent;
  Node* left;
  Node* right;
  long long key;
  long long height;
};

struct AVLBinTree {
  Node* root;
};

Node* Add(AVLBinTree& T, Node* pNew);
Node* Balance(Node* p);
long long BFactor(Node* p);
void Clear(Node* p);
void FixHeight(Node* p);
long long Height(Node* p);
Node* LeftRotate(Node* p);
long long Max(long long a, long long b);
long long Next(AVLBinTree& T, long long key);
void Print(Node* p);
Node* RightRotate(Node* p);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  AVLBinTree T = {nullptr};
  long long n = 0, val = 0, y = 0;
  std::cin >> n;
  char command, preCommand = '.';
  while (n != 0) {
    std::cin >> command;
    switch (command) {
      case '+': {
        std::cin >> val;
        Node* pNew = new Node{nullptr, nullptr, nullptr, 0, 1};
        if ((preCommand == '.') || (preCommand == '+')) {
          pNew->key = val;
        } else {
          pNew->key = (val + y) % 1000000000;
        }
        T.root = Add(T, pNew);
        preCommand = '+';
        break;
      }
      case '?': {
        std::cin >> val;
        y = Next(T, val);
        std::cout << y << "\n";
        preCommand = '?';
        break;
      }
      default: {
        std::cout << "Error!"
                  << "\n";
      }
    }
    Print(T.root);
    --n;
  }
  Clear(T.root);
  return 0;
}

Node* Add(AVLBinTree& T, Node* pNew) {
  bool isSame = false;
  Node* y = nullptr;
  Node* x = T.root;
  while (x != nullptr) {
    if (x->key == pNew->key) {
      isSame = true;
      break;
    }
    y = x;
    if (pNew->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  if (isSame) {
    delete pNew;
    return T.root;
  }
  if (y == nullptr) {
    T.root = pNew;
    return T.root;
  }
  pNew->parent = y;
  if (pNew->key < y->key) {
    y->left = pNew;
  } else {
    y->right = pNew;
  }
  y->height = Max(Height(y->left), Height(y->right)) + 1;
  while (y->parent != nullptr) {
    y = y->parent;
    y = Balance(y);
  }
  return y;
}

Node* Balance(Node* p) {
  FixHeight(p);
  if (BFactor(p) == 2) {
    if (BFactor(p->right) < 0) {
      p->right = RightRotate(p->right);
    }
    p = LeftRotate(p);
  } else if (BFactor(p) == -2) {
    if (BFactor(p->left) > 0) {
      p->left = LeftRotate(p->left);
    }
    p = RightRotate(p);
  }
  return p;
}

long long BFactor(Node* p) {
  return Height(p->right) - Height(p->left);
}

void Clear(Node* p) {
  if (p != nullptr) {
    Clear(p->left);
    Clear(p->right);
    delete p;
  }
}

void FixHeight(Node* p) {
  p->height = Max(Height(p->right), Height(p->left)) + 1;
}

long long Height(Node* p) {
  if (p != nullptr) {
    return p->height;
  }
  return 0;
}

Node* LeftRotate(Node* p) {
  Node* q = p->right;
  q->parent = p->parent;
  if (p->parent != nullptr) {
    if (p->parent->left == p) {
      p->parent->left = q;
    } else {
      p->parent->right = q;
    }
  }
  p->right = q->left;
  if (q->left != nullptr) {
    q->left->parent = p;
  }
  q->left = p;
  p->parent = q;
  FixHeight(p);
  FixHeight(q);
  return q;
}

long long Max(long long a, long long b) {
  long long max = a;
  if (b > max) {
    max = b;
  }
  return max;
}

long long Next(AVLBinTree& T, long long key) {
  Node* x = T.root;
  long long tmp = 0;
  while ((x != nullptr) && (x->key != key)) {
    if (x->key >= key) {
      tmp = x->key;
    }
    if (x->key > key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  if (x != nullptr) {
    return key;
  }
  if (tmp >= key) {
    return tmp;
  }
  return -1;
}

void Print(Node* p) {
  if (p != nullptr) {
    Print(p->left);
    std::cout << p->key << ": Height " << p->height << " parent " << p->parent << " left " << p->left << " right " << p->right << "\n";
    Print(p->right);
  }
}

Node* RightRotate(Node* p) {
  Node* q = p->left;
  q->parent = p->parent;
  if (p->parent != nullptr) {
    if (p->parent->left == p) {
      p->parent->left = q;
    } else {
      p->parent->right = q;
    }
  }
  p->left = q->right;
  if (q->right != nullptr) {
    q->right->parent = p;
  }
  q->right = p;
  p->parent = q;
  FixHeight(p);
  FixHeight(q);
  return q;
}