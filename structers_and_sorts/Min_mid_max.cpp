// Реализуйте структуру данных для хранения различных целых чисел, которая
// поддерживает 4 операции:

// «add x> — Добавить в структуру элемент x (1 ≤ x ≤ 109);

// «min» — Извлечь из структуры минимальный элемент;

// «max» — Извлечь из структуры максимальный элемент;

// «mid» — Извлечь из структуры медианный элемент

#include <iostream>

struct Heap {
  int arr[200001];
  size_t posOfLastNode;
};

void Add(Heap& h, int n);
void ExtractMax(Heap& h);
void ExtractMid(Heap& h);
void ExtractMin(Heap& h);
size_t LeftChild(size_t pos);
size_t Parent(size_t pos);
size_t RightChild(size_t pos);
void SiftDown(Heap& h, size_t pos);
void SiftUp(Heap& h, size_t pos);
void Swap(Heap& h, size_t first, size_t second);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Heap h = {{}, 0};
  char command[4], letter1, letter3;
  int m = 0, n = 0;
  std::cin >> m;
  while (m != 0) {
    std::cin >> command;
    letter1 = command[0];
    switch (letter1) {
      case 'a': {
        std::cin >> n;
        Add(h, n);
        break;
      }
      case 'm': {
        letter3 = command[2];
        if (letter3 == 'x') {
          ExtractMax(h);
        } else if (letter3 == 'n') {
          ExtractMin(h);
        } else {
          ExtractMid(h);
        }
        break;
      }
    }
    --m;
  }
  return 0;
}

void Add(Heap& h, int n) {
  ++h.posOfLastNode;
  h.arr[h.posOfLastNode] = n;
  SiftUp(h, h.posOfLastNode);
}

void ExtractMax(Heap& h) {
  if (h.posOfLastNode != 0) {
    std::cout << h.arr[1] << "\n";
    Swap(h, 1, h.posOfLastNode);
    --h.posOfLastNode;
    if (h.posOfLastNode != 0) {
      SiftDown(h, 1);
    }
  }
}

void ExtractMid(Heap& h) {
  if (h.posOfLastNode != 0) {
    if (h.posOfLastNode % 2 == 0) {
      size_t mid = h.posOfLastNode / 2;
      std::cout << h.arr[mid] << "\n";
      Swap(h, mid, h.posOfLastNode);
      --h.posOfLastNode;
      if (h.posOfLastNode != 0) {
        SiftUp(h, mid);
        SiftDown(h, mid);
      }
    } else {
      size_t mid = h.posOfLastNode / 2 + 1;
      std::cout << h.arr[mid] << "\n";
      Swap(h, mid, h.posOfLastNode);
      --h.posOfLastNode;
      if (h.posOfLastNode != 0) {
        SiftUp(h, mid);
        SiftDown(h, mid);
      }
    }
  }
}

void ExtractMin(Heap& h) {
  if (h.posOfLastNode != 0) {
    size_t min = h.posOfLastNode / 2 + 1;
    for (size_t i = h.posOfLastNode / 2 + 2; i <= h.posOfLastNode; ++i) {
      if (h.arr[i] < h.arr[min]) {
        min = i;
      }
    }
    std::cout << h.arr[min] << "\n";
    Swap(h, min, h.posOfLastNode);
    --h.posOfLastNode;
    if (h.posOfLastNode != 0) {
      SiftUp(h, min);
    }
  }
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

void Swap(Heap& h, size_t first, size_t second) {
  int tmp = h.arr[first];
  h.arr[first] = h.arr[second];
  h.arr[second] = tmp;
}