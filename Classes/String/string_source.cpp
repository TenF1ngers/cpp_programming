#include "header.h"

char* UpSize(const char* c_style_str, size_t cur_size, size_t& capacity) {
  char* temp_buf = new char[(capacity - 1) * 2 + 1];
  for (size_t i = 0; i < cur_size; ++i) {
    temp_buf[i] = c_style_str[i];
  }
  temp_buf[cur_size] = '\0';
  capacity = (capacity - 1) * 2 + 1;
  delete[] c_style_str;
  return temp_buf;
}

char* UpCapacity(const char* c_style_str, size_t cur_size, size_t& capacity, size_t new_capacity) {
  char* temp_buf = new char[new_capacity + 1];
  if (new_capacity >= cur_size) {
    for (size_t i = 0; i < cur_size; ++i) {
      temp_buf[i] = c_style_str[i];
    }
    temp_buf[cur_size] = '\0';
  } else {
    for (size_t i = 0; i < new_capacity; ++i) {
      temp_buf[i] = c_style_str[i];
    }
    temp_buf[new_capacity] = '\0';
  }
  capacity = new_capacity + 1;
  if (c_style_str != nullptr) {
    delete[] c_style_str;
  }
  return temp_buf;
}

size_t StrLen(const char* c_style_str) {
  size_t size = 0, i = 0;
  if (c_style_str != nullptr) {
    while (c_style_str[i++] != '\0') {
      ++size;
    }
  }
  return size;
}

String::String() : buffer_(nullptr), size_(0), capacity_(1) {
}

String::String(const size_t& size, const char& symbol) {
  if (size == 0) {
    buffer_ = nullptr;
  } else {
    buffer_ = new char[size + 1];
    for (size_t i = 0; i < size; ++i) {
      buffer_[i] = symbol;
    }
    buffer_[size] = '\0';
  }
  size_ = size;
  capacity_ = size + 1;
}

String::String(const char* c_style_str) {
  size_t size = StrLen(c_style_str);
  if (size == 0) {
    buffer_ = nullptr;
  } else {
    buffer_ = new char[size + 1];
    for (size_t i = 0; i < size; ++i) {
      buffer_[i] = c_style_str[i];
    }
    buffer_[size] = '\0';
  }
  size_ = size;
  capacity_ = size + 1;
}

String::String(const String& other) {
  if (other.size_ == 0) {
    buffer_ = nullptr;
  } else {
    buffer_ = new char[other.size_ + 1];
    for (size_t i = 0; i < other.size_; ++i) {
      buffer_[i] = other.buffer_[i];
    }
    buffer_[other.size_] = '\0';
  }
  size_ = other.size_;
  capacity_ = other.size_ + 1;
}

String::String(const char* c_style_str, const size_t& size) {
  if (size == 0) {
    buffer_ = nullptr;
  } else {
    buffer_ = new char[size + 1];
    for (size_t i = 0; i < size; ++i) {
      buffer_[i] = c_style_str[i];
    }
    buffer_[size] = '\0';
  }
  size_ = size;
  capacity_ = size + 1;
}

String::~String() {
  delete[] buffer_;
}

char String::operator[](const size_t& idx) const {
  return buffer_[idx];
}

char& String::operator[](const size_t& idx) {
  return buffer_[idx];
}

char String::At(const size_t& idx) const {
  if ((idx < 0) || (idx > size_ - 1)) {
    throw StringOutOfRange{};
  }
  return buffer_[idx];
}

char& String::At(const size_t& idx) {
  if ((idx < 0) || (idx > size_ - 1)) {
    throw StringOutOfRange{};
  }
  return buffer_[idx];
}

char String::Front() const {
  return buffer_[0];
}

char& String::Front() {
  return buffer_[0];
}

char String::Back() const {
  return buffer_[size_ - 1];
}

char& String::Back() {
  return buffer_[size_ - 1];
}

char* String::CStr() {
  return buffer_;
}

const char* String::CStr() const {
  return buffer_;
}

char* String::Data() {
  return buffer_;
}

const char* String::Data() const {
  return buffer_;
}

bool String::Empty() const {
  bool flag = false;
  if (size_ == 0) {
    flag = true;
  }
  return flag;
}

size_t String::Size() const {
  return size_;
}

size_t String::Length() const {
  return size_;
}

size_t String::Capacity() const {
  return capacity_ - 1;
}

void String::Clear() {
  size_ = 0;
}

void String::Swap(String& second) {
  String temp_str(buffer_);
  *this = second;
  second = temp_str;
}

void String::PopBack() {
  --size_;
}

void String::PushBack(const char& symbol) {
  if (buffer_ == nullptr) {
    buffer_ = new char[2];
    buffer_[0] = symbol;
    buffer_[1] = '\0';
    size_ = 1;
    capacity_ = 2;
  } else {
    if (size_ == capacity_ - 1) {
      buffer_ = UpSize(buffer_, size_, capacity_);
    }
    buffer_[size_] = symbol;
    ++size_;
  }
}

String& String::operator+=(const String& second) {
  size_t size = StrLen(second.buffer_);
  if (size != 0) {
    if (capacity_ == 1) {
      buffer_ = new char[size + 1];
      for (size_t i = 0; i < size; ++i) {
        buffer_[i] = second.buffer_[i];
      }
      buffer_[size] = '\0';
      size_ = size;
      capacity_ = size + 1;
    } else {
      while (size_ + size > capacity_ - 1) {
        buffer_ = UpSize(buffer_, size_, capacity_);
      }
      for (size_t i = size_; i < size_ + size; ++i) {
        buffer_[i] = second.buffer_[i - size_];
      }
      buffer_[size_ + size] = '\0';
      size_ += size;
    }
  }
  return *this;
}

void String::Resize(const size_t& new_size, const char& symbol) {
  if (capacity_ == 1) {
    buffer_ = new char[new_size + 1];
    for (size_t i = 0; i < new_size; ++i) {
      buffer_[i] = symbol;
    }
    size_ = new_size;
    capacity_ = new_size + 1;
  } else {
    if (new_size <= capacity_) {
      if (new_size <= size_) {
        size_ = new_size;
      } else {
        for (size_t i = size_; i < new_size; ++i) {
          buffer_[i] = symbol;
        }
        size_ = new_size;
      }
    } else {
      while (capacity_ - 1 < new_size) {
        buffer_ = UpSize(buffer_, size_, capacity_);
      }
      for (size_t i = size_; i < new_size; ++i) {
        buffer_[i] = symbol;
      }
      size_ = new_size;
    }
  }
}

void String::Reserve(const size_t& new_capacity) {
  size_t max_capacity = std::max(capacity_, new_capacity);
  if (max_capacity != capacity_) {
    buffer_ = UpCapacity(buffer_, size_, capacity_, new_capacity);
  }
}

void String::ShrinkToFit() {
  buffer_ = UpCapacity(buffer_, size_, capacity_, size_);
}

std::ostream& operator<<(std::ostream& out, const String& str) {
  if (str.buffer_ != nullptr) {
    size_t i = 0;
    while (str.buffer_[i++] != '\0') {
      out << str.buffer_[i - 1];
    }
  }
  return out;
}

const String operator+(const String& first, const String& second) {
  String new_str(first);
  new_str += second;
  return new_str;
}

bool String::operator>(const String& second) const {
  size_t max_size = std::max(size_, second.size_);
  bool flag = false;
  size_t counter = 0;
  if (max_size == size_) {
    for (size_t i = 0; i < second.size_; ++i) {
      if (buffer_[i] > second.buffer_[i]) {
        flag = true;
        break;
      } else if (buffer_[i] < second.buffer_[i]) {
        break;
      } else {
        ++counter;
      }
    }
    if (counter == second.size_) {
      if (max_size != second.size_) {
        flag = true;
      }
    }
  } else {
    for (size_t i = 0; i < size_; ++i) {
      if (buffer_[i] > second.buffer_[i]) {
        flag = true;
        break;
      } else if (buffer_[i] < second.buffer_[i]) {
        break;
      }
    }
  }
  return flag;
}

bool String::operator<(const String& second) const {
  size_t max_size = std::max(size_, second.size_);
  bool flag = false;
  size_t counter = 0;
  if (max_size == size_) {
    for (size_t i = 0; i < second.size_; ++i) {
      if (buffer_[i] < second.buffer_[i]) {
        flag = true;
        break;
      } else if (buffer_[i] > second.buffer_[i]) {
        break;
      }
    }
  } else {
    for (size_t i = 0; i < size_; ++i) {
      if (buffer_[i] < second.buffer_[i]) {
        flag = true;
        break;
      } else if (buffer_[i] > second.buffer_[i]) {
        break;
      } else {
        ++counter;
      }
    }
    if (counter == size_) {
      if (max_size != size_) {
        flag = true;
      }
    }
  }
  return flag;
}

bool String::operator>=(const String& second) const {
  size_t max_size = std::max(size_, second.size_);
  bool flag = false;
  size_t counter = 0;
  if (max_size == size_) {
    for (size_t i = 0; i < second.size_; ++i) {
      if (buffer_[i] > second.buffer_[i]) {
        flag = true;
        break;
      } else if (buffer_[i] < second.buffer_[i]) {
        break;
      } else {
        ++counter;
      }
    }
    if (counter == second.size_) {
      flag = true;
    }
  } else {
    for (size_t i = 0; i < size_; ++i) {
      if (buffer_[i] > second.buffer_[i]) {
        flag = true;
        break;
      } else if (buffer_[i] < second.buffer_[i]) {
        break;
      } else {
        ++counter;
      }
    }
    if (counter == size_) {
      if (max_size == size_) {
        flag = true;
      }
    }
  }
  return flag;
}

bool String::operator<=(const String& second) const {
  size_t max_size = std::max(size_, second.size_);
  bool flag = false;
  size_t counter = 0;
  if (max_size == size_) {
    for (size_t i = 0; i < second.size_; ++i) {
      if (buffer_[i] < second.buffer_[i]) {
        flag = true;
        break;
      } else if (buffer_[i] > second.buffer_[i]) {
        break;
      } else {
        ++counter;
      }
    }
    if (counter == second.size_) {
      if (max_size == second.size_) {
        flag = true;
      }
    }
  } else {
    for (size_t i = 0; i < size_; ++i) {
      if (buffer_[i] < second.buffer_[i]) {
        flag = true;
        break;
      } else if (buffer_[i] > second.buffer_[i]) {
        break;
      } else {
        ++counter;
      }
    }
    if (counter == size_) {
      flag = true;
    }
  }
  return flag;
}

bool String::operator==(const String& second) const {
  bool flag = true;
  if (size_ == second.size_) {
    for (size_t i = 0; i < size_; ++i) {
      if (buffer_[i] != second.buffer_[i]) {
        flag = false;
        break;
      }
    }
  } else {
    flag = false;
  }
  return flag;
}

bool String::operator!=(const String& second) const {
  size_t max_size = std::max(size_, second.size_);
  bool flag = false;
  size_t counter = 0;
  if (max_size == size_) {
    for (size_t i = 0; i < second.size_; ++i) {
      if (buffer_[i] != second.buffer_[i]) {
        flag = true;
        break;
      } else {
        ++counter;
      }
    }
    if (counter == second.size_) {
      if (second.size_ != max_size) {
        flag = true;
      }
    }
  } else {
    for (size_t i = 0; i < size_; ++i) {
      if (buffer_[i] != second.buffer_[i]) {
        flag = true;
        break;
      } else {
        ++counter;
      }
    }
    if (counter == size_) {
      if (size_ != max_size) {
        flag = true;
      }
    }
  }
  return flag;
}

String& String::operator=(const String& second) {
  if (second.buffer_ == nullptr) {
    if (buffer_ != nullptr) {
      delete[] buffer_;
      buffer_ = nullptr;
    }
    size_ = 0;
    capacity_ = 1;
  } else {
    size_t size = StrLen(second.buffer_);
    buffer_ = UpCapacity(buffer_, size_, capacity_, second.Capacity());
    for (size_t i = 0; i < size; ++i) {
      buffer_[i] = second.buffer_[i];
    }
    buffer_[size] = '\0';
    size_ = size;
    capacity_ = second.Capacity() + 1;
  }
  return *this;
}

int main () {
  std::cout << String("abacaba") << ' ' << String() << ' ' << String(5, 'a');
  return 0;
}