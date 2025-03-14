#include <iostream>
#include <chrono>
#include <assert.h>
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


void find_PI() {
    auto start = std::chrono::high_resolution_clock::now();

    LongNumber Pi(0);
    LongNumber hex(1);
    for(int k = 0; k < 0.8 * LongNumber::precision + 5; k++) {
        LongNumber sec = LongNumber(4) / LongNumber(8 * k + 1);
        LongNumber third = LongNumber(2) / LongNumber(8 * k + 4);
        LongNumber fourth = LongNumber(1) / LongNumber(8 * k + 5);
        LongNumber fifth = LongNumber(1) / LongNumber(8 * k + 6);
        Pi = Pi + (sec - third - fourth - fifth) * hex;
        hex = hex / LongNumber(16);
    }

    std::cout << Pi << '\n';

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = end - start;
    std::cout << "Time: " << time.count() << '\n';
}
size_t LongNumber::precision = 50;

int main() {


    size_t precision;

    std::cout << "Enter Pi precision: ";
    std::cin >> precision;

    LongNumber::precision = precision;

    find_PI();

    try {
        std::cout << "Running Addition test...\n";
        TestResult addition_result = TestSystem::run_test("Addition", test_addition);
        std::cout << "Addition test completed with result: " << (addition_result == OK ? "PASS" : "FAIL") << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Exception in Addition test: " << e.what() << "\n";
    }

    try {
        std::cout << "Running Subtraction test...\n";
        TestResult subtraction_result = TestSystem::run_test("Subtraction", test_subtraction);
        std::cout << "Subtraction test completed with result: " << (subtraction_result == OK ? "PASS" : "FAIL") << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Exception in Subtraction test: " << e.what() << "\n";
    }

    try {
        std::cout << "Running Multiplication test...\n";
        TestResult multiplication_result = TestSystem::run_test("Multiplication", test_multiplication);
        std::cout << "Multiplication test completed with result: " << (multiplication_result == OK ? "PASS" : "FAIL") << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Exception in Multiplication test: " << e.what() << "\n";
    }

    try {
        std::cout << "Running Division test...\n";
        TestResult division_result = TestSystem::run_test("Division", test_division);
        std::cout << "Division test completed with result: " << (division_result == OK ? "PASS" : "FAIL") << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Exception in Division test: " << e.what() << "\n";
    }

    return 0;
}