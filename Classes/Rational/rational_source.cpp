#include "rational.h"
#include <numeric>

int32_t Rational::GetDenominator() const {
  return denominator_;
}

int32_t Rational::GetNumerator() const {
  return numerator_;
}

Rational Rational::operator+(const Rational& second) const {
  int32_t den2 = second.denominator_;
  int32_t new_num1 = numerator_ * den2;
  int32_t new_num2 = second.numerator_ * denominator_;
  int32_t new_num = new_num1 + new_num2;
  Rational new_rt(new_num, denominator_ * den2);
  return new_rt;
}

Rational Rational::operator-(const Rational& second) const {
  int32_t den2 = second.denominator_;
  int32_t new_num1 = numerator_ * den2;
  int32_t new_num2 = second.numerator_ * denominator_;
  int32_t new_num = new_num1 - new_num2;
  Rational new_rt(new_num, denominator_ * den2);
  return new_rt;
}

Rational Rational::operator*(const Rational& second) const {
  int32_t new_num = numerator_ * second.numerator_;
  int32_t new_den = denominator_ * second.denominator_;
  Rational new_rt(new_num, new_den);
  return new_rt;
}

Rational Rational::operator/(const Rational& second) const {
  int32_t new_num = numerator_ * second.denominator_;
  int32_t new_den = denominator_ * second.numerator_;
  Rational new_rt(new_num, new_den);
  return new_rt;
}

Rational& Rational::operator+=(const Rational& value) {
  numerator_ *= value.denominator_;
  numerator_ += value.numerator_ * denominator_;
  denominator_ *= value.denominator_;
  Reduction();
  return *this;
}

Rational& Rational::operator-=(const Rational& value) {
  numerator_ *= value.denominator_;
  numerator_ -= value.numerator_ * denominator_;
  denominator_ *= value.denominator_;
  Reduction();
  return *this;
}

Rational& Rational::operator*=(const Rational& value) {
  numerator_ *= value.numerator_;
  denominator_ *= value.denominator_;
  Reduction();
  return *this;
}

Rational& Rational::operator/=(const Rational& value) {
  numerator_ *= value.denominator_;
  denominator_ *= value.numerator_;
  Reduction();
  return *this;
}

Rational Rational::operator+() const {
  return {numerator_, denominator_};
}

Rational Rational::operator-() const {
  return {-numerator_, denominator_};
}

Rational& Rational::operator++() {
  numerator_ += denominator_;
  Reduction();
  return *this;
}

Rational& Rational::operator--() {
  numerator_ -= denominator_;
  Reduction();
  return *this;
}

const Rational Rational::operator++(int) {
  const Rational old = *this;
  numerator_ += denominator_;
  Reduction();
  return old;
}

const Rational Rational::operator--(int) {
  const Rational old = *this;
  numerator_ -= denominator_;
  Reduction();
  return old;
}

bool Rational::operator>(Rational second) const {
  int32_t num1 = numerator_ * second.denominator_;
  int32_t num2 = second.numerator_ * denominator_;
  bool flag = true;
  if (num1 <= num2) {
    flag = false;
  }
  return flag;
}

bool Rational::operator<(Rational second) const {
  int32_t num1 = numerator_ * second.denominator_;
  int32_t num2 = second.numerator_ * denominator_;
  bool flag = true;
  if (num1 >= num2) {
    flag = false;
  }
  return flag;
}

bool Rational::operator>=(Rational second) const {
  int32_t num1 = numerator_ * second.denominator_;
  int32_t num2 = second.numerator_ * denominator_;
  bool flag = true;
  if (num1 < num2) {
    flag = false;
  }
  return flag;
}

bool Rational::operator<=(Rational second) const {
  int32_t num1 = numerator_ * second.denominator_;
  int32_t num2 = second.numerator_ * denominator_;
  bool flag = true;
  if (num1 > num2) {
    flag = false;
  }
  return flag;
}

bool Rational::operator==(Rational second) const {
  int32_t num1 = numerator_ * second.denominator_;
  int32_t num2 = second.numerator_ * denominator_;
  bool flag = true;
  if (num1 != num2) {
    flag = false;
  }
  return flag;
}

bool Rational::operator!=(Rational second) const {
  int32_t num1 = numerator_ * second.denominator_;
  int32_t num2 = second.numerator_ * denominator_;
  bool flag = true;
  if (num1 == num2) {
    flag = false;
  }
  return flag;
}

std::istream& operator>>(std::istream& in, Rational& rt) {
  const int32_t max_size = 22;
  char str[max_size];
  in >> str;
  char* end = nullptr;
  rt.numerator_ = static_cast<int32_t>(strtoll(str, &end, 10));
  if (*end != 0) {
    ++end;
    rt.denominator_ = static_cast<int32_t>(strtoll(end, &end, 10));
  } else {
    rt.denominator_ = 1;
  }
  rt.Reduction();
  return in;
}

std::ostream& operator<<(std::ostream& out, const Rational& rt) {
  if (rt.denominator_ == 1) {
    out << rt.numerator_;
  } else {
    out << rt.numerator_ << "/" << rt.denominator_;
  }
  return out;
}

Rational::Rational() : numerator_(0), denominator_(1) {
}

Rational::Rational(const int32_t& value) : numerator_(value), denominator_(1) {
}

Rational::Rational(int32_t num, int32_t den) : numerator_(num), denominator_(den) {
  Reduction();
}

void Rational::Reduction() {
  if (denominator_ == 0) {
    throw RationalDivisionByZero();
  }
  int32_t gcd = std::gcd(std::abs(numerator_), std::abs(denominator_));
  if ((numerator_ < 0) && (denominator_ < 0)) {
    numerator_ = std::abs(numerator_);
    denominator_ = std::abs(denominator_);
  } else if (denominator_ < 0) {
    numerator_ = -numerator_;
    denominator_ = std::abs(denominator_);
  }
  numerator_ /= gcd;
  denominator_ /= gcd;
}

void Rational::SetDenominator(int32_t den) {
  denominator_ = den;
  Reduction();
}

void Rational::SetNumerator(int32_t num) {
  numerator_ = num;
  Reduction();
}

bool operator>(const int32_t& first, Rational second) {
  Rational temp(first);
  bool flag = true;
  if (temp <= second) {
    flag = false;
  }
  return flag;
}

bool operator<(const int32_t& first, Rational second) {
  Rational temp(first);
  bool flag = true;
  if (temp >= second) {
    flag = false;
  }
  return flag;
}

bool operator>=(const int32_t& first, Rational second) {
  Rational temp(first);
  bool flag = true;
  if (temp < second) {
    flag = false;
  }
  return flag;
}

bool operator<=(const int32_t& first, Rational second) {
  Rational temp(first);
  bool flag = true;
  if (temp > second) {
    flag = false;
  }
  return flag;
}

bool operator==(const int32_t& first, Rational second) {
  Rational temp(first);
  bool flag = true;
  if (temp != second) {
    flag = false;
  }
  return flag;
}

bool operator!=(const int32_t& first, Rational second) {
  Rational temp(first);
  bool flag = true;
  if (temp == second) {
    flag = false;
  }
  return flag;
}