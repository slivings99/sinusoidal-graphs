#include "pinumber.h"
#include <cmath>
#include <QString>
#include <QDebug>

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
    float   piRatio = std::abs(value) / M_PI; // piRatio starts as positive
    int wholeNumber = 0;

    mValue = value;

    // Extract the whole number part.
    if (piRatio >= 1.0f)
    {
        wholeNumber = std::trunc(piRatio);
        piRatio = piRatio - (float) wholeNumber;
    }
    if (piRatio == 0.0f)
    {
        mIsFractionOfPi = true;
        mPiCoefficient = wholeNumber;
        if (value < 0)  // take into account the negative input here at the end.
        {
            mPiCoefficient = (-1)*mPiCoefficient;
        }
        mDenominator = 1;
        if (mRunTest)
        {
            qDebug() << QString("Whole Multiple of Pi: %1 π").arg(mPiCoefficient);
        }
    }
    else
    {
        if (mRunTest)
        {
            qDebug() << "Ratio: " << QString::number(piRatio, 'f', 3);
        }
        ClosestFraction(piRatio, mMaxDenominator, thisNumerator, thisDenominator);
        float ratio = (float) thisNumerator / (float) thisDenominator;
        if ( std::abs(piRatio - ratio) < mPrecision) {
            mIsFractionOfPi = true;
            mPiCoefficient = thisNumerator + wholeNumber*thisDenominator;
            mDenominator = thisDenominator;
            if (value < 0)  // take into account the negative input here at the end.
            {
                mPiCoefficient = (-1)*mPiCoefficient;
            }
            if (mRunTest)
            {
                qDebug() << "Fraction: " << QString::number(mPiCoefficient) << "π / " << QString::number(thisDenominator);
            }
        }
        else {
            if (mRunTest)
            {
                qDebug() << "Value: " << QString::number(mValue, 'f', 2);
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
        if (std::abs(mPiCoefficient) != 1)
        {
            output = QString("%1 π").arg(mPiCoefficient);
        }
        else
        {
            if (mPiCoefficient < 0)
            {
                output = QString ("-π");
            }
            else
            {
                output = QString("π");
            }
        }
        if (mDenominator != 1)
        {
            output.append(QString(" / %1").arg(mDenominator));
        }
    }
    else
    {
//        output = QString("%1").arg(QString::number(mValue,'f', 3));
        output = QString::number(mValue,'f', 3);
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
