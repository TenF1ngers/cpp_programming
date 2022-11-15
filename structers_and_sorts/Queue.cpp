#include <iostream>

struct Node {
  int val;
  int min;
  Node* next;
};

struct Queue {
  Node* pbeg;
  Node* pend;
  size_t size;
};

void push_back(Queue& q, int val);
void pop_top(Queue& q);
void front(Queue& q);
void size_of(Queue& q);
void clear(Queue& q);
void min_of(Queue& q);

int main() {
  int n = 0, val = 0;
  char letter;
  std::cin >> n;
  Queue q = {nullptr, nullptr, 0};
  char command[10];
  for (int i = 0; i < n; ++i) {
    std::cin >> command;
    letter = command[1];
    switch (letter) {
      case 'n': {
        std::cin >> val;
        push_back(q, val);
        break;
      }
      case 'e': {
        pop_top(q);
        break;
      }
      case 'r': {
        front(q);
        break;
      }
      case 'i': {
        if (command[2] == 'z') {
          size_of(q);
          break;
        }
        min_of(q);
        break;
      }
      case 'l': {
        clear(q);
        std::cout << "ok" << '\n';
        break;
      }
      default: {
        std::cout << "Error!" << '\n';
      }
    }
  }
  clear(q);
  return 0;
}

void push_back(Queue& q, int val) {
  Node* pNew = new Node{val, val, nullptr};
  if (q.pend == nullptr) {
    q.pbeg = pNew;
    q.pend = pNew;
  } else {
    if (pNew->min > q.pend->min) {
      pNew->min = q.pend->min;
    }
    q.pend->next = pNew;
    q.pend = pNew;
  }
  std::cout << "ok" << '\n';
  ++q.size;
}

void pop_top(Queue& q) {
  if (q.pbeg == nullptr) {
    std::cout << "error" << '\n';
  } else {
    std::cout << q.pbeg->val << "\n";
    if (q.size != 1) {
      if (q.pbeg->min != q.pend->min) {
        Node* tmp = q.pbeg;
        q.pbeg = q.pbeg->next;
        q.pbeg->min = q.pbeg->val;
        delete tmp;
        --q.size;
      } else {
        Node* tmp = q.pbeg;
        q.pbeg = q.pbeg->next;
        delete tmp;
        --q.size;
        q.pbeg->min = q.pbeg->val;
        int min = q.pbeg->val;
        tmp = q.pbeg->next;
        for (int i = 1; i < (int)q.size; ++i) {
          if (tmp->val < min) {
            min = tmp->val;
          }
          tmp = tmp->next;
        }
        q.pend->min = min;
      }
    } else {
      Node* tmp = q.pbeg;
      q.pend = q.pbeg = nullptr;
      delete tmp;
      --q.size;
    }
  }
}

void front(Queue& q) {
  if (q.pbeg == nullptr) {
    std::cout << "error" << '\n';
  } else {
    std::cout << q.pbeg->val << '\n';
  }
}

void size_of(Queue& q) {
  std::cout << q.size << '\n';
}

void clear(Queue& q) {
  Node* tmp;
  while (q.pbeg != nullptr) {
    tmp = q.pbeg;
    q.pbeg = q.pbeg->next;
    if (q.pbeg == nullptr) {
      q.pend = nullptr;
    }
    delete tmp;
  }
  q.size = 0;
}

void min_of(Queue& q) {
  if (q.pbeg == nullptr) {
    std::cout << "error" << '\n';
  } else {
    std::cout << q.pend->min << "\n";
  }
}