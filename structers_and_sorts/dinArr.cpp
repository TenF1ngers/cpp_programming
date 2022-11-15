#include <iostream>

struct DinArr {
  int* arr;
  int idOfLast;
  size_t size;
};

void upSize(DinArr& a);
void push_back(DinArr& a, int val);
void pop_back(DinArr& a);
void get(DinArr& a, int val);
void size_of(DinArr& a);
void clear(DinArr& a);

int main() {
  DinArr a = {nullptr, -1, 0};
  int n = 0, val = 0;
  std::cin >> n;
  char letter;
  char command[10];
  for (int i = 0; i < n; ++i) {
    std::cin >> command;
    letter = command[1];
    switch (letter) {
      case 'u': {
        std::cin >> val;
        push_back(a, val);
        break;
      }
      case 'o': {
        pop_back(a);
        break;
      }
      case 'e': {
        std::cin >> val;
        get(a, val);
        break;
      }
      case 'i': {
        size_of(a);
        break;
      }
      case 'l': {
        clear(a);
        std::cout << "ok"
                  << "\n";
        break;
      }
      default: {
        std::cout << "Error!"
                  << '\n';
      }
    }
  }
  delete[] a.arr;
  return 0;
}

void upSize(DinArr& a) {
  if (a.size == 0) {
    a.size = 1;
    int* newA = new int[1]();
    a.arr = newA;
  } else {
    int* newA = new int[a.size * 2]();
    for (int i = 0; i <= (int)a.idOfLast; ++i) {
      newA[i] = a.arr[i];
    }
    delete[] a.arr;
    a.arr = newA;
    a.size *= 2;
  }
}

void push_back(DinArr& a, int val) {
  if (a.size == 0) {
    upSize(a);
    a.arr[0] = val;
    ++a.idOfLast;
  } else {
    if (a.idOfLast != (int)a.size - 1) {
      a.arr[a.idOfLast + 1] = val;
      ++a.idOfLast;
    } else {
      upSize(a);
      a.arr[a.idOfLast + 1] = val;
      ++a.idOfLast;
    }
  }
  std::cout << "ok"
            << "\n";
}

void pop_back(DinArr& a) {
  if (a.idOfLast < 0) {
    std::cout << "error"
              << "\n";
  } else {
    std::cout << a.arr[a.idOfLast] << "\n";
    --a.idOfLast;
  }
}

void get(DinArr& a, int val) {
  if ((val > a.idOfLast) || (val < 0)) {
    std::cout << "Incorrect index"
              << "\n";
  } else {
    std::cout << a.arr[val]
              << "\n";
  }
}

void size_of(DinArr& a) {
  std::cout << a.idOfLast + 1
            << "\n";
}

void clear(DinArr& a) {
  if (a.size > 0) {
    delete[] a.arr;
    a.arr = nullptr;
    a.size = 0;
    a.idOfLast = -1;
  }
}