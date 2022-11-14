#ifndef ARRAY__TASK__HEADER_H
#define ARRAY__TASK__HEADER_H
#define ARRAY_TRAITS_IMPLEMENTED

#include <iostream>
#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <class T>
void Swap2(T& first, T& second) {
  T temp = first;
  first = second;
  second = temp;
}

template <class T, size_t N>
class Array {
 public:
  T array[N];

  T& operator[](size_t idx) {
    return array[idx];
  }

  const T& operator[](size_t idx) const {
    return array[idx];
  }

  T& At(size_t idx) {
    if ((N - 1 < idx) || (N < 0)) {
      throw ArrayOutOfRange{};
    }
    return array[idx];
  }

  const T& At(size_t idx) const {
    if ((N - 1 < idx) || (N < 0)) {
      throw ArrayOutOfRange{};
    }
    return array[idx];
  }

  T& Front() {
    return array[0];
  }

  const T& Front() const {
    return array[0];
  }

  T& Back() {
    return array[N - 1];
  }

  const T& Back() const {
    return array[N - 1];
  }

  T* Data() {
    return array;
  }

  const T* Data() const {
    return array;
  }

  size_t Size() {
    return N;
  }

  size_t Size() const {
    return N;
  }

  bool Empty() {
    bool flag = false;
    if (N == 0) {
      flag = true;
    }
    return flag;
  }

  bool Empty() const {
    bool flag = false;
    if (N == 0) {
      flag = true;
    }
    return flag;
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      array[i] = value;
    }
  }

  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
      Swap2(array[i], other[i]);
    }
  }
};

template <class T>
size_t GetSize(const T& var) {
  return 0;
}

template <class T, size_t N>
size_t GetSize(T (&arr)[N]) {
  return sizeof(arr) / sizeof(T);
}

template <class T>
size_t GetRank(const T& var) {
  return 0;
}

template <class T, size_t N>
size_t GetRank(T (&arr)[N]) {
  return 1 + GetRank(arr[0]);
}

template <class T>
size_t GetNumElements(const T& var) {
  return 1;
}

template <class T, size_t N>
size_t GetNumElements(T (&arr)[N]) {
  return GetSize(arr) * GetNumElements(arr[0]);
}

#endif  // ARRAY__TASK__HEADER_H
