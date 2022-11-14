#pragma once

#include <iostream>
#include <optional>
#include <stdexcept>

class BadOptionalAccess : public std::bad_optional_access {
 public:
  BadOptionalAccess() : std::bad_optional_access() {
  }
};

template <class T>
class Optional {
 private:
  char memory_[sizeof(T)];
  bool has_value_;
  T* object_;

 public:
  explicit operator bool() const {
    return has_value_;
  }

  template <class... Args>
  T& Emplace(Args&&... args) {
    this->Reset();

    object_ = new (memory_) T(std::forward<Args>(args)...);

    has_value_ = true;

    return *object_;
  }

  [[nodiscard]] bool HasValue() const {
    return has_value_;
  }

  explicit Optional() : has_value_(false), object_(nullptr) {
  }

  Optional(const Optional<T>& other) {
    if (other.HasValue()) {
      object_ = new (memory_) T(*(other.object_));

      has_value_ = true;
    } else {
      object_ = nullptr;

      has_value_ = false;
    }
  }

  Optional(Optional<T>&& other) noexcept {
    if (other.HasValue()) {
      object_ = new (memory_) T(std::move(*(other.object_)));

      has_value_ = true;
    } else {
      object_ = nullptr;

      has_value_ = false;
    }
  }

  Optional(const T& other_object) : has_value_(true), object_(new (memory_) T(other_object)) {  //  NOLINT
  }

  Optional(T&& other_object) : has_value_(true), object_(new (memory_) T(std::move(other_object))) {  //  NOLINT
  }

  void Reset() {
    if (this->HasValue()) {
      object_->~T();

      has_value_ = false;
    }
  }

  void Swap(Optional<T>& other) {
    Optional<T> tmp = std::move(*this);
    *this = std::move(other);
    other = std::move(tmp);
  }

  T Value() const {
    if (!this->HasValue()) {
      throw BadOptionalAccess{};
    }
    return *object_;
  }

  T& Value() {
    if (!this->HasValue()) {
      throw BadOptionalAccess{};
    }
    return *object_;
  }

  Optional<T>& operator=(const Optional<T>& other) {
    if (other.HasValue()) {
      this->Reset();

      object_ = new (memory_) T(*(other.object_));

      has_value_ = true;
    } else {
      if (this->HasValue()) {
        this->Reset();
      }
    }

    return *this;
  }

  Optional<T>& operator=(Optional<T>&& other) noexcept {
    if (other.HasValue()) {
      this->Reset();

      object_ = new (memory_) T(std::move(*(other.object_)));

      has_value_ = true;
    } else {
      if (this->HasValue()) {
        this->Reset();
      }
    }

    return *this;
  }

  Optional<T>& operator=(const T& other_object) {
    this->Reset();

    object_ = new (memory_) T(other_object);

    has_value_ = true;

    return *this;
  }

  Optional<T>& operator=(T&& other_object) {
    this->Reset();

    object_ = new (memory_) T(std::move(other_object));

    has_value_ = true;

    return *this;
  }

  T operator*() const {
    return *object_;
  }

  T& operator*() {
    return *object_;
  }

  ~Optional() {
    this->Reset();
  }
};