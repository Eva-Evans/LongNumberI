#include <iostream>
#include <chrono>
#include <assert.h>
#include "../include/longnumber.hpp"


//size_t LongNumber::precision = 50;

int main() {
    //size_t precision;

    //assert(LongNumber(154.3) * LongNumber(14.2) == LongNumber(2191.06));
    // assert((LongNumber(-15) / LongNumber(-3)) == LongNumber(5));
    assert(LongNumber(0) * LongNumber(1543) == LongNumber(154300000));
    //assert(LongNumber("-8238234.175645") + LongNumber("83346393.24854") == LongNumber(-8238234.175645 + 83346393.24854));
    //assert(LongNumber("-0") - LongNumber(0) == LongNumber("0"));

    //LongNumber::precision = precision;

    return 0;
}
