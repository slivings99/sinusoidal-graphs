#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>
#include <cmath>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mCurvePen (Qt::darkBlue),
    mAxisPen (Qt::black),
    mScale (1.0),
    mIntervalLength(M_PI),
    mStepCount(256),
    mAmplitude(1),
    mPeriod(2*M_PI),
    mPhaseShift(0),
    mMidline(0)
{
    setBackgroundColor(Qt::white);
}

int RenderArea::mBuffer = 10; // 10 pixels on each side of the curve

QSize RenderArea::minimumSizeHint() const
{
    return QSize(400,400);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400,400);
}

void RenderArea::setXRatio()
{
    float distanceFromX = std::abs(mMidline)+mAmplitude;
    float curveHeight = 2 * mAmplitude; // mAmplitude is always positive
    if (distanceFromX > curveHeight)  // The x axis will be on an edge
    {
        mXRatio = (float)(this->height() - 2*mBuffer) / distanceFromX;
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
        mXRatio = (float)(this->height() - 2*mBuffer) / curveHeight;
        mXAxisYValue = (int) std::round((mAmplitude * mXRatio) + (mMidline * mXRatio));
    }
}

void RenderArea::setYRatio()
{
    float curveWidth;

    if (mPhaseShift < 0)
    {
        curveWidth = mPeriod * 1.5; // graph extra 1/4 period on each side of one cycle
        mYRatio = (float)(this->width() - 2*mBuffer) / curveWidth;
        mYAxisXValue = mBuffer + (int) std::round((0.25 * mPeriod - mPhaseShift)*mYRatio);
    }
    else
    {
        if (mPhaseShift > mPeriod / 4)
        {
            curveWidth = mPeriod * 1.25 + mPhaseShift;
            mYRatio = (float)(this->width() - 2*mBuffer) / curveWidth;
            mYAxisXValue = mBuffer; // y axis on left side of graph
        }
        else
        {
            curveWidth = 1.5 * mPeriod;
            mYRatio = (float)(this->width() - 2*mBuffer) / curveWidth;
            mYAxisXValue = mBuffer + (int) std::round( (mPeriod/4 - mPhaseShift)*mYRatio );
        }
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


    QPoint center = this->rect().center();
    QPoint zeroZero(0,0);
//    painter.drawLine(zeroZero,center);

/*    // Test values for locateXaxis()
    mMidline = 4.0;
    mAmplitude = 6.0;
*/
/*    // Test values for locateYaxis()
    mPeriod = 2 * M_PI;
    mPhaseShift = M_PI / 8;
*/
    painter.setPen(mAxisPen);

    setXRatio();

    QPoint xAxisStart(0,mXAxisYValue);
    QPoint xAxisEnd(this->width(), mXAxisYValue);
    painter.drawLine(xAxisStart,xAxisEnd); // x - axis

    setYRatio();
    QPoint yAxisStart(mYAxisXValue,0);
    QPoint yAxisEnd(mYAxisXValue,this->height());
    painter.drawLine(yAxisStart,yAxisEnd); // y - axis

    float a, b, c, d; // f(x) = asin(b(x+c))+d
    painter.setPen(mCurvePen);
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
