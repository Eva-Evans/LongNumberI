#include "../include/longnumber.hpp"
//#include "../include/test_system.hpp"


inline bool test_addition() {
    LongNumber a(123.45);
    LongNumber b(67.89);
    LongNumber expected(191.34);

    LongNumber result = a + b;

    if (result == expected) {
        return true;
    } else {
        printf("Expected: %s, Got: %s\n", expected.to_string().c_str(), result.to_string().c_str());
        return false;
    }
}


inline bool test_subtraction() {
    LongNumber a(100.0);
    LongNumber b(50.5);
    LongNumber expected(49.5);

    LongNumber result = a - b;

    if (result == expected) {
        return true;
    } else {
        printf("Expected: %s, Got: %s\n", expected.to_string().c_str(), result.to_string().c_str());
        return false;
    }
}

inline bool test_multiplication() {
    LongNumber a(12.34);
    LongNumber b(5.6);
    LongNumber expected(69.104);

    LongNumber result = a * b;

    if (result == expected) {
        return true;
    } else {
        printf("Expected: %s, Got: %s\n", expected.to_string().c_str(), result.to_string().c_str());
        return false;
    }
}

inline bool test_division() {
    LongNumber a(100.0);
    LongNumber b(4.0);
    LongNumber expected(25.0);

    LongNumber result = a / b;

    if (result == expected) {
        return true;
    } else {
        printf("Expected: %s, Got: %s\n", expected.to_string().c_str(), result.to_string().c_str());
        return false;
    }
}
