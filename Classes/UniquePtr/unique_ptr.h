#pragma once

template <class T>
void Swap(T& first, T& second) {
  T tmp = std::move(first);
  first = std::move(second);
  second = std::move(tmp);
}

template <class T>
class UniquePtr {
 private:
  T* ptr_;

 public:
  UniquePtr(const UniquePtr& other) = delete;
  UniquePtr& operator=(const UniquePtr& other) = delete;

  UniquePtr() : ptr_(nullptr) {
  }

  explicit UniquePtr(T* other) : ptr_(other) {
  }

  UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
      Swap(this->ptr_, other->ptr_);
    }
    return *this;
  }

  T* Release() {
    T* tmp = this->ptr_;
    this->ptr_ = nullptr;
    return tmp;
  }

  void Reset(T* other = nullptr) {
    if (this->ptr_ != other) {
      delete this->ptr_;
      this->ptr_ = other;
    }
  }

  void Swap(UniquePtr<T>& other) {
    UniquePtr<T> tmp = std::move(other);
    other = std::move(*this);
    *this = std::move(tmp);
  }

  T* Get() const {
    return this->ptr_;
  }

  T& operator*() const {
    return *(this->ptr_);
  }

  T* operator->() const {
    return this->ptr_;
  }

  explicit operator bool() const {
    bool flag = false;
    if (this->ptr_ != nullptr) {
      flag = true;
    }
    return flag;
  }

  ~UniquePtr() {
    delete this->ptr_;
  }
};