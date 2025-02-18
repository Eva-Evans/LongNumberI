



#include "longnumber.hpp"

//LongNumber findApproximateDivision(const LongNumber& dividend, const LongNumber& divisor) {}

LongNumber LongNumber::operator+(const LongNumber& other) const {
    if ((*this).sign == Sign::Negative && other.sign == Sign::Negative) {
        LongNumber result = -*this + -other;
        return -result;
    } else if (sign != other.sign){
        LongNumber result = *this - (-other);
        return result;
    }

    std::vector<char> resultInteger;
    std::vector<char> resultFractional;

    size_t size1 = fractionalPart.size();
    size_t size2 = other.fractionalPart.size();

    char carry = 0;

    for (int ind = fmax(size1, size2) - 1; ind >= 0; --ind) {
        char digit1 = (ind < size1) ? fractionalPart[ind] : 0;
        char digit2 = (ind < size2) ? other.fractionalPart[ind] : 0;

        resultFractional.push_back(AdditionDig(digit1, digit2, carry));
    }
    
    auto it1 = integerPart.rbegin();
    auto it2 = other.integerPart.rbegin();

    while (it1 != integerPart.rend() || it2 != other.integerPart.rend() || carry) {
        char digit1 = (it1 != integerPart.rend()) ? *it1 : 0;
        char digit2 = (it2 != other.integerPart.rend()) ? *it2 : 0;

        resultInteger.push_back(AdditionDig(digit1, digit2, carry));

        if (it1 != integerPart.rend()) ++it1;
        if (it2 != other.integerPart.rend()) ++it2;
    }

    reverse(resultInteger.begin(), resultInteger.end());
    reverse(resultFractional.begin(), resultFractional.end());

    return LongNumber(resultInteger, resultFractional);
}

LongNumber LongNumber::operator-(const LongNumber& other) const {
    if (sign == other.sign) {
        if (sign == Sign::Positive && other.sign == Sign::Positive) {
            if (*this < other) {
                LongNumber result = other - *this;
                return -result;
            }
        } else {
            LongNumber result = -*this - (-other);
            return -result;
        }
    } else {
        LongNumber result = *this + (-other);
        return result;
    }

    std::vector<char> resultInteger;
    std::vector<char> resultFractional;

    size_t size1 = fractionalPart.size();
    size_t size2 = other.fractionalPart.size();

    char borrow = 0;

    for (int ind = fmax(size1, size2) - 1; ind >= 0; --ind) {
        char digit1 = (ind < size1) ? fractionalPart[ind] : 0;
        char digit2 = (ind < size2) ? other.fractionalPart[ind] : 0;

        resultFractional.push_back(SubtractionDig(digit1, digit2, borrow));
    }

    auto it1 = integerPart.rbegin();
    auto it2 = other.integerPart.rbegin();

    while (it1 != integerPart.rend() || it2 != other.integerPart.rend() || borrow != 0) {
        char digit1 = (it1 != integerPart.rend()) ? *it1 : 0;
        char digit2 = (it2 != other.integerPart.rend()) ? *it2 : 0;

        resultInteger.push_back(SubtractionDig(digit1, digit2, borrow));

        if (it1 != integerPart.rend()) ++it1;
        if (it2 != other.integerPart.rend()) ++it2;
    }

    while (!resultInteger.empty() && resultInteger.back() == 0) {
        resultInteger.pop_back();
    }

    reverse(resultInteger.begin(), resultInteger.end());
    reverse(resultFractional.begin(), resultFractional.end());

    return LongNumber(resultInteger, resultFractional, sign);
}

LongNumber LongNumber::operator*(const LongNumber& other) const {
    std::vector<char> num1Comb = integerPart;
    num1Comb.insert(num1Comb.end(), fractionalPart.begin(), fractionalPart.end());

    std::vector<char> num2Comb = other.integerPart;
    num2Comb.insert(num2Comb.end(), other.fractionalPart.begin(), other.fractionalPart.end());

    std::vector<char> resultComb = MultiplicationDigComb(num1Comb, num2Comb);

    std::vector<char> resultInteger (resultComb.begin(), resultComb.end() - fractionalPart.size() - other.fractionalPart.size());
    std::vector<char> resultFractional (resultComb.end() - fractionalPart.size() - other.fractionalPart.size(), resultComb.end());
    Sign resultSign = ((*this).sign == other.sign) ? Sign::Positive : Sign::Negative;

    while (!resultInteger.empty() && !*resultInteger.begin()) {
        resultInteger.erase(resultInteger.begin());
    }

    if (resultInteger.empty()) {
        resultInteger.push_back(0);
    }

    return LongNumber(resultInteger, resultFractional, resultSign);
}

//LongNumber LongNumber::operator/(const LongNumber& other) const {}

LongNumber LongNumber::operator-() const {
    LongNumber result = *this;
    result.sign = (result.sign == Sign::Positive) ? Sign::Negative : Sign::Positive;
    return result;
}

LongNumber LongNumber::operator+=(const LongNumber& other) {
    return *this = *this + other;
}

LongNumber LongNumber::operator-=(const LongNumber& other) {
    return *this = *this - other;
}

LongNumber LongNumber::operator*=(const LongNumber& other) {
    return *this = *this * other;
}

LongNumber LongNumber::operator/=(const LongNumber& other) {
    return *this = *this / other;
}

std::vector<char> LongNumber::getIntegerPart() const {
    return integerPart;
}

std::vector<char> LongNumber::getFractionalPart() const {
    return fractionalPart;
}

bool LongNumber::operator==(const LongNumber& other) const {
    return (integerPart == other.integerPart) && (fractionalPart == other.fractionalPart) && (sign == other.sign);
}

bool LongNumber::operator!=(const LongNumber& other) const {
    return !(*this == other);
}

bool LongNumber::operator<(const LongNumber& other) const {
    if (sign == Sign::Negative && other.sign == Sign::Negative) return -other < -*this;

    if (sign == Sign::Positive && other.sign == Sign::Negative) return false;

    if (sign == Sign::Negative && other.sign == Sign::Positive) return true;

    if (integerPart.size() != other.integerPart.size()) {
        return integerPart.size() < other.integerPart.size();
    }

    for (size_t i = 0; i < integerPart.size(); ++i) {
        if (integerPart[i] != other.integerPart[i]) {
            return integerPart[i] < other.integerPart[i];
        }
    }

    for (size_t i = 0; i < fmin(fractionalPart.size(), other.fractionalPart.size()); ++i) {
        if (fractionalPart[i] != other.fractionalPart[i]) {
            return fractionalPart[i] < other.fractionalPart[i];
        }
    }

    return fractionalPart.size() < other.fractionalPart.size();
}

bool LongNumber::operator<=(const LongNumber& other) const {
    return (*this < other) || (*this == other);
}

bool LongNumber::operator>(const LongNumber& other) const {
    return !(*this <= other);
}

bool LongNumber::operator>=(const LongNumber& other) const {
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const LongNumber& num) {
    if (num.sign == Sign::Negative) os << '-';

    for (size_t i = 0; i < num.integerPart.size(); ++i) {
        os << (int)num.integerPart[i];
    }

    // if (number.integerPart.empty()) os << '0';

    if (!num.fractionalPart.empty()) {
        os << '.';

        for (int i = 0; i < fmin(num.fractionalPart.size(), LongNumber::precision); ++i) {
            os << (int)num.fractionalPart[i];
        }
    }

    return os;
}