#include <iostream>

struct Node {
  Node* parent;
  Node* left;
  Node* right;
  int key;
};

struct BinTree {
  Node* root;
};

void Clear(Node* p);
void Height(Node* p, int& h, int& tmpH);
void Insert(BinTree& T, Node* pNew);

int main() {
  BinTree T = {nullptr};
  int key = 0;
  std::cin >> key;
  while (key != 0) {
    Node* pNew = new Node{nullptr, nullptr, nullptr, key};
    Insert(T, pNew);
    std::cin >> key;
  }
  int h = 0, tmpH = 0;
  Height(T.root, h, tmpH);
  --h;
  std::cout << h << "\n";
  Clear(T.root);
  return 0;
}

void Clear(Node* p) {
  if (p != nullptr) {
    Clear(p->left);
    Clear(p->right);
    delete p;
  }
}

void Height(Node* p, int& h, int& tmpH) {
  if (p != nullptr) {
    ++tmpH;
    Height(p->left, h, tmpH);
    Height(p->right, h, tmpH);
    --tmpH;
  }
  if (tmpH > h) {
    h = tmpH;
  }
}

void Insert(BinTree& T, Node* pNew) {
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