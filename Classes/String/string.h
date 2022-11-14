#ifndef STRING__CLASS__HEADER_H
#define STRING__CLASS__HEADER_H

#include <iostream>
#include <stdexcept>
#include <string_view>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 private:
  char* buffer_;
  size_t size_;
  size_t capacity_;

 public:
  String ();
  String(const size_t& size, const char& symbol);
  String(const char* c_style_str);  //  NOLINT
  String(const String& other);  //  NOLINT
  String(const char* c_style_str, const size_t& size);
  ~String();
  String& operator=(const String& second);
  friend char* UpSize(const char* c_style_str, size_t cur_size, size_t& capacity);
  char operator[](const size_t& idx) const;
  char& operator[](const size_t& idx);
  char At(const size_t& idx) const;
  char& At(const size_t& idx);
  char Front() const;
  char& Front();
  char Back() const;
  char& Back();
  char* CStr();
  const char* CStr() const;
  char* Data();
  const char* Data() const;
  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();
  void Swap(String& second);
  void PopBack();
  void PushBack(const char& symbol);
  String& operator+=(const String& second);
  friend const String operator+(const String& first, const String& second);
  bool operator>(const String& second) const;
  bool operator<(const String& second) const;
  bool operator>=(const String& second) const;
  bool operator<=(const String& second) const;
  bool operator==(const String& second) const;
  bool operator!=(const String& second) const;
  friend std::ostream& operator<<(std::ostream& out, const String& str);
  void Resize(const size_t& new_size, const char& symbol);
  void Reserve(const size_t& new_capacity);
  void ShrinkToFit();
};

#endif //STRING__CLASS__HEADER_H

void CheckEqual(const String& actual, std::string_view expected) {
  std::cout << (actual.Capacity() >= actual.Size());
  std::cout << (actual.Size() == expected.size());
  std::cout << (actual.Length() == expected.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    std::cout << (actual[i] == expected[i]);
  }
  std::cout << "\n";
}

void CheckComparisonEqual(const String& lhs, const String& rhs) {
  std::cout << 1 << "\n";
  std::cout << (lhs == rhs);
  std::cout << (lhs <= rhs);
  std::cout << (lhs >= rhs);
  std::cout << (lhs != rhs);
  std::cout << (lhs < rhs);
  std::cout << (lhs > rhs);
  std::cout << "\n";
}

void CheckComparisonLess(const String& lhs, const String& rhs) {
  std::cout << 2 << "\n";
  std::cout << (lhs == rhs);
  std::cout << (lhs <= rhs);
  std::cout << (lhs >= rhs);
  std::cout << (lhs != rhs);
  std::cout << (lhs < rhs);
  std::cout << (lhs > rhs);
  std::cout << "\n";
}

void CheckComparisonGreater(const String& lhs, const String& rhs) {
  std::cout << 3 << "\n";
  std::cout << (lhs == rhs);
  std::cout << (lhs <= rhs);
  std::cout << (lhs >= rhs);
  std::cout << (lhs != rhs);
  std::cout << (lhs < rhs);
  std::cout << (lhs > rhs);
  std::cout << "\n";
}