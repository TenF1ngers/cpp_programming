#ifndef STRING_VIEW__CLASS__HEADER_H
#define STRING_VIEW__CLASS__HEADER_H

#include <iostream>
#include <stdexcept>

size_t StrLen(const char* c_string) {
  size_t size = 0, i = 0;
  while (c_string[i++] != '\0') {
    ++size;
  }
  return size;
}

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

class StringView {
 private:
  const char* buffer_;
  size_t size_;

 public:
  StringView() : buffer_(nullptr), size_(0) {
  }

  StringView(const char* c_string) : buffer_(c_string), size_(StrLen(c_string)) {
  }

  StringView(const char* c_string, size_t size) : buffer_(c_string), size_(size) {
  }

  char operator[](size_t idx) const {
    return buffer_[idx];
  }

  char At(size_t idx) const {
    if (idx >= size_) {
      throw StringViewOutOfRange{};
    }
    return buffer_[idx];
  }

  char Front() const {
    return buffer_[0];
  }

  char Back() const {
    return buffer_[size_ - 1];
  }

  size_t Size() const {
    return size_;
  }

  size_t Length() const {
    return size_;
  }

  bool Empty() const {
    bool flag = false;
    if (size_ == 0) {
      flag = true;
    }
    return flag;
  }

  const char* Data() const {
    return buffer_;
  }

  void Swap(StringView& second) {
    const char* temp = buffer_;
    size_t temp_size = size_;
    buffer_ = second.buffer_;
    second.buffer_ = temp;
    size_ = second.size_;
    second.size_ = temp_size;
  }

  void RemovePrefix(size_t prefix_size) {
    if (prefix_size > size_) {
      size_ = 0;
    } else {
      size_ -= prefix_size;
    }
    buffer_ += prefix_size;
  }

  void RemoveSuffix(size_t suffix_size) {
    if (suffix_size > size_) {
      size_ = 0;
    } else {
      size_ -= suffix_size;
    }
  }

  StringView Substr(size_t pos, size_t count) const {
    if (pos >= size_) {
      throw StringViewOutOfRange{};
    }
    StringView new_str(&buffer_[pos], std::min(count, size_ - pos));
    return new_str;
  }
};

void Equal(const StringView& actual, const char* expected, size_t n) {
  std::cout << (actual.Data() == expected);
  std::cout << (actual.Size() == n);
  std::cout << (actual.Length() == n);
  std::cout << (actual.Empty() == (n == 0));
  for (size_t i = 0; i < n; ++i) {
    std::cout << (actual[i] == expected[i]);
  }
  std::cout << "\n";
}

#endif //STRING_VIEW__CLASS__HEADER_H