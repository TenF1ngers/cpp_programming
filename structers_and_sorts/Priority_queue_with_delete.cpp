#include <iostream>

struct PriorityQueue {
  int* heap;
  size_t posOfLastVal;
  size_t size;
};

void Delete(PriorityQueue& pq, size_t idx);
void GetMax(PriorityQueue& pq);
void Insert(PriorityQueue& pq, int val);
size_t LeftChild(size_t pos);
size_t Parent(size_t pos);
size_t RightChild(size_t pos);
void SiftDown(PriorityQueue& pq, size_t pos, size_t& newPos);
void SiftUp(PriorityQueue& pq, size_t pos, size_t& newPos);
void Swap(int& first, int& second);

int main() {
  int n = 0, m = 0;
  std::cin >> n >> m;
  ++n;
  PriorityQueue pq = {nullptr, 0, 0};
  pq.heap = new int[n];
  size_t size = (size_t)n - 1;
  pq.size = size;
  int command = 0, val = 0;
  size_t idx = 0;
  while (m != 0) {
    std::cin >> command;
    switch (command) {
      case 1: {
        GetMax(pq);
        break;
      }
      case 2: {
        std::cin >> val;
        Insert(pq, val);
        break;
      }
      case 3: {
        std::cin >> idx;
        Delete(pq, idx);
        break;
      }
      default: {
        std::cout << "Error!"
                  << "\n";
        break;
      }
    }
    --m;
  }
  for (size_t i = 1; i <= pq.posOfLastVal; ++i) {
    std::cout << pq.heap[i] << " ";
  }
  std::cout << "\n";
  delete[] pq.heap;
  return 0;
}

void Delete(PriorityQueue& pq, size_t idx) {
  if ((idx < 1) || (idx > pq.posOfLastVal)) {
    std::cout << -1 << "\n";
  } else {
    std::cout << pq.heap[idx] << "\n";
    bool isLast = false;
    if (idx == pq.posOfLastVal) {
      isLast = true;
    }
    Swap(pq.heap[idx], pq.heap[pq.posOfLastVal]);
    --pq.posOfLastVal;
    size_t newPos = idx;
    if (!isLast) {
      SiftUp(pq, idx, newPos);
      SiftDown(pq, idx, newPos);
    }
  }
}

void GetMax(PriorityQueue& pq) {
  if (pq.posOfLastVal == 0) {
    std::cout << -1 << "\n";
  } else {
    bool isLast = false;
    if (pq.posOfLastVal == 1) {
      isLast = true;
    }
    int max = pq.heap[1];
    Swap(pq.heap[1], pq.heap[pq.posOfLastVal]);
    size_t newPos = 1;
    --pq.posOfLastVal;
    if (!isLast) {
      SiftDown(pq, 1, newPos);
      std::cout << newPos << " " << max << "\n";
    } else {
      std::cout << 0 << " " << max << "\n";
    }
  }
}

void Insert(PriorityQueue& pq, int val) {
  if (pq.posOfLastVal == pq.size) {
    std::cout << -1 << "\n";
  } else {
    ++pq.posOfLastVal;
    size_t newPos = pq.posOfLastVal;
    pq.heap[pq.posOfLastVal] = val;
    SiftUp(pq, pq.posOfLastVal, newPos);
    std::cout << newPos << "\n";
  }
}

size_t LeftChild(size_t pos) { return pos << 1; }

size_t Parent(size_t pos) { return pos >> 1; }

size_t RightChild(size_t pos) { return (pos << 1) + 1; }

void SiftDown(PriorityQueue& pq, size_t pos, size_t& newPos) {
  size_t left = LeftChild(pos);
  size_t right = RightChild(pos);
  size_t biggest = pos;
  if ((left <= pq.posOfLastVal) && (pq.heap[left] > pq.heap[biggest])) {
    biggest = left;
  }
  if ((right <= pq.posOfLastVal) && (pq.heap[right] > pq.heap[biggest])) {
    biggest = right;
  }
  if (biggest != pos) {
    Swap(pq.heap[pos], pq.heap[biggest]);
    newPos = biggest;
    SiftDown(pq, biggest, newPos);
  }
}

void SiftUp(PriorityQueue& pq, size_t pos, size_t& newPos) {
  size_t parent = Parent(pos);
  if ((parent >= 1) && (pq.heap[pos] > pq.heap[parent])) {
    Swap(pq.heap[pos], pq.heap[parent]);
    newPos = parent;
    SiftUp(pq, parent, newPos);
  }
}

void Swap(int& first, int& second) {
  int tmp = first;
  first = second;
  second = tmp;
}