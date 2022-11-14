#pragma once

#define VECTOR_MEMORY_IMPLEMENTED

#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>

class OutOfRange : public std::out_of_range {
 public:
  OutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <class T>
class Vector {
 private:
  size_t size_;
  size_t capacity_;
  T* begin_;

 public:
  using ValueType = T;
  using SizeType = size_t;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;

  using Iterator = T*;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstIterator = const T*;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  Iterator begin() noexcept;             //  NOLINT
  ConstIterator begin() const noexcept;  //  NOLINT

  ConstIterator cbegin() const noexcept;  //  NOLINT
  ConstIterator cend() const noexcept;    //  NOLINT

  Iterator end() noexcept;             //  NOLINT
  ConstIterator end() const noexcept;  //  NOLINT

  ReverseIterator rbegin() noexcept;             //  NOLINT
  ConstReverseIterator rbegin() const noexcept;  //  NOLINT

  ConstReverseIterator crbegin() const noexcept;  //  NOLINT
  ConstReverseIterator crend() const noexcept;    //  NOLINT

  ReverseIterator rend() noexcept;             //  NOLINT
  ConstReverseIterator rend() const noexcept;  //  NOLINT

  const T& At(const size_t& pos) const;
  T& At(const size_t& pos);

  const T& Back() const noexcept;
  T& Back() noexcept;

  [[nodiscard]] size_t Capacity() const noexcept;

  void Clear() noexcept;

  const T* Data() const noexcept;
  T* Data() noexcept;

  template <class... Args>
  void EmplaceBack(Args&&... args) {
    if (size_ == capacity_) {
      T* new_begin = (capacity_ != 0) ? static_cast<T*>(operator new(sizeof(T) * capacity_ * 2))
                                      : static_cast<T*>(operator new(sizeof(T)));

      size_t count = 0;
      try {
        for (size_t i = 0; i < size_; ++i) {
          new (new_begin + i) T(std::move_if_noexcept(begin_[i]));

          ++count;
        }
        new (new_begin + size_) T(std::forward<Args>(args)...);

        ++count;
      } catch (...) {
        for (size_t j = 0; j < count; ++j) {
          (new_begin + j)->~T();
        }
        operator delete(new_begin);

        throw;
      }
      for (size_t i = 0; i < size_; ++i) {
        (begin_ + i)->~T();
      }
      operator delete(begin_);

      begin_ = new_begin;
      ++size_;
      if (capacity_ != 0) {
        capacity_ *= 2;
      } else {
        capacity_ = 1;
      }
    } else {
      ++size_;
      try {
        new (begin_ + size_ - 1) T(std::forward<Args>(args)...);
      } catch (...) {
        (begin_ + size_ - 1)->~T();

        --size_;

        throw;
      }
    }
  }

  [[nodiscard]] bool Empty() const noexcept;

  const T& Front() const noexcept;
  T& Front() noexcept;

  void PopBack() noexcept;
  void PushBack(const T& extra_val);
  void PushBack(T&& extra_val);

  void Reserve(const size_t& new_cap);

  void Resize(const size_t& new_size);
  void Resize(const size_t& new_size, const T& value);

  void ShrinkToFit();

  [[nodiscard]] size_t Size() const noexcept;

  void Swap(Vector& other) noexcept;

  Vector() noexcept;
  explicit Vector(const size_t& new_size);
  Vector(const size_t& new_size, const T& value);
  Vector(std::initializer_list<T> list);  //  NOLINT
  Vector(const Vector<T>& other);
  Vector(Vector<T>&& other) noexcept;

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator first, Iterator second) {
    size_t count = 0;
    if (first != second) {
      for (auto it = first; it != second; ++it) {
        ++count;
      }
    }

    size_ = count;
    capacity_ = count;

    begin_ = (capacity_ != 0) ? static_cast<T*>(operator new(sizeof(T) * capacity_)) : nullptr;

    auto it = first;
    count = 0;
    try {
      for (size_t i = 0; i < size_; ++i) {
        new (begin_ + i) T(*it);

        ++it;
        ++count;
      }
    } catch (...) {
      for (size_t i = 0; i < count; ++i) {
        (begin_ + i)->~T();
      }
      operator delete(begin_);

      throw;
    }
  }

  ~Vector();

  const T& operator[](const size_t& pos) const noexcept;
  T& operator[](const size_t& pos) noexcept;

  Vector<T>& operator=(const Vector<T>& other);
  Vector<T>& operator=(Vector<T>&& other) noexcept;

 private:
  void SetCapacity(const size_t& new_cap);
};

template <class T>
typename Vector<T>::Iterator Vector<T>::begin() noexcept {  //  NOLINT
  return begin_;
}

template <class T>
typename Vector<T>::ConstIterator Vector<T>::begin() const noexcept {  //  NOLINT
  return begin_;
}

template <class T>
typename Vector<T>::ConstIterator Vector<T>::cbegin() const noexcept {  //  NOLINT
  return begin_;
}

template <class T>
typename Vector<T>::ConstIterator Vector<T>::cend() const noexcept {  //  NOLINT
  return begin_ + size_;
}

template <class T>
typename Vector<T>::Iterator Vector<T>::end() noexcept {  //  NOLINT
  return begin_ + size_;
}

template <class T>
typename Vector<T>::ConstIterator Vector<T>::end() const noexcept {  //  NOLINT
  return begin_ + size_;
}

template <class T>
typename Vector<T>::ReverseIterator Vector<T>::rbegin() noexcept {  //  NOLINT
  return std::reverse_iterator(this->end());
}

template <class T>
typename Vector<T>::ConstReverseIterator Vector<T>::rbegin() const noexcept {  //  NOLINT
  return std::reverse_iterator(this->end());
}

template <class T>
typename Vector<T>::ConstReverseIterator Vector<T>::crbegin() const noexcept {  //  NOLINT
  return std::reverse_iterator(this->cend());
}

template <class T>
typename Vector<T>::ConstReverseIterator Vector<T>::crend() const noexcept {  //  NOLINT
  return std::reverse_iterator(this->cbegin());
}

template <class T>
typename Vector<T>::ReverseIterator Vector<T>::rend() noexcept {  //  NOLINT
  return std::reverse_iterator(this->begin());
}

template <class T>
typename Vector<T>::ConstReverseIterator Vector<T>::rend() const noexcept {  //  NOLINT
  return std::reverse_iterator(this->begin());
}

template <class T>
const T& Vector<T>::At(const size_t& pos) const {
  if (pos > size_ - 1) {
    throw OutOfRange{};
  }
  return begin_[pos];
}

template <class T>
T& Vector<T>::At(const size_t& pos) {
  if (pos > size_ - 1) {
    throw OutOfRange{};
  }
  return begin_[pos];
}

template <class T>
const T& Vector<T>::Back() const noexcept {
  return begin_[size_ - 1];
}

template <class T>
T& Vector<T>::Back() noexcept {
  return begin_[size_ - 1];
}

template <class T>
size_t Vector<T>::Capacity() const noexcept {
  return capacity_;
}

template <class T>
void Vector<T>::Clear() noexcept {
  for (size_t i = 0; i < size_; ++i) {
    (begin_ + i)->~T();
  }
  size_ = 0;
}

template <class T>
const T* Vector<T>::Data() const noexcept {
  return begin_;
}

template <class T>
T* Vector<T>::Data() noexcept {
  return begin_;
}

template <class T>
bool Vector<T>::Empty() const noexcept {
  return size_ == 0;
}

template <class T>
const T& Vector<T>::Front() const noexcept {
  return begin_[0];
}

template <class T>
T& Vector<T>::Front() noexcept {
  return begin_[0];
}

template <class T>
void Vector<T>::PopBack() noexcept {
  if (size_ != 0) {
    (begin_ + size_ - 1)->~T();
    --size_;
  }
}

template <class T>
void Vector<T>::PushBack(const T& extra_val) {
  if (size_ == capacity_) {
    auto new_begin = (capacity_ != 0) ? static_cast<T*>(operator new(sizeof(T) * capacity_ * 2))
                                      : static_cast<T*>(operator new(sizeof(T)));

    size_t count = 0;
    try {
      for (size_t i = 0; i < size_; ++i) {
        new (new_begin + i) T(std::move_if_noexcept(begin_[i]));

        ++count;
      }
      new (new_begin + size_) T(extra_val);

      ++count;
    } catch (...) {
      for (size_t j = 0; j < count; ++j) {
        (new_begin + j)->~T();
      }
      operator delete(new_begin);

      throw;
    }
    for (size_t i = 0; i < size_; ++i) {
      (begin_ + i)->~T();
    }
    operator delete(begin_);

    begin_ = new_begin;
    ++size_;
    if (capacity_ != 0) {
      capacity_ *= 2;
    } else {
      capacity_ = 1;
    }
  } else {
    ++size_;

    try {
      new (begin_ + size_ - 1) T(extra_val);
    } catch (...) {
      (begin_ + size_ - 1)->~T();
      --size_;

      throw;
    }
  }
}

template <class T>
void Vector<T>::PushBack(T&& extra_val) {
  if (size_ == capacity_) {
    auto new_begin = (capacity_ != 0) ? static_cast<T*>(operator new(sizeof(T) * capacity_ * 2))
                                      : static_cast<T*>(operator new(sizeof(T)));

    size_t count = 0;
    try {
      for (size_t i = 0; i < size_; ++i) {
        new (new_begin + i) T(std::move_if_noexcept(begin_[i]));

        ++count;
      }
      new (new_begin + size_) T(std::move(extra_val));

      ++count;
    } catch (...) {
      for (size_t j = 0; j < count; ++j) {
        (new_begin + j)->~T();
      }
      operator delete(new_begin);

      throw;
    }
    for (size_t i = 0; i < size_; ++i) {
      (begin_ + i)->~T();
    }
    operator delete(begin_);

    begin_ = new_begin;
    ++size_;
    if (capacity_ != 0) {
      capacity_ *= 2;
    } else {
      capacity_ = 1;
    }
  } else {
    ++size_;

    try {
      new (begin_ + size_ - 1) T(std::move(extra_val));
    } catch (...) {
      (begin_ + size_ - 1)->~T();
      --size_;

      throw;
    }
  }
}

template <class T>
void Vector<T>::Reserve(const size_t& new_cap) {
  if (capacity_ < new_cap) {
    auto new_begin = static_cast<T*>(operator new(sizeof(T) * new_cap));

    size_t count = 0;
    try {
      for (size_t i = 0; i < size_; ++i) {
        new (new_begin + i) T(std::move_if_noexcept(begin_[i]));

        ++count;
      }
    } catch (...) {
      for (size_t i = 0; i < count; ++i) {
        (new_begin + i)->~T();
      }
      operator delete(new_begin);

      throw;
    }
    for (size_t i = 0; i < size_; ++i) {
      (begin_ + i)->~T();
    }
    operator delete(begin_);

    begin_ = new_begin;
    capacity_ = new_cap;
  }
}

template <class T>
void Vector<T>::Resize(const size_t& new_size) {
  size_t count = 0;
  if (new_size > capacity_) {
    auto new_begin = static_cast<T*>(operator new(sizeof(T) * new_size));

    try {
      for (size_t i = 0; i < size_; ++i) {
        new (new_begin + i) T(std::move_if_noexcept(begin_[i]));

        ++count;
      }
      for (size_t i = size_; i < new_size; ++i) {
        new (new_begin + i) T;

        ++count;
      }
    } catch (...) {
      for (size_t j = 0; j < count; ++j) {
        (new_begin + j)->~T();
      }
      operator delete(new_begin);

      throw;
    }
    for (size_t i = 0; i < size_; ++i) {
      (begin_ + i)->~T();
    }
    operator delete(begin_);

    begin_ = new_begin;
    capacity_ = new_size;
  } else {
    if (size_ < new_size) {
      try {
        for (size_t i = size_; i < new_size; ++i) {
          new (begin_ + i) T;

          ++count;
        }
      } catch (...) {
        for (size_t j = size_; j < size_ + count; ++j) {
          (begin_ + j)->~T();
        }

        throw;
      }
    } else {
      for (size_t i = new_size; i < size_; ++i) {
        (begin_ + i)->~T();
      }
    }
  }
  size_ = new_size;
}

template <class T>
void Vector<T>::Resize(const size_t& new_size, const T& value) {
  size_t count = 0;
  if (new_size > capacity_) {
    auto new_begin = static_cast<T*>(operator new(sizeof(T) * new_size));

    try {
      for (size_t i = 0; i < size_; ++i) {
        new (new_begin + i) T(std::move_if_noexcept(begin_[i]));

        ++count;
      }
      for (size_t i = size_; i < new_size; ++i) {
        new (new_begin + i) T(value);

        ++count;
      }
    } catch (...) {
      for (size_t j = 0; j < count; ++j) {
        (new_begin + j)->~T();
      }
      operator delete(new_begin);

      throw;
    }
    for (size_t i = 0; i < size_; ++i) {
      (begin_ + i)->~T();
    }
    operator delete(begin_);

    begin_ = new_begin;
    capacity_ = new_size;
  } else {
    if (size_ < new_size) {
      try {
        for (size_t i = size_; i < new_size; ++i) {
          new (begin_ + i) T(value);

          ++count;
        }
      } catch (...) {
        for (size_t j = size_; j < size_ + count; ++j) {
          (begin_ + j)->~T();
        }

        throw;
      }
    } else {
      for (size_t i = new_size; i < size_; ++i) {
        (begin_ + i)->~T();
      }
    }
  }
  size_ = new_size;
}

template <class T>
void Vector<T>::ShrinkToFit() {
  try {
    this->SetCapacity(size_);
  } catch (...) {
    throw;
  }
}

template <class T>
size_t Vector<T>::Size() const noexcept {
  return size_;
}

template <class T>
void Vector<T>::Swap(Vector& other) noexcept {
  Vector<T> tmp = std::move(*this);
  *this = std::move(other);
  other = std::move(tmp);
}

template <class T>
Vector<T>::Vector() noexcept : size_(0), capacity_(0), begin_(nullptr) {
}

template <class T>
Vector<T>::Vector(const size_t& new_size)
        : size_(new_size)
        , capacity_(new_size)
        , begin_((new_size != 0) ? static_cast<T*>(operator new(sizeof(T) * new_size)) : nullptr) {
  size_t count = 0;
  try {
    for (size_t i = 0; i < size_; ++i) {
      new (begin_ + i) T;

      ++count;
    }
  } catch (...) {
    for (size_t j = 0; j < count; ++j) {
      (begin_ + j)->~T();
    }
    operator delete(begin_);

    throw;
  }
}

template <class T>
Vector<T>::Vector(const size_t& new_size, const T& value)
        : size_(new_size)
        , capacity_(new_size)
        , begin_((new_size != 0) ? static_cast<T*>(operator new(sizeof(T) * new_size)) : nullptr) {
  size_t count = 0;
  try {
    for (size_t i = 0; i < size_; ++i) {
      new (begin_ + i) T(value);

      ++count;
    }
  } catch (...) {
    for (size_t j = 0; j < count; ++j) {
      (begin_ + j)->~T();
    }
    operator delete(begin_);

    throw;
  }
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> list)
        : size_(list.size())
        , capacity_(list.size())
        , begin_((list.size() != 0) ? static_cast<T*>(operator new(sizeof(T) * list.size())) : nullptr) {
  T* it = begin_;
  size_t count = 0;
  try {
    for (auto& element : list) {
      new (it) T(element);

      ++it;
      ++count;
    }
  } catch (...) {
    it = begin_;

    while (count-- != 0) {
      it->~T();

      ++it;
    }
    operator delete(begin_);

    throw;
  }
}

template <class T>
Vector<T>::Vector(const Vector<T>& other)
        : size_(other.size_)
        , capacity_(other.size_)
        , begin_((other.capacity_ != 0) ? static_cast<T*>(operator new(sizeof(T) * other.capacity_)) : nullptr) {
  size_t count = 0;
  try {
    for (size_t i = 0; i < other.Size(); ++i) {
      new (begin_ + i) T(other[i]);

      ++count;
    }
  } catch (...) {
    for (size_t j = 0; j < count; ++j) {
      (begin_ + j)->~T();
    }
    operator delete(begin_);

    throw;
  }
}

template <class T>
Vector<T>::Vector(Vector<T>&& other) noexcept
        : size_(other.size_), capacity_(other.capacity_), begin_(std::move(other.begin_)) {
  other.begin_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <class T>
Vector<T>::~Vector() {
  for (size_t i = 0; i < size_; ++i) {
    (begin_ + i)->~T();
  }
  operator delete(begin_);
}

template <class T>
const T& Vector<T>::operator[](const size_t& pos) const noexcept {
  return *(begin_ + pos);
}

template <class T>
T& Vector<T>::operator[](const size_t& pos) noexcept {
  return *(begin_ + pos);
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
  T* new_begin = (other.capacity_ != 0) ? static_cast<T*>(operator new(sizeof(T) * other.capacity_)) : nullptr;

  size_t count = 0;
  try {
    for (size_t i = 0; i < other.size_; ++i) {
      new (new_begin + i) T(other[i]);

      ++count;
    }
  } catch (...) {
    for (size_t i = 0; i < count; ++i) {
      (new_begin + i)->~T();
    }
    operator delete(new_begin);

    throw;
  }
  for (size_t i = 0; i < size_; ++i) {
    (begin_ + i)->~T();
  }
  operator delete(begin_);

  begin_ = new_begin;
  capacity_ = other.capacity_;
  size_ = other.size_;

  return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept {
  this->Clear();
  operator delete(begin_);

  begin_ = std::move(other.begin_);
  size_ = other.size_;
  capacity_ = other.capacity_;

  other.size_ = 0;
  other.capacity_ = 0;
  other.begin_ = nullptr;

  return *this;
}

template <class T>
void Vector<T>::SetCapacity(const size_t& new_cap) {
  T* new_begin = (new_cap != 0) ? static_cast<T*>(operator new(sizeof(T) * new_cap)) : nullptr;

  size_t new_size = std::min(new_cap, size_);
  size_t count = 0;
  try {
    for (size_t i = 0; i < new_size; ++i) {
      new (new_begin + i) T(std::move_if_noexcept(begin_[i]));

      ++count;
    }
  } catch (...) {
    for (size_t j = 0; j < count; ++j) {
      (new_begin + j)->~T();
    }
    operator delete(new_begin);

    throw;
  }
  for (size_t i = 0; i < size_; ++i) {
    (begin_ + i)->~T();
  }
  operator delete(begin_);

  if (new_cap < size_) {
    size_ = new_cap;
  }
  begin_ = new_begin;
  capacity_ = new_cap;
}

template <class T>
bool operator<(const Vector<T>& first, const Vector<T>& second) noexcept {
  bool is_lower = false;
  size_t count_of_equal = 0;
  size_t min_size = std::min(first.Size(), second.Size());
  for (size_t i = 0; i < min_size; ++i) {
    if (first[i] < second[i]) {
      is_lower = true;

      break;
    }

    if (first[i] == second[i]) {
      ++count_of_equal;

      continue;
    }

    break;
  }
  if (!is_lower && (count_of_equal == min_size)) {
    if (first.Size() < second.Size()) {
      is_lower = true;
    }
  }
  return is_lower;
}

template <class T>
bool operator>(const Vector<T>& first, const Vector<T>& second) noexcept {
  bool is_greater = false;
  size_t count_of_equal = 0;
  size_t min_size = std::min(first.Size(), second.Size());
  for (size_t i = 0; i < min_size; ++i) {
    if (first[i] > second[i]) {
      is_greater = true;

      break;
    }

    if (first[i] == second[i]) {
      ++count_of_equal;

      continue;
    }

    break;
  }
  if (!is_greater && (count_of_equal == min_size)) {
    if (first.Size() > second.Size()) {
      is_greater = true;
    }
  }
  return is_greater;
}

template <class T>
bool operator<=(const Vector<T>& first, const Vector<T>& second) noexcept {
  return !(first > second);
}

template <class T>
bool operator>=(const Vector<T>& first, const Vector<T>& second) noexcept {
  return !(first < second);
}

template <class T>
bool operator==(const Vector<T>& first, const Vector<T>& second) noexcept {
  bool is_equal = false;
  if (first.Size() == second.Size()) {
    size_t count_of_equal = 0;
    for (size_t i = 0; i < first.Size(); ++i) {
      if (first[i] == second[i]) {
        ++count_of_equal;

        continue;
      }

      break;
    }
    if (count_of_equal == first.Size()) {
      is_equal = true;
    }
  }
  return is_equal;
}

template <class T>
bool operator!=(const Vector<T>& first, const Vector<T>& second) noexcept {
  return !(first == second);
}