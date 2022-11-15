#include <iostream>

struct Node {
  int key;
  Node* left;
  Node* right;
  Node* parent;
};

struct BinTree {
  Node* root;
};

void Clear(Node* p);
void Count(Node* p, int& count);
void Insert(BinTree& T, Node* pNew);

int main() {
  BinTree T = {nullptr};
  int key = 0;
  std::cin >> key;
  while (key != 0) {
    Node* pNew = new Node{key, nullptr, nullptr, nullptr};
    Insert(T, pNew);
    std::cin >> key;
  }
  int count = 0;
  Count(T.root, count);
  std::cout << count << "\n";
  Clear(T.root);
  return 0;
}

void Clear(Node* p) {
  if (p == nullptr) {
    return;
  }
  Clear(p->left);
  Clear(p->right);
  delete p;
}

void Count(Node* p, int& count) {
  if (p == nullptr) {
    return;
  }
  Count(p->left, count);
  Count(p->right, count);
  ++count;
}

void Insert(BinTree& T, Node* pNew) {
  Node *x = T.root, *y = nullptr;
  bool isSame = false;
  while (x != nullptr) {
    y = x;
    if (x->key == pNew->key) {
      isSame = true;
      break;
    }
    if (pNew->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  if (isSame) {
    delete pNew;
  } else {
    if (y == nullptr) {
      T.root = pNew;
    } else {
      pNew->parent = y;
      if (pNew->key < y->key) {
        y->left = pNew;
      } else {
        y->right = pNew;
      }
    }
  }
}