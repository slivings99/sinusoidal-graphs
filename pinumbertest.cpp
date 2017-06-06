#include "pinumbertest.h"

PiNumberTest::PiNumberTest( int typeOfTest):
    mPiNumber(0.0f)
{
    if(typeOfTest == 1)
    {
        printf("Hello world.\n");

        for (const auto& value: testValues) {
            printf("%2.2f \n", value);
            mPiNumber.setValue(value);
        }
    }
}

