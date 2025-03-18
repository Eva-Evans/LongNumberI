#include <iostream>
#include <chrono>
#include <assert.h>
#include <iomanip>
#include <cmath>
#include "../include/longnumber.hpp"
#include "../include/test_system.hpp"

using namespace TestSystem;

TestResult TestSystem::run_test(
    const char* name,
    TestScenario test,
    size_t timeout_ms /* = 1000U */,
    bool inspect /* = false */)
{
    if (inspect) {
        printf("Running test %s with timeout %zu ms\n", name, timeout_ms);
    } else {
        printf("Running test %s\n", name);
    }

    bool result = test();
    return result ? OK : FAIL;
}

bool test_addition() {
    std::cout << "Starting test_addition...\n";
    LongNumber a(123.45);
    LongNumber b(67.89);
    LongNumber expected(191.34);

    std::cout << "Performing addition...\n";
    LongNumber result = a + b;

    if (result == expected) {
        std::cout << "Addition test passed.\n";
        return true;
    } else {
        printf("Expected: %s, Got: %s\n", expected.to_string().c_str(), result.to_string().c_str());
        return false;
    }
}

bool test_subtraction() {
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

bool test_multiplication() {
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

bool test_division() {
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


double arctan_taylor(double x, int terms) {
    double result = 0.0;
    for (int n = 0; n < terms; ++n) {
        double term = std::pow(-1, n) * std::pow(x, 2 * n + 1) / (2 * n + 1);
        result += term;
    }
    return result;
}



size_t LongNumber::precision = 50;

int main() {
    
    size_t precision;

    std::cout << "Enter Pi precision: ";
    std::cin >> precision;
    LongNumber::precision = precision;
    int terms = 1000000;

    double arctan_1_5 = arctan_taylor(1.0 / 5, terms);
    double arctan_1_239 = arctan_taylor(1.0 / 239, terms);
    long double pi = 16 * arctan_1_5 - 4 * arctan_1_239;
    std::cout << "Calculated Pi: " << std::setprecision(precision) << pi << std::endl;
    std::cout << "Actual Pi:     " << std::setprecision(precision) << M_PI << std::endl;

    LongNumber::precision = precision;

    TestSystem::run_test("AdditionDig", test_addition);
    TestSystem::run_test("SubtractionDig", test_subtraction);
    TestSystem::run_test("MultiplicationDigComb", test_multiplication);
    TestSystem::run_test("findApproximateDivision", test_division);



    return 0;
}