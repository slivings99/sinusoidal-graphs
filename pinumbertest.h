#ifndef PINUMBERTEST_H
#define PINUMBERTEST_H

#include "pinumber.h"
#include <cstdio>
#include <array>

class PiNumberTest
{
public:
    PiNumberTest(int typeOfTest);

private:
    PiNumber    mPiNumber;
    std::array<float, 18> testValues
    { {
        3 * M_PI,
        3.2,    // not a multiple of pi
        1.5708, // approx 0.5 pi
        M_PI / 3,
        M_PI / 4,
        4.7124, // approx 3/2 pi
        4.712389, // closer approx 3/2 pi
        5 * M_PI / 4,
        4 * M_PI / 3,
        4.19, // approx 4/3 pi
        4.1888, // closer approx 4/3 pi
        4.18879, // closest approx
        M_PI,
        2.0,
        3.0,
        4.0,
        0.5,
        0.25
    } };
};

#endif // PINUMBERTEST_H
