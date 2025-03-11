
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

    /*  
     LongNumber(int intValue) {
            sign = (intValue >= 0) ? Sign::Positive : Sign::Negative;
            intValue = abs(intValue);

            while (intValue > 0) {
                char digit = intValue % 10;
                intValue /= 10;
                integerPart.insert(integerPart.begin(), digit);
            }

            if (integerPart.empty()){
                integerPart.push_back(0);
            }
        } 

        LongNumber(unsigned unsignedValue) {
            while (unsignedValue > 0) {
                char digit = unsignedValue % 10;
                unsignedValue /= 10;
                integerPart.insert(integerPart.begin(), digit);
            }

            if (integerPart.empty()){
                integerPart.push_back(0);
            }
        }

        LongNumber(long long longValue) {
            sign = (longValue >= 0) ? Sign::Positive : Sign::Negative;
            longValue = abs(longValue);

            while (longValue > 0) {
                char digit = longValue % 10;
                longValue /= 10;
                integerPart.insert(integerPart.begin(), digit);
            }

            if (integerPart.empty()){
                integerPart.push_back(0);
            }
        }

        LongNumber(unsigned long long unsignedLongValue) {
            while (unsignedLongValue > 0) {
                char digit = unsignedLongValue % 10;
                unsignedLongValue /= 10;
                integerPart.insert(integerPart.begin(), digit);
            }

            if (integerPart.empty()){
                integerPart.push_back(0);
            }
        }
       
        LongNumber(double doubleValue) {
            std::stringstream ss(std::to_string(doubleValue));
            char ch;
            
            sign = (doubleValue >= 0) ? Sign::Positive : Sign::Negative;

            while (ss.get(ch) && ch != '.') {
                if (isdigit(ch)) {
                    integerPart.push_back(ch - '0');
                }
            }

            while (ss.get(ch)) {
                if (isdigit(ch)) {
                    fractionalPart.push_back(ch - '0');
                }
            }

            while (!fractionalPart.empty() && !fractionalPart.back()) {
                fractionalPart.pop_back();
            }

            if (integerPart.empty()){
                integerPart.push_back(0);
            }

            if (fractionalPart.empty() && *integerPart.begin() == 0) {
                sign = Sign::Positive;
            }
        }

        LongNumber(const std::vector<char>& integerPart_, const std::vector<char>& fractionalPart_, const Sign sign_ = Sign::Positive) {
            integerPart = integerPart_;
            fractionalPart = fractionalPart_;
            sign = sign_;

            while (!fractionalPart.empty() && !fractionalPart.back()) {
                fractionalPart.pop_back();
            }

            if (integerPart.empty()){
                integerPart.push_back(0);
            }

            if (fractionalPart.empty() && *integerPart.begin() == 0) {
                sign = Sign::Positive;
            }
        }
*/

    LongNumber(const LongNumber& other) = default; //еонструктор копирования
    LongNumber& operator=(const LongNumber& other) = default; //конструктор присваивания
    //

    ~LongNumber() = default;
    
       // LongNumber(const string& numberStr) {}

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

    bool operator==(const LongNumber& other) const;
    bool operator!=(const LongNumber& other) const;
    bool operator<(const LongNumber& other) const;
    bool operator<=(const LongNumber& other) const;
    bool operator>(const LongNumber& other) const;
    bool operator>=(const LongNumber& other) const;


    

    friend std::ostream& operator<<(std::ostream& os, const LongNumber& num);
    // friend std::istream &operator>>(std::istream &stream,  LongNumber& num);
                    // Количество знаков после запятой
};

// Литерал для создания длинного числа из long double
LongNumber operator"" _longnum(long double number);

#endif // LONG_NUMBER_HPP