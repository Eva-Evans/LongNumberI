#include "../include/longnumber.hpp"


LongNumber::LongNumber(int intValue) {
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

LongNumber::LongNumber(unsigned unsignedValue) {
    while (unsignedValue > 0) {
        char digit = unsignedValue % 10;
        unsignedValue /= 10;
        integerPart.insert(integerPart.begin(), digit);
    }

    if (integerPart.empty()){
        integerPart.push_back(0);
    }
}

LongNumber::LongNumber(long long longValue) {
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

LongNumber::LongNumber(unsigned long long unsignedLongValue) {
    while (unsignedLongValue > 0) {
        char digit = unsignedLongValue % 10;
        unsignedLongValue /= 10;
        integerPart.insert(integerPart.begin(), digit);
    }

    if (integerPart.empty()){
        integerPart.push_back(0);
    }
}

LongNumber::LongNumber(double doubleValue) {
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

LongNumber::LongNumber(const std::vector<char>& integerPart_, const std::vector<char>& fractionalPart_, const Sign sign_) {
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


char LongNumber::AdditionDig(const char& dig1, const char& dig2, char& carry) const {
        char sum = dig1 + dig2 + carry;
        carry = sum / 10;
        return sum % 10;
    }

char LongNumber::SubtractionDig(const char& dig1, const char& dig2, char& borrow) const {
        char diff = dig1 - dig2 - borrow;
        borrow = (diff < 0) ? 1 : 0;
        return (borrow == 1) ? diff + 10 : diff;
    }

std::vector<char> LongNumber::MultiplicationDigComb(const std::vector<char>& num1, const std::vector<char>& num2) const {
        std::vector<char> result(num1.size() + num2.size(), 0);

        for (int i = num1.size() - 1; i >= 0; --i) {
            char carry = 0;
            for (int j = num2.size() - 1; j >= 0 || carry != 0; --j) {
                char current = result[i + j + 1] + num1[i] * (j >= 0 ? num2[j] : 0) + carry;
                result[i + j + 1] = current % 10;
                carry = current / 10;
            }
        }

        return result;
    }

//LongNumber findApproximateDivision(const LongNumber& dividend, const LongNumber& divisor) {}
LongNumber findApproximateDivision(const LongNumber& dividend, const LongNumber& divisor) {
    LongNumber low(0);
    LongNumber high(1);
    LongNumber epsilon(5E-1);
    const LongNumber tenConst(10);
    const LongNumber oneTenthConst(1E-1);
    const LongNumber oneSecondConst(5E-1);

    for (size_t i = 0; i < divisor.fractionalPart.size(); ++i) {
        high = high * tenConst;
    }

    high *= dividend;

    for (size_t i = 0; i < LongNumber::precision + 10; ++i) {
        epsilon = epsilon * oneTenthConst;
    }

    while ((high - low) >= epsilon) {
        LongNumber mid = (low + high) * oneSecondConst;
        LongNumber multiplyResult = mid * divisor;

        if (multiplyResult > dividend) {
            high = mid;
        } else {
            low = mid;
            if (multiplyResult == dividend) {
                break;
            }
        }
    }

    low += epsilon;
    std::vector<char> fractionalPartCropped(low.fractionalPart.begin(), min(low.fractionalPart.begin() + LongNumber::precision + 5, low.fractionalPart.end()));
    
    while (!fractionalPartCropped.empty() && !fractionalPartCropped.back()) {
        fractionalPartCropped.pop_back();
    }

    low.fractionalPart = fractionalPartCropped;

    return low;
}


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

    for (size_t ind = fmax(size1, size2) - 1; ind >= 0; --ind) {
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

    for (size_t ind = fmax(size1, size2) - 1; ind >= 0; --ind) {
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

LongNumber LongNumber::operator/(const LongNumber& other) const {

    if (other.sign == Sign::Positive){
        if (sign == Sign::Positive){
            return findApproximateDivision(*this, other);
        } else {
            return -findApproximateDivision(-*this, other);
        }
    } else {
        if (sign == Sign::Positive){
            return -findApproximateDivision(*this, -other);
        } else {
            return findApproximateDivision(-*this, -other);
        }
    }
}

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