#pragma once

#include <stdexcept>

#define WEAK_PTR_IMPLEMENTED

class BadWeakPtr : public std::runtime_error {
 public:
  BadWeakPtr() : std::runtime_error("BadWeakPtr") {
  }
};

class Counter {
 public:
  int strong_count;
  int weak_count;
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
 private:
  T* ptr_;
  Counter* counter_;

 public:
  SharedPtr() : ptr_(nullptr), counter_(nullptr) {
  }

  SharedPtr(T* other_ptr) : ptr_(other_ptr), counter_(nullptr) {  //  NOLINT
    if (this->ptr_) {
      this->counter_ = new Counter{1, 0};
      std::cout << ptr_ << " " << counter_->strong_count << " " << counter_->weak_count << "\n";
    }
  }

  SharedPtr(const SharedPtr<T>& other) : ptr_(other.ptr_), counter_(other.counter_) {
    if (this->ptr_) {
      ++(this->counter_->strong_count);
    }
  }

  SharedPtr(SharedPtr<T>&& other) noexcept : ptr_(other.ptr_), counter_(other.counter_) {
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
  }

  SharedPtr(const WeakPtr<T>& other) : ptr_(other.Get()), counter_(other.GetCounter()) {  //  NOLINT
    if (other.Expired()) {
      throw BadWeakPtr{};
    }
    ++(this->counter_->strong_count);
  }

  SharedPtr& operator=(const SharedPtr<T>& other) {
    if (this->ptr_ != other.ptr_) {
      this->Delete();
      this->ptr_ = other.ptr_;
      this->counter_ = other.counter_;
      if (this->ptr_) {
        ++(this->counter_->strong_count);
      }
    }
    return *this;
  }

  SharedPtr& operator=(SharedPtr<T>&& other) noexcept {
    if (other.ptr_ != this->ptr_) {
      this->Delete();
      this->ptr_ = other.ptr_;
      this->counter_ = other.counter_;
    } else {
      if (this->ptr_) {
        --(this->counter_->strong_count);
      }
    }
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
    return *this;
  }

  SharedPtr& operator=(T* other_ptr) {
    this->Delete();
    this->ptr_ = other_ptr;
    if (this->ptr_) {
      this->counter_ = new Counter{1, 0};
    } else {
      this->counter_ = nullptr;
    }
    return *this;
  }

  void Reset(T* other_ptr = nullptr) {
    this->Delete();
    this->ptr_ = other_ptr;
    if (this->ptr_) {
      this->counter_ = new Counter{1, 0};
    } else {
      this->counter_ = nullptr;
    }
  }

  void Swap(SharedPtr<T>& other) {
    SharedPtr tmp = std::move(other);
    other = std::move(*this);
    *this = std::move(tmp);
  }

  T* Get() const {
    return this->ptr_;
  }

  Counter* GetCounter() const {
    return this->counter_;
  }

  int UseCount() const {
    int count = 0;
    if (this->counter_) {
      count = this->counter_->strong_count;
    }
    return count;
  }

  T& operator*() const {
    return *(this->ptr_);
  }

  T* operator->() const {
    return this->ptr_;
  }

  explicit operator bool() const {
    bool flag = false;
    if (this->ptr_) {
      flag = true;
    }
    return flag;
  }

  void Delete() {
    if (this->ptr_) {
      --(this->counter_->strong_count);
      if ((this->counter_->strong_count == 0) && (this->counter_->weak_count == 0)) {
        delete this->ptr_;
        delete this->counter_;
      } else if (this->counter_->strong_count == 0) {
        delete this->ptr_;
      }
    }
  }

  ~SharedPtr() {
    this->Delete();
    this->ptr_ = nullptr;
    this->counter_ = nullptr;
  }
};

template <class T>
class WeakPtr {
 private:
  T* ptr_;
  Counter* counter_;

 public:
  WeakPtr() : ptr_(nullptr), counter_(nullptr) {
  }

  WeakPtr(T* other_ptr) : ptr_(other_ptr), counter_(nullptr) {                            //  NOLINT
    if (this->ptr_) {
      counter_ = new Counter{0, 1};
    }
  }

  WeakPtr(const SharedPtr<T>& other) : ptr_(other.Get()), counter_(other.GetCounter()) {  //  NOLINT
    if (this->counter_) {
      ++(this->counter_->weak_count);
      std::cout << ptr_ << " " << counter_->strong_count << " " << counter_->weak_count << "\n";
    }
  }

  WeakPtr(const WeakPtr<T>& other) : ptr_(other.ptr_), counter_(other.counter_) {
    if (this->ptr_) {
      ++(this->counter_->weak_count);
    }
  }

  WeakPtr(WeakPtr<T>&& other) noexcept : ptr_(other.ptr_), counter_(other.counter_) {
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
  }

  WeakPtr& operator=(const WeakPtr<T>& other) {
    if (this->ptr_ != other.ptr_) {
      if (this->ptr_) {
        --(this->counter_->weak_count);
      }
      this->ptr_ = other.ptr_;
      this->counter_ = other.counter_;
      ++(this->counter_->weak_count);
    }
    return *this;
  }

  WeakPtr& operator=(WeakPtr<T>&& other) noexcept {
    if (this->ptr_ != other.ptr_) {
      if (this->ptr_) {
        --(this->counter_->weak_count);
      }
      this->ptr_ = other.ptr_;
      this->counter_ = other.counter_;
    } else {
      if (this->ptr_) {
        --(this->counter_->weak_count);
      }
    }
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
    return *this;
  }

  void Swap(WeakPtr<T>& other) {
    WeakPtr<T> tmp = std::move(other);
    other = std::move(*this);
    *this = std::move(tmp);
  }

  void Reset() {
    if (this->counter_) {
      --(this->counter_->weak_count);
    }
    this->ptr_ = nullptr;
    this->counter_ = nullptr;
  }

  T* Get() const {
    return this->ptr_;
  }

  Counter* GetCounter() const {
    return this->counter_;
  }

  int UseCount() const {
    int count = 0;
    if (this->counter_) {
      count = this->counter_->strong_count;
    }
    return count;
  }

  bool Expired() const {
    bool flag = false;
    if (this->UseCount() == 0) {
      flag = true;
    }
    return flag;
  }

  SharedPtr<T> Lock() const {
    if (this->Expired()) {
      return SharedPtr<T>(nullptr);
    } else {
      return SharedPtr<T>(*this);
    }
  }

  ~WeakPtr() {
    if (this->counter_) {
      --(this->counter_->weak_count);
      if ((this->counter_->strong_count == 0) && (this->counter_->weak_count == 0)) {
        delete this->counter_;
      }
    }
    this->ptr_ = nullptr;
    this->counter_ = nullptr;
  }
};

template <class T, class... Args>
SharedPtr<T> MakeShared(Args&&... args) {
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}