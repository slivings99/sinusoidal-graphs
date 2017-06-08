#include "pinumber.h"
#include <cmath>
#include <QString>

PiNumber::PiNumber(float value)
{
    setValue(value);
}

int PiNumber::mMaxDenominator = 25;
float PiNumber::mPrecision = 0.0001;
bool PiNumber::mRunTest = false;

void PiNumber::setPrecision(int precision)
{
    PiNumber::mPrecision = precision;
}

void PiNumber::setRunTest(bool runTest)
{
    PiNumber::mRunTest = runTest;
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
        if (mRunTest)
        {
            printf ("Whole Multiple of Pi: %d π \n", wholeNumber);
        }
    }
    else
    {
        if (mRunTest)
        {
            printf ("Ratio: %0.03f\n", piRatio);
        }
        ClosestFraction(piRatio, mMaxDenominator, thisNumerator, thisDenominator);
        float ratio = (float) thisNumerator / (float) thisDenominator;
        if ( std::abs(piRatio - ratio) < mPrecision) {
            mIsFractionOfPi = true;
            mPiCoefficient = thisNumerator + wholeNumber*thisDenominator;
            mDenominator = thisDenominator;
            if (mRunTest)
            {
                printf("Fraction: %d π / %d\n", mPiCoefficient, thisDenominator);
            }
        }
        else {
            if (mRunTest)
            {
                printf("Value: %0.2f\n", mValue);
            }
            mIsFractionOfPi = false;
            mPiCoefficient = 0;
            mDenominator = 0;
        }
    }
}

QString PiNumber::displayValue()
{
    QString output;
    if (mIsFractionOfPi)
    {
        output = QString("Hello");
    }
    else
    {
        output = QString("%1").arg(mValue);
    }
    return(output);
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
