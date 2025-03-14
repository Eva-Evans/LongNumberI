//include/longnumber.hpp
#ifndef LONG_NUMBER_HPP
#define LONG_NUMBER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <stdexcept>



enum class Sign {
    Positive,
    Negative
};

class LongNumber {
private:
    Sign sign;
    std::vector<char> integerPart;
    std::vector<char> fractionalPart;
    char AdditionDig(const char& dig1, const char& dig2, char& carry) const;
    char SubtractionDig(const char& dig1, const char& dig2, char& borrow) const;
    std::vector<char> MultiplicationDigComb(const std::vector<char>& num1, const std::vector<char>& num2) const;

    friend LongNumber findApproximateDivision(const LongNumber& dividend, const LongNumber& divisor);

public:
    static size_t precision;

    LongNumber(int intValue);
    LongNumber(unsigned unsignedValue);
    LongNumber(long long longValue);
    LongNumber(unsigned long long unsignedLongValue);
    LongNumber(double doubleValue);
    LongNumber(const std::vector<char>& integerPart_, const std::vector<char>& fractionalPart_, const Sign sign_ = Sign::Positive);


    LongNumber(const LongNumber& other) = default; //оператор копирования
    LongNumber& operator=(const LongNumber& other) = default; //оператор присваивания

    ~LongNumber() = default;

    LongNumber operator+(const LongNumber& other) const;
    LongNumber operator-(const LongNumber& other) const;
    LongNumber operator*(const LongNumber& other) const;
    LongNumber operator/(const LongNumber& other) const;
    LongNumber operator-() const;
    LongNumber operator+=(const LongNumber& other);
    LongNumber operator-=(const LongNumber& other);
    LongNumber operator*=(const LongNumber& other);
    LongNumber operator/=(const LongNumber& other);

    std::vector<char> getIntegerPart() const;
    std::vector<char> getFractionalPart() const;
    std::string to_string() const;

    bool operator==(const LongNumber& other) const;
    bool operator!=(const LongNumber& other) const;
    bool operator<(const LongNumber& other) const;
    bool operator<=(const LongNumber& other) const;
    bool operator>(const LongNumber& other) const;
    bool operator>=(const LongNumber& other) const;


    

    friend std::ostream& operator<<(std::ostream& os, const LongNumber& num);
    friend std::istream &operator>>(std::istream &stream,  LongNumber& num);
};

LongNumber operator"" _longnum(long double number);

#endif // LONG_NUMBER_HPP