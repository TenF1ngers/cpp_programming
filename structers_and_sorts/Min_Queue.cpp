#include <iostream>

struct Node {
  int val;
  int min;
  Node* next;
};

struct Stack {
  Node* head;
  size_t size;
};

struct Queue {
  Stack inS;
  Stack outS;
};

void push(Queue& q, int val);
void pop(Queue& q);
void front(Queue& q);
void size_of(Queue& q);
void clear(Queue& q);
void min_of(Queue& q);

int main() {
  int n = 0, val = 0;
  char letter;
  std::cin >> n;
  Queue q = {{nullptr, 0}, {nullptr, 0}};
  char command[10];
  for (int i = 0; i < n; ++i) {
    std::cin >> command;
    letter = command[1];
    switch (letter) {
      case 'n': {
        std::cin >> val;
        push(q, val);
        break;
      }
      case 'e': {
        pop(q);
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
        if ((q.inS.head == nullptr) && (q.outS.head == nullptr)) {
          std::cout << "ok"
                    << "\n";
        } else {
          clear(q);
          std::cout << "ok"
                    << "\n";
        }
        break;
      }
      default: {
        std::cout << "Error!"
                  << '\n';
      }
    }
  }
  clear(q);
  return 0;
}

void push(Queue& q, int val) {
  Node* pNew = new Node{val, val, nullptr};
  if (q.inS.head == nullptr) {
    q.inS.head = pNew;
  } else {
    if (pNew->min > q.inS.head->min) {
      pNew->min = q.inS.head->min;
    }
    pNew->next = q.inS.head;
    q.inS.head = pNew;
  }
  ++q.inS.size;
  std::cout << "ok" << '\n';
}

void pop(Queue& q) {
  if (q.outS.head == nullptr) {
    if (q.inS.head == nullptr) {
      std::cout << "error"
                << "\n";
    } else {
      Node* pNew = new Node{q.inS.head->val, q.inS.head->val, nullptr};
      q.outS.head = pNew;
      ++q.outS.size;
      Node* tmp = q.inS.head;
      q.inS.head = q.inS.head->next;
      if (q.inS.size == 1) {
        q.inS.head = nullptr;
      }
      delete tmp;
      --q.inS.size;
      while (q.inS.size > 0) {
        pNew = new Node{q.inS.head->val, q.inS.head->val, nullptr};
        if (pNew->min > q.outS.head->min) {
          pNew->min = q.outS.head->min;
        }
        pNew->next = q.outS.head;
        q.outS.head = pNew;
        ++q.outS.size;
        tmp = q.inS.head;
        q.inS.head = q.inS.head->next;
        if (q.inS.size == 1) {
          q.inS.head = nullptr;
        }
        delete tmp;
        --q.inS.size;
      }
      std::cout << q.outS.head->val << "\n";
      tmp = q.outS.head;
      q.outS.head = q.outS.head->next;
      if (q.outS.size == 1) {
        q.outS.head = nullptr;
      }
      delete tmp;
      --q.outS.size;
    }
  } else {
    std::cout << q.outS.head->val << "\n";
    Node* tmp = q.outS.head;
    q.outS.head = q.outS.head->next;
    if (q.outS.size == 1) {
      q.outS.head = nullptr;
    }
    delete tmp;
    --q.outS.size;
  }
}

void front(Queue& q) {
  if (q.outS.head == nullptr) {
    if (q.inS.head == nullptr) {
      std::cout << "error"
                << "\n";
    } else {
      Node* pNew = new Node{q.inS.head->val, q.inS.head->val, nullptr};
      q.outS.head = pNew;
      ++q.outS.size;
      Node* tmp = q.inS.head;
      q.inS.head = q.inS.head->next;
      if (q.inS.size == 1) {
        q.inS.head = nullptr;
      }
      delete tmp;
      --q.inS.size;
      while (q.inS.size > 0) {
        pNew = new Node{q.inS.head->val, q.inS.head->val, nullptr};
        if (pNew->min > q.outS.head->min) {
          pNew->min = q.outS.head->min;
        }
        pNew->next = q.outS.head;
        q.outS.head = pNew;
        ++q.outS.size;
        tmp = q.inS.head;
        q.inS.head = q.inS.head->next;
        if (q.inS.size == 1) {
          q.inS.head = nullptr;
        }
        delete tmp;
        --q.inS.size;
      }
      std::cout << q.outS.head->val << "\n";
    }
  } else {
    std::cout << q.outS.head->val << "\n";
  }
}

void size_of(Queue& q) {
  std::cout << q.inS.size + q.outS.size << '\n';
}

void min_of(Queue& q) {
  if (q.outS.head == nullptr) {
    if (q.inS.head == nullptr) {
      std::cout << "error"
                << "\n";
    } else {
      std::cout << q.inS.head->min << "\n";
    }
  } else {
    if (q.inS.head == nullptr) {
      std::cout << q.outS.head->min << "\n";
    } else {
      std::cout << std::min(q.inS.head->min, q.outS.head->min) << "\n";
    }
  }
}

void clear(Queue& q) {
  if (q.inS.head != nullptr) {
    Node* tmp;
    while (q.inS.head != nullptr) {
      tmp = q.inS.head;
      q.inS.head = q.inS.head->next;
      delete tmp;
      --q.inS.size;
    }
  }
  if (q.outS.head != nullptr) {
    Node* tmp;
    while (q.outS.head != nullptr) {
      tmp = q.outS.head;
      q.outS.head = q.outS.head->next;
      delete tmp;
      --q.outS.size;
    }
  }
}