// В постфиксной записи (или обратной польской записи) операция записывается после двух
// операндов. Например, сумма двух чисел A и B записывается как «A B +». Запись
// «B C + D *» обозначает привычное нам «(B + C) * D», а запись «A B C + D * +» означает
// «A + (B + C) * D». Достоинство постфиксной записи в том, что она не требует скобок
// и дополнительных соглашений о приоритете операторов для своего чтения.

#include <cstring>
#include <iostream>

struct Node {
  int val;
  Node* next;
  Node* pre;
};

struct List {
  Node* pend;
};

void push(List& l, int num);
void pop(List& l);

int main() {
  char str[100000] = {};
  std::cin.getline(str, 100000);
  List l = {nullptr};
  char operation = '.';
  int curCountOfOperands = 0, countOfOperands = 0, curCountOfOperations = 0;
  int expValue = 0, interValue = 0, num = 0, len = (int)strlen(str);
  for (int i = 0; i < len; ++i) {
    if ((curCountOfOperands == 2) && (curCountOfOperations == 1)) {
      --countOfOperands;
      if (l.pend != nullptr) {
        if (operation == '+') {
          interValue = l.pend->pre->val + l.pend->val;
          pop(l);
          l.pend->val = interValue;
        } else if (operation == '-') {
          interValue = l.pend->pre->val - l.pend->val;
          pop(l);
          l.pend->val = interValue;
        } else {
          interValue = l.pend->pre->val * l.pend->val;
          pop(l);
          l.pend->val = interValue;
        }
        if (countOfOperands >= 2) {
          curCountOfOperands = 2;
        }
        curCountOfOperations = 0;
      }
    }
    if (str[i] != ' ') {
      if ((str[i] != '+') && (str[i] != '-') && (str[i] != '*')) {
        num = str[i] - '0';
        push(l, num);
        ++countOfOperands;
        if (curCountOfOperands < 2) {
          ++curCountOfOperands;
        }
      } else {
        operation = str[i];
        ++curCountOfOperations;
      }
    }
  }
  if (l.pend != nullptr) {
    if (operation == '+') {
      interValue = l.pend->pre->val + l.pend->val;
      pop(l);
      l.pend->val = interValue;
    } else if (operation == '-') {
      interValue = l.pend->pre->val - l.pend->val;
      pop(l);
      l.pend->val = interValue;
    } else {
      interValue = l.pend->pre->val * l.pend->val;
      pop(l);
      l.pend->val = interValue;
    }
    expValue = l.pend->val;
    std::cout << expValue
              << "\n";
    delete l.pend;
  }
  return 0;
}

void push(List& l, int num) {
  Node* pNew = new Node{num, nullptr, nullptr};
  if (l.pend == nullptr) {
    l.pend = pNew;
  } else {
    pNew->pre = l.pend;
    l.pend->next = pNew;
    l.pend = pNew;
  }
}

void pop(List& l) {
  Node* tmp;
  tmp = l.pend;
  l.pend = l.pend->pre;
  l.pend->next = nullptr;
  delete tmp;
}