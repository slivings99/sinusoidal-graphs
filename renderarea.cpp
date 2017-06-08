#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>
#include <cmath>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mCurvePen (Qt::darkBlue),
    mAxisPen (Qt::black),
    mIntervalLength(M_PI),
    mStepCount(256),
    mScale (1.0),
    mPeriod(2*M_PI),
    mAmplitude(1),
    mPhaseShift(0),
    mMidline(0)
{
    setBackgroundColor(Qt::white);
}

int RenderArea::mBuffer = 20; // 20 pixels on each side of the curve

QSize RenderArea::minimumSizeHint() const
{
    return QSize(400,400);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400,400);
}

void RenderArea::setYRatio()
{
    float distanceFromX = std::abs(mMidline)+mAmplitude;
    float curveHeight = 2 * mAmplitude; // mAmplitude is always positive
    if (distanceFromX > curveHeight)  // The x axis will be on an edge
    {
        mYRatio = (float)(this->height() - 2*mBuffer) / distanceFromX;
        if (mMidline < 0)
        {   // x-axis at top of drawing area
            mXAxisYValue = mBuffer;
        }
        else
        {   // x-axis at the bottom of the drawing area
            mXAxisYValue = this->height() - mBuffer;
        }
    }
    else
    {
        mYRatio = (float)(this->height() - 2*mBuffer) / curveHeight;
        mXAxisYValue = (int) std::round((mAmplitude + mMidline) * mYRatio) + mBuffer;
    }
}

void RenderArea::setXRatio()
{
    float period = mPeriod.value();
    float phaseShift = mPhaseShift.value();
/* Not needed, pinumber class will take care of this.
    if (mPeriodTimesPi)
    {
        period *= M_PI;
    }
    if (mPhaseShiftTimesPi)
    {
        phaseShift *= M_PI;
    }
*/
    if ((phaseShift < 0) || (phaseShift < period / 4))
    {
        mIntervalLength = 1.5 * period; // graph extra 1/4 period on each side of one cycle
        mXStart = -(0.25 * period - phaseShift);
        mXRatio = (float)(this->width() - 2*mBuffer) / mIntervalLength;
        mYAxisXValue = mBuffer + (int) std::round((0.25 * period - phaseShift)*mXRatio);
    }
    else
    {
        mIntervalLength = 1.25 * period + phaseShift;
        mXStart = 0;
        mXRatio = (float)(this->width() - 2*mBuffer) / mIntervalLength;
        mYAxisXValue = mBuffer; // y axis on left side of graph
    }
}


void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(mBackgroundColor);
    // Drawing area
    painter.drawRect(this->rect());

    painter.setPen(mCurvePen);


    // Test values for locateXaxis()
    mMidline = -2.0;
    mAmplitude = 1.0;

    // Test values for locateYaxis()
    mPeriod.setValue(2 * M_PI);
    mPhaseShift.setValue(- M_PI / 4);

    painter.setPen(mAxisPen);

    setXRatio();

    QPoint xAxisStart(0,mXAxisYValue);
    QPoint xAxisEnd(this->width(), mXAxisYValue);
    painter.drawLine(xAxisStart,xAxisEnd); // x - axis

    setYRatio();

    QPoint yAxisStart(mYAxisXValue,0);
    QPoint yAxisEnd(mYAxisXValue,this->height());
    painter.drawLine(yAxisStart,yAxisEnd); // y - axis

    QPoint origin(mYAxisXValue,mXAxisYValue);

    float a, b, c, d; // f(x) = asin(b(x-c))+d
    a = mAmplitude;
    if (mNegative)
    {
        a *= -1.0;
    }
    b = 2 * M_PI / mPeriod.value();
    c = mPhaseShift.value();
    d = mMidline;

    float y = (a * sin(b * (mXStart - c)) + d)*mYRatio;
    QPoint prevPixel;
    prevPixel.setX(mBuffer);
    prevPixel.setY(origin.y() - y); // subtract y because y = 0 at the top of the screen
    float step = mIntervalLength / mStepCount;

    painter.setPen(mCurvePen);

    for (float t = mXStart; t < (mIntervalLength + mXStart); t+=step)
    {
        QPoint pixel;
        y = (a * sin(b * (t - c)) + d)*mYRatio;
        pixel.setX(t*mXRatio + origin.x());
        pixel.setY(origin.y() - y); // subtract y because y = 0 at the top of the screen
        painter.drawLine(pixel, prevPixel);
        prevPixel = pixel;
    }
    QPoint pixel;
    float t = mIntervalLength + mXStart;
    pixel.setX(t*mXRatio + origin.x());
    y = (a * sin(b * (t - c)) + d)*mYRatio;
    pixel.setY(origin.y() - y); // subtract y because y = 0 at the top of the screen
    painter.drawLine(pixel, prevPixel);
}
/*  THIS IS WHERE I AM, CONTINUE TO UPDATE paintEvent to paint a sine curve.

    QPointF prevPoint = compute(0);
    QPoint prevPixel;
    prevPixel.setX(prevPoint.x() * mScale + center.x());
    prevPixel.setY(prevPoint.y() * mScale + center.y());

    float step = mIntervalLength / mStepCount;

    for (float t = 0; t < mIntervalLength; t += step)
    {
        QPointF point = compute (t);

        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y());

//        painter.drawPoint(pixel);
        painter.drawLine(pixel, prevPixel);
        prevPixel = pixel;
    }
    QPointF point = compute (mIntervalLength);

    QPoint pixel;
    pixel.setX(point.x() * mScale + center.x());
    pixel.setY(point.y() * mScale + center.y());
    painter.drawLine(pixel, prevPixel);
}
*/
