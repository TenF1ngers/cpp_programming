#include <iostream>

struct Node {
  int val;
  size_t num;
};

struct Heap {
  size_t posOfLastNode;
  size_t countOfNums;
  Node arrOfNodes[200001];
  size_t arrOfNums[200001];
};

void Change(Heap& h, size_t x, int n);
void Clear(Heap& h);
void Delete(Heap& h, size_t x);
void ExtractMin(Heap& h);
void GetMin(Heap& h);
void Insert(Heap& h, int val);
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
  Heap h = {0, 0, {}, {}};
  char command[12], letter2, letter3;
  int m = 0, val = 0, n = 0;
  size_t x = 0;
  std::cin >> m;
  while (m != 0) {
    std::cin >> command;
    letter2 = command[1];
    letter3 = command[2];
    switch (letter2) {
      case 'n': {
        std::cin >> val;
        Insert(h, val);
        std::cout << "ok"
                  << "\n";
        break;
      }
      case 'x': {
        ExtractMin(h);
        break;
      }
      case 'e': {
        if (letter3 == 'l') {
          std::cin >> x;
          Delete(h, x);
        } else {
          GetMin(h);
        }
        break;
      }
      case 'h': {
        std::cin >> x >> n;
        Change(h, x, n);
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

void Change(Heap& h, size_t x, int n) {
  if ((x > h.countOfNums) || (h.arrOfNums[x] == 0)) {
    std::cout << "error"
              << "\n";
  } else {
    h.arrOfNodes[h.arrOfNums[x]].val = n;
    SiftUp(h, h.arrOfNums[x]);
    SiftDown(h, h.arrOfNums[x]);
    std::cout << "ok"
              << "\n";
  }
}

void Clear(Heap& h) {
  for (size_t i = 1; i <= h.posOfLastNode; ++i) {
    h.arrOfNums[h.arrOfNodes[i].num] = 0;
  }
  h.posOfLastNode = 0;
}

void Delete(Heap& h, size_t x) {
  if ((x > h.countOfNums) || (h.arrOfNums[x] == 0)) {
    std::cout << "error"
              << "\n";
  } else {
    size_t numOfChanging = h.arrOfNodes[h.posOfLastNode].num;
    Swap(h, h.arrOfNums[x], h.posOfLastNode);
    h.arrOfNums[h.arrOfNodes[h.posOfLastNode].num] = 0;
    --h.posOfLastNode;
    if (h.arrOfNums[numOfChanging] != 0) {
      SiftUp(h, h.arrOfNums[numOfChanging]);
      SiftDown(h, h.arrOfNums[numOfChanging]);
    }
    std::cout << "ok"
              << "\n";
  }
}

void ExtractMin(Heap& h) {
  if (h.posOfLastNode == 0) {
    std::cout << "error"
              << "\n";
  } else {
    size_t min = h.posOfLastNode / 2 + 1;
    for (size_t i = h.posOfLastNode / 2 + 2; i <= h.posOfLastNode; ++i) {
      if (h.arrOfNodes[i].val < h.arrOfNodes[min].val) {
        min = i;
      }
    }
    std::cout << h.arrOfNodes[min].val << "\n";
    Swap(h, min, h.posOfLastNode);
    h.arrOfNums[h.arrOfNodes[h.posOfLastNode].num] = 0;
    --h.posOfLastNode;
    if (h.arrOfNums[h.arrOfNodes[min].num] != 0) {
      SiftUp(h, min);
    }
  }
}

void GetMin(Heap& h) {
  if (h.posOfLastNode == 0) {
    std::cout << "error"
              << "\n";
  } else {
    size_t min = h.posOfLastNode / 2 + 1;
    for (size_t i = h.posOfLastNode / 2 + 2; i <= h.posOfLastNode; ++i) {
      if (h.arrOfNodes[i].val < h.arrOfNodes[min].val) {
        min = i;
      }
    }
    std::cout << h.arrOfNodes[min].val << "\n";
  }
}

void Insert(Heap& h, int val) {
  ++h.posOfLastNode;
  ++h.countOfNums;
  h.arrOfNodes[h.posOfLastNode].val = val;
  h.arrOfNodes[h.posOfLastNode].num = h.countOfNums;
  h.arrOfNums[h.countOfNums] = h.posOfLastNode;
  SiftUp(h, h.posOfLastNode);
}

size_t LeftChild(size_t pos) {
  return pos * 2;
}

size_t Parent(size_t pos) {
  return pos / 2;
}

size_t RightChild(size_t pos) {
  return pos * 2 + 1;
}

void SiftDown(Heap& h, size_t pos) {
  size_t left = LeftChild(pos);
  size_t right = RightChild(pos);
  size_t biggest = pos;
  if ((left <= h.posOfLastNode) && (h.arrOfNodes[left].val > h.arrOfNodes[biggest].val)) {
    biggest = left;
  }
  if ((right <= h.posOfLastNode) && (h.arrOfNodes[right].val > h.arrOfNodes[biggest].val)) {
    biggest = right;
  }
  if (biggest != pos) {
    Swap(h, pos, biggest);
    SiftDown(h, biggest);
  }
}

void SiftUp(Heap& h, size_t pos) {
  size_t parent = Parent(pos);
  if ((parent >= 1) && (h.arrOfNodes[pos].val > h.arrOfNodes[parent].val)) {
    Swap(h, pos, parent);
    SiftUp(h, parent);
  }
}

void Size(Heap& h) {
  std::cout << h.posOfLastNode << "\n";
}

void Swap(Heap& h, size_t first, size_t second) {
  int tmp1 = h.arrOfNodes[first].val;
  h.arrOfNodes[first].val = h.arrOfNodes[second].val;
  h.arrOfNodes[second].val = tmp1;
  size_t tmp2 = h.arrOfNodes[first].num;
  h.arrOfNodes[first].num = h.arrOfNodes[second].num;
  h.arrOfNodes[second].num = tmp2;
  tmp2 = h.arrOfNums[h.arrOfNodes[first].num];
  h.arrOfNums[h.arrOfNodes[first].num] = h.arrOfNums[h.arrOfNodes[second].num];
  h.arrOfNums[h.arrOfNodes[second].num] = tmp2;
}