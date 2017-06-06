#ifndef PINUMBER_H
#define PINUMBER_H

#include <cmath>
#include <cstdio>

class PiNumber
{
public:
    explicit PiNumber(float value = 0);
    void setValue(float value);
    int Denominator() const {return mDenominator;} // getter
    int numerator() const {return mPiCoefficient;} // getter
    bool IsFractionOfPi() const {return mIsFractionOfPi;} // getter
    float value() const {return mValue; } // getter
    static void ClosestFraction ( float value, int max_denominator, int & numerator, int & denominator );
    static void setPrecision (int precision); // setter

private:
    float   mValue;
    bool    mIsFractionOfPi;
    int     mPiCoefficient;
    int     mDenominator;
    static float mPrecision;
    static int mMaxDenominator;
};

#endif // PINUMBER_H
