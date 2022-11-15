// Гоблины Мглистых гор очень любях ходить к своим шаманам. Так как гоблинов много,
// к шаманам часто образуются очень длинные очереди. А поскольку много гоблинов в одном
// месте быстро образуют шумную толку, которая мешает шаманам проводить сложные
// медицинские манипуляции, последние решили установить некоторые правила касательно
// порядка в очереди.

// Обычные гоблины при посещении шаманов должны вставать в конец очереди.
// Привилегированные же гоблины, знающие особый пароль, встают ровно в ее середину,
// причем при нечетной длине очереди они встают сразу за центром.

// Так как гоблины также широко известны своим непочтительным отношением ко всяческим
// правилам и законам, шаманы попросили вас написать программу, которая бы отслеживала
// порядок гоблинов в очереди.

// В первой строке входных данный записано число 

// N (1 ≤ N ≤ 10^5) — количество запросов к программе. Следующие N строк содержат описание запросов в формате:

// «+ i» — гоблин с номером i (1≤i≤N) встает в конец очереди;

// «* i» — привилегированный гоблин с номером i встает в середину очереди;
// «-» — первый гоблин из очереди уходит к шаманам. Гарантируется, что на момент
// такого запроса очередь не пуста.

#include <iostream>

struct Node {
  int number;
  Node* next;
  Node* pre;
};

struct GobQueue {
  Node* pbeg;
  Node* pend;
  Node* mid;
  size_t size;
};

void push_back(GobQueue& gq, int num);
void push_mid(GobQueue& gq, int num);
void pop_front(GobQueue& gq);

int main() {
  int n = 0;
  std::cin >> n;
  GobQueue gq = {nullptr, nullptr, nullptr, 0};
  char symbol = '.';
  int num = 0;
  while (n != 0) {
    std::cin >> symbol;
    switch (symbol) {
      case '+': {
        std::cin >> num;
        push_back(gq, num);
        break;
      }
      case '*': {
        std::cin >> num;
        push_mid(gq, num);
        break;
      }
      case '-': {
        pop_front(gq);
        break;
      }
      default: {
        std::cout << "Error!"
                  << "\n";
      }
    }
    --n;
  }
  while (gq.size != 0) {
    Node* tmp = gq.pbeg;
    gq.pbeg = gq.pbeg->next;
    if (gq.size == 1) {
      gq.pbeg = gq.pend = nullptr;
    }
    delete tmp;
    --gq.size;
  }
  return 0;
}

void push_back(GobQueue& gq, int num) {
  Node* pNew = new Node{num, nullptr, nullptr};
  if (gq.pend == nullptr) {
    gq.pbeg = gq.pend = pNew;
    gq.mid = pNew;
    ++gq.size;
  } else {
    pNew->pre = gq.pend;
    gq.pend->next = pNew;
    gq.pend = pNew;
    if (gq.size % 2 != 0) {
      gq.mid = gq.mid->next;
    }
    ++gq.size;
  }
}

void push_mid(GobQueue& gq, int num) {
  Node* pNew = new Node{num, nullptr, nullptr};
  if (gq.pend == nullptr) {
    gq.pbeg = gq.pend = pNew;
    gq.mid = pNew;
    ++gq.size;
  } else {
    if (gq.size == 1) {
      pNew->pre = gq.pend;
      gq.pend->next = pNew;
      gq.pend = pNew;
      gq.mid = gq.mid->next;
      ++gq.size;
    } else if (gq.size % 2 == 0) {
      pNew->pre = gq.mid->pre;
      pNew->next = gq.mid;
      gq.mid->pre->next = pNew;
      gq.mid->pre = pNew;
      gq.mid = gq.mid->pre;
      ++gq.size;
    } else {
      pNew->pre = gq.mid;
      pNew->next = gq.mid->next;
      gq.mid->next->pre = pNew;
      gq.mid->next = pNew;
      gq.mid = gq.mid->next;
      ++gq.size;
    }
  }
}

void pop_front(GobQueue& gq) {
  if (gq.pbeg != nullptr) {
    std::cout << gq.pbeg->number
              << "\n";
  }
  if (gq.size == 1) {
    Node* tmp = gq.pbeg;
    gq.pbeg = gq.pend = gq.mid = nullptr;
    delete tmp;
    gq.size = 0;
  } else {
    Node* tmp = gq.pbeg;
    if (gq.pbeg != nullptr) {
      gq.pbeg = gq.pbeg->next;
      gq.pbeg->pre = nullptr;
      if (gq.size % 2 != 0) {
        gq.mid = gq.mid->next;
      }
      delete tmp;
      --gq.size;
    }
  }
}