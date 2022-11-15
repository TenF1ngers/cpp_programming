// Реализуйте структуру данных, способную выполнять операции ниже. Напишите программу,
// реализовав все указанные здесь методы. Возможные команды для программы:

// insert n — добавить в структуру число n (1 ≤ n ≤ 109) (значение n задается после
// команды). Программа должна вывести ok.

// extract_min — удалить из структуры минимальный элемент. Программа должна вывести 
//его значение.

// get_min — программа должна вывести значение минимального элемента, не удаляя его
// из структуры.

// extract_max — удалить из структуры максимальный элемент. Программа должна вывести
// его значение.

// get_max — программа должна вывести значение миаксимального элемента, не удаляя его
// из структуры.

// size — программа должна вывести количество элементов в структуре.

// clear — Программа должна очистить структуру и вывести ok.

// Если во входных данных встречается операция extract_min, extract_max, get_min или
// get_max, и при этом в структуре нет ни одного элемента, то программа должна вместо
// числового значения вывести строку error.

#include <iostream>

struct Heap {
  int arr[200001];
  size_t posOfLastNode;
};

void Clear(Heap& h);
void ExtractMax(Heap& h);
void ExtractMin(Heap& h);
void GetMax(Heap& h);
void GetMin(Heap& h);
void Insert(Heap& h, int n);
size_t LeftChild(size_t pos);
size_t Parent(size_t pos);
size_t RightChild(size_t pos);
void SiftDown(Heap& h, size_t pos);
void SiftUp(Heap& h, size_t pos);
void Size(Heap& h);
void Swap(Heap& h, size_t first, size_t second);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Heap h = {{}, 0};
  char command[12], letter2, letter6, letter10;
  int m = 0, n = 0;
  std::cin >> m;
  while (m != 0) {
    std::cin >> command;
    letter2 = command[1];
    switch (letter2) {
      case 'n': {
        std::cin >> n;
        Insert(h, n);
        std::cout << "ok"
                  << "\n";
        break;
      }
      case 'x': {
        letter10 = command[9];
        if (letter10 == 'i') {
          ExtractMin(h);
        } else {
          ExtractMax(h);
        }
        break;
      }
      case 'e': {
        letter6 = command[5];
        if (letter6 == 'i') {
          GetMin(h);
        } else {
          GetMax(h);
        }
        break;
      }
      case 'l': {
        Clear(h);
        std::cout << "ok"
                  << "\n";
        break;
      }
      case 'i': {
        Size(h);
        break;
      }
    }
    --m;
  }
  return 0;
}

void Clear(Heap& h) {
  h.posOfLastNode = 0;
}

void ExtractMax(Heap& h) {
  if (h.posOfLastNode == 0) {
    std::cout << "error"
              << "\n";
  } else {
    std::cout << h.arr[1] << "\n";
    Swap(h, 1, h.posOfLastNode);
    --h.posOfLastNode;
    if (h.posOfLastNode != 0) {
      SiftDown(h, 1);
    }
  }
}

void ExtractMin(Heap& h) {
  if (h.posOfLastNode == 0) {
    std::cout << "error"
              << "\n";
  } else {
    size_t min = h.posOfLastNode / 2 + 1;
    for (size_t i = h.posOfLastNode / 2 + 2; i <= h.posOfLastNode; ++i) {
      if (h.arr[i] < h.arr[min]) {
        min = i;
      }
    }
    std::cout << h.arr[min] << "\n";
    Swap(h, min, h.posOfLastNode);
    --h.posOfLastNode;
    if (min != 0) {
      SiftUp(h, min);
    }
  }
}

void GetMax(Heap& h) {
  if (h.posOfLastNode == 0) {
    std::cout << "error"
              << "\n";
  } else {
    std::cout << h.arr[1] << "\n";
  }
}

void GetMin(Heap& h) {
  if (h.posOfLastNode == 0) {
    std::cout << "error"
              << "\n";
  } else {
    size_t min = h.posOfLastNode / 2 + 1;
    for (size_t i = h.posOfLastNode / 2 + 2; i <= h.posOfLastNode; ++i) {
      if (h.arr[i] < h.arr[min]) {
        min = i;
      }
    }
    std::cout << h.arr[min] << "\n";
  }
}

void Insert(Heap& h, int n) {
  ++h.posOfLastNode;
  h.arr[h.posOfLastNode] = n;
  SiftUp(h, h.posOfLastNode);
}

size_t LeftChild(size_t pos) {
  return pos << 1;
}

size_t Parent(size_t pos) {
  return pos >> 1;
}

size_t RightChild(size_t pos) {
  return (pos << 1) + 1;
}

void SiftDown(Heap& h, size_t pos) {
  size_t left = LeftChild(pos);
  size_t right = RightChild(pos);
  size_t biggest = pos;
  if ((left <= h.posOfLastNode) && (h.arr[left] > h.arr[biggest])) {
    biggest = left;
  }
  if ((right <= h.posOfLastNode) && (h.arr[right] > h.arr[biggest])) {
    biggest = right;
  }
  if (biggest != pos) {
    Swap(h, pos, biggest);
    SiftDown(h, biggest);
  }
}

void SiftUp(Heap& h, size_t pos) {
  size_t parent = Parent(pos);
  if ((parent >= 1) && (h.arr[pos] > h.arr[parent])) {
    Swap(h, pos, parent);
    SiftUp(h, parent);
  }
}

void Size(Heap& h) {
  std::cout << h.posOfLastNode << "\n";
}

void Swap(Heap& h, size_t first, size_t second) {
  int tmp = h.arr[first];
  h.arr[first] = h.arr[second];
  h.arr[second] = tmp;
}