#include <iostream>

struct Node {
  int val;
  Node* next;
  Node* pre;
};

struct Dequeue {
  Node* pbeg;
  Node* pend;
  size_t size;
};

void push_front(Dequeue& d, int val);
void push_back(Dequeue& d, int val);
void pop_front(Dequeue& d);
void pop_back(Dequeue& d);
void front(Dequeue& d);
void back(Dequeue& d);
void size(Dequeue& d);
void clear(Dequeue& d);

int main() {
  Dequeue d = {nullptr, nullptr, 0};
  int n = 0, val = 0;
  std::cin >> n;
  char letter2, letter5, letter6;
  char command[11];
  for (int i = 0; i < n; ++i) {
    std::cin >> command;
    letter2 = command[1];
    letter5 = command[4];
    letter6 = command[5];
    switch (letter2) {
      case 'u': {
        std::cin >> val;
        if (letter6 == 'f') {
          push_front(d, val);
          break;
        }
        push_back(d, val);
        break;
      }
      case 'o': {
        if (letter5 == 'f') {
          pop_front(d);
          break;
        }
        pop_back(d);
        break;
      }
      case 'r': {
        front(d);
        break;
      }
      case 'a': {
        back(d);
        break;
      }
      case 'i': {
        size(d);
        break;
      }
      case 'l': {
        clear(d);
        std::cout << "ok"
                  << "\n";
        break;
      }
      case 'x': {
        std::cout << "bye"
                  << "\n";
        break;
      }
      default: {
        std::cout << "Error!"
                  << '\n';
      }
    }
  }
  clear(d);
}

void push_front(Dequeue& d, int val) {
  Node* pNew = new Node{val, nullptr, nullptr};
  if (d.pbeg == nullptr) {
    d.pbeg = d.pend = pNew;
    ++d.size;
  } else {
    d.pbeg->pre = pNew;
    pNew->next = d.pbeg;
    d.pbeg = pNew;
    ++d.size;
  }
  std::cout << "ok"
            << "\n";
}

void push_back(Dequeue& d, int val) {
  Node* pNew = new Node{val, nullptr, nullptr};
  if (d.pend == nullptr) {
    d.pbeg = d.pend = pNew;
    ++d.size;
  } else {
    d.pend->next = pNew;
    pNew->pre = d.pend;
    d.pend = pNew;
    ++d.size;
  }
  std::cout << "ok"
            << "\n";
}

void pop_front(Dequeue& d) {
  if (d.pbeg == nullptr) {
    std::cout << "error"
              << "\n";
  } else {
    std::cout << d.pbeg->val
              << "\n";
    Node* tmp = d.pbeg;
    d.pbeg = d.pbeg->next;
    if (d.size == 1) {
      d.pbeg = d.pend = nullptr;
    } else {
      d.pbeg->pre = nullptr;
    }
    delete tmp;
    --d.size;
  }
}

void pop_back(Dequeue& d) {
  if (d.pend == nullptr) {
    std::cout << "error"
              << "\n";
  } else {
    std::cout << d.pend->val
              << "\n";
    Node* tmp = d.pend;
    d.pend = d.pend->pre;
    if (d.size == 1) {
      d.pbeg = d.pend = nullptr;
    } else {
      d.pend->next = nullptr;
    }
    delete tmp;
    --d.size;
  }
}

void front(Dequeue& d) {
  if (d.pbeg == nullptr) {
    std::cout << "error"
              << "\n";
  } else {
    std::cout << d.pbeg->val
              << "\n";
  }
}

void back(Dequeue& d) {
  if (d.pend == nullptr) {
    std::cout << "error"
              << "\n";
  } else {
    std::cout << d.pend->val
              << "\n";
  }
}

void size(Dequeue& d) {
  std::cout << d.size
            << "\n";
}

void clear(Dequeue& d) {
  if (d.size != 0) {
    Node* tmp;
    while (d.size > 0) {
      tmp = d.pbeg;
      d.pbeg = d.pbeg->next;
      if (d.size == 1) {
        d.pbeg = d.pend = nullptr;
      } else {
        d.pbeg->pre = nullptr;
      }
      delete tmp;
      --d.size;
    }
  }
}