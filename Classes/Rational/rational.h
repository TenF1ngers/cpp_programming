#pragma once

#include <iostream>
#include <stdexcept>
#include <numeric>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 private:
  int32_t numerator_;
  int32_t denominator_;

 public:
  int32_t GetDenominator() const;
  int32_t GetNumerator() const;
  Rational operator+(const Rational& second) const;
  Rational operator-(const Rational& second) const;
  Rational operator*(const Rational& second) const;
  Rational operator/(const Rational& second) const;
  Rational& operator+=(const Rational& value);
  Rational& operator-=(const Rational& value);
  Rational& operator*=(const Rational& value);
  Rational& operator/=(const Rational& value);
  Rational operator+() const;
  Rational operator-() const;
  Rational& operator++();
  Rational& operator--();
  const Rational operator++(int);
  const Rational operator--(int);
  bool operator>(Rational second) const;
  bool operator<(Rational second) const;
  bool operator>=(Rational second) const;
  bool operator<=(Rational second) const;
  bool operator==(Rational second) const;
  bool operator!=(Rational second) const;
  friend std::istream& operator>>(std::istream& in, Rational& rt);
  friend std::ostream& operator<<(std::ostream& out, const Rational& rt);
  Rational();
  Rational(const int32_t& value);  //  NOLINT
  Rational(int32_t num, int32_t den);
  void Reduction();
  void SetDenominator(int32_t den);
  void SetNumerator(int32_t num);
};

bool operator>(const int32_t& first, Rational second);
bool operator<(const int32_t& first, Rational second);
bool operator>=(const int32_t& first, Rational second);
bool operator<=(const int32_t& first, Rational second);
bool operator==(const int32_t& first, Rational second);
bool operator!=(const int32_t& first, Rational second);