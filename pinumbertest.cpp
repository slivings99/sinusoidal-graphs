#include "pinumbertest.h"
#include <QDebug>

PiNumberTest::PiNumberTest( int typeOfTest):
    mPiNumber(0.0f)
{
    if(typeOfTest == 1)
    {
        PiNumber::setRunTest(true);

        for (const auto& value: testValues) {
            qDebug() << QString::number (value, 'f', 2);
            mPiNumber.setValue(value);
        }
    }
    PiNumber::setRunTest(false);
}

