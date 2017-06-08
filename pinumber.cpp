#include "pinumber.h"
#include <cmath>

PiNumber::PiNumber(float value)
{
    setValue(value);
}

int PiNumber::mMaxDenominator = 50;
float PiNumber::mPrecision = 0.01;

void PiNumber::setPrecision(int precision)
{
    PiNumber::mPrecision = precision;
}

void PiNumber::setValue(float value)
{
    int thisNumerator, thisDenominator = 0;
    float   piRatio = value / M_PI;
    int wholeNumber = 0;

    mValue = value;

    // Extract the whole number part.
    while (piRatio >= 1.0f)
    {
        piRatio -= 1.0f;
        wholeNumber += 1;
    }
    if (piRatio == 0.0f)
    {
        mIsFractionOfPi = true;
        mPiCoefficient = wholeNumber;
        mDenominator = 1;
//        printf ("%d π \n", wholeNumber);
    }
    else
    {
//        printf ("%0.03f\n", piRatio);
        ClosestFraction(piRatio, mMaxDenominator, thisNumerator, thisDenominator);
//        printf ("%d / %d\n",thisNumerator, thisDenominator);
        float ratio = (float) thisNumerator / (float) thisDenominator;
        if ( std::abs(piRatio - ratio) < mPrecision) {
            mIsFractionOfPi = true;
            mPiCoefficient = thisNumerator + wholeNumber*thisDenominator;
            mDenominator = thisDenominator;
//            printf("%d π / %d\n", mPiCoefficient, thisDenominator);
        }
        else {
//            printf("%0.2f\n", mValue);
            mIsFractionOfPi = false;
            mPiCoefficient = 0;
            mDenominator = 0;
        }
    }
}

void PiNumber::ClosestFraction( float value, int max_denominator, int & numerator, int & denominator )
{
    int low_n = 0;
    int low_d = 1;
    int high_n = 1;
    int high_d = 1;
    int mid_n;
    int mid_d;

    do
    {
        mid_n = low_n + high_n;
        mid_d = low_d + high_d;
        if ( mid_n < value * mid_d )
        {
            low_n = mid_n;
            low_d = mid_d;
            numerator = high_n;
            denominator = high_d;
        }
        else
        {
            high_n = mid_n;
            high_d = mid_d;
            numerator = low_n;
            denominator = low_d;
        }
    } while ( mid_d <= max_denominator );
}
