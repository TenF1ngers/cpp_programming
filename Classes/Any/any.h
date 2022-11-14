#pragma once

#include <stdexcept>
#include <memory>

class BadAnyCast : public std::bad_cast {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "BadAnyCast error";
  }
};

class IHolder {
 public:
  virtual std::shared_ptr<IHolder> Clone() = 0;
};

template <class T>
class AnyHolder : public IHolder {
 public:
  T value;

  AnyHolder(const T& accepted) : value(accepted) {  //  NOLINT
  }

  std::shared_ptr<IHolder> Clone() override {
    std::shared_ptr<AnyHolder<T>> new_object_ptr(std::make_shared<AnyHolder<T>>(this->value));
    return new_object_ptr;
  }
};

class Any {
 public:
  std::shared_ptr<IHolder> object_ptr;

  Any() : object_ptr(nullptr) {
  }

  Any(const Any& other) : object_ptr(other.object_ptr->Clone()) {
  }

  Any(Any&& other) noexcept : object_ptr(std::move(other.object_ptr)) {
    other.object_ptr = nullptr;
  }

  template <class T>
  Any(const T& accepted) : object_ptr(new AnyHolder<T>(accepted)) {  //  NOLINT
  }

  Any& operator=(const Any& other) {
    if (this != &other) {
      Any(other).Swap(*this);
    }
    return *this;
  }

  Any& operator=(Any&& other) {
    if (this != &other) {
      this->object_ptr = other.object_ptr;
      other.object_ptr = nullptr;
    }
    return *this;
  }

  [[nodiscard]] bool HasValue() const {
    bool flag = false;
    if (this->object_ptr) {
      flag = true;
    }
    return flag;
  }

  void Reset() {
    this->object_ptr = nullptr;
  }

  void Swap(Any& second) {
    this->object_ptr.swap(second.object_ptr);
  }
};

template <class T>
T AnyCast(const Any& accepted) {
  auto tmp = std::dynamic_pointer_cast<AnyHolder<T>>(accepted.object_ptr);
  T value;
  if (tmp) {
    value = tmp->value;
  } else {
    throw BadAnyCast{};
  }
  return value;
}