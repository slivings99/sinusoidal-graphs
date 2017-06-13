#include "renderarea.h"
#include <cmath>

RenderArea::RenderArea(QWidget *parent) :
    QWidget(parent),
    mCurvePen (Qt::darkBlue),
    mAxisPen (Qt::black),
    mMidLinePen(Qt::black),
    mIntervalLength(M_PI),
    mStepCount(256),
    mScale (1.0),
    mPeriod(2*M_PI),
    mAmplitude(1),
    mPhaseShift(0),
    mMidline(0),
    mNegative(false),
    mShowParentFunction(false),
    mXRatio(1),
    mYRatio(1),
    mOrigin(0,0),
    mXAxisYValue(0),
    mYAxisXValue(0),
    mMidlineYValue(0),
    mXStart(0),
    mFunction(FunctSine)
{
    setBackgroundColor(Qt::white);
    functionLabel.setParent(this);
    midlineLabel.setParent(this);
    maximumLabel.setParent(this);
    minimumLabel.setParent(this);
    for (int x = 0; x < 7; x++)
    {
        xLabels[x] = new QLabel(this);
    }
    phaseShiftLabel.setParent(this);
    mMidLinePen.setStyle(Qt::DashLine);
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
    mMidlineYValue = mXAxisYValue - (int) std::round(mMidline*mYRatio);
}

void RenderArea::setXRatio()
{
    float period = mPeriod.value();
    float phaseShift = mPhaseShift.value();
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

float RenderArea::calculate(float t,
                            float a,
                            float b,
                            float c,
                            float d)
{
    float y;

    switch (mFunction)
    {
    case FunctSine:
        y = (a * sin(b * (t - c)) + d)*mYRatio;
        break;
    case FunctCosine:
        y = (a * cos(b * (t - c)) + d)*mYRatio;
        break;
    default:
        y = t*mYRatio;
        break;
    }
    return (y);
}

void RenderArea::displayCurve(QPainter *painter, float a, float b, float c, float d)
{
    float y = calculate(mXStart,a,b,c,d);
    QPoint prevPixel;
    prevPixel.setX(mBuffer);
    prevPixel.setY(mOrigin.y() - y); // subtract y because y = 0 at the top of the screen
    float step = mIntervalLength / mStepCount;


    for (float t = mXStart; t < (mIntervalLength + mXStart); t+=step)
    {
        QPoint pixel;
        y = calculate(t,a,b,c,d);
        pixel.setX(t*mXRatio + mOrigin.x());
        pixel.setY(mOrigin.y() - y); // subtract y because y = 0 at the top of the screen
        painter->drawLine(pixel, prevPixel);
        prevPixel = pixel;
    }
    QPoint pixel;
    float t = mIntervalLength + mXStart;
    pixel.setX(t*mXRatio + mOrigin.x());
    y = calculate(t,a,b,c,d);

    pixel.setY(mOrigin.y() - y); // subtract y because y = 0 at the top of the screen
    painter->drawLine(pixel, prevPixel);
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter    painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(mBackgroundColor);
    // Drawing area
    painter.drawRect(this->rect());

//    painter.setPen(mCurvePen);


//    // Test values for setYRatio()
//    mMidline = -2.0;
//    mAmplitude = 1.0;

//    // Test values for setXRatio()
//    mPeriod.setValue(2 * M_PI);
//    mPhaseShift.setValue(- M_PI / 4);

    setXRatio();
    setYRatio();

    painter.setPen(mAxisPen);

    QPoint xAxisStart(0,mXAxisYValue);
    QPoint xAxisEnd(this->width(), mXAxisYValue);
    painter.drawLine(xAxisStart,xAxisEnd); // x - axis

    QPoint yAxisStart(mYAxisXValue,0);
    QPoint yAxisEnd(mYAxisXValue,this->height());
    painter.drawLine(yAxisStart,yAxisEnd); // y - axis

    mOrigin.setX(mYAxisXValue);
    mOrigin.setY(mXAxisYValue);

    // Set up some y axis labels:
    QPoint labelStart(mYAxisXValue-3,mOrigin.y());
    QPoint labelEnd(mYAxisXValue+3,mOrigin.y());
    if (mMidlineYValue != mXAxisYValue)
    {
        // Draw mid-line as a dashed line
        painter.setPen(mMidLinePen);
        QPoint midLineStart(0,mMidlineYValue);
        QPoint midLineEnd(this->width(), mMidlineYValue);
        painter.drawLine(midLineStart, midLineEnd);
        // Label y axis with midline value:
        labelStart.setY(mMidlineYValue);
        labelEnd.setY(mMidlineYValue);
        painter.drawLine(labelStart, labelEnd);
        midlineLabel.setText(QString("y = %1").arg(mMidline));
        midlineLabel.adjustSize();
        midlineLabel.move(mYAxisXValue+1,mMidlineYValue+1);
        midlineLabel.show();
    }
    else
    {
        midlineLabel.hide();
    }
    // Label y axis with minimum and maximum values:
    painter.setPen(mAxisPen);
    int minimumYValue = mMidlineYValue + (int) std::round(mAmplitude*mYRatio);
    if (minimumYValue != mXAxisYValue) // Only display this value if other than at the origin.
    {
        labelStart.setY(minimumYValue);
        labelEnd.setY(minimumYValue);
        painter.drawLine(labelStart, labelEnd);
        // y axis labels are to the left of the y axis and centered on their y values.
        minimumLabel.setText(QString("%1").number(mMidline-mAmplitude));
        minimumLabel.adjustSize();
        minimumLabel.move(mYAxisXValue - minimumLabel.size().width() - 2, minimumYValue - minimumLabel.size().height()/2);
        minimumLabel.show();
    }
    else
    {
        minimumLabel.hide();
    }
    int maximumYValue = mMidlineYValue - (int) std::round(mAmplitude*mYRatio);
    if (maximumYValue != mXAxisYValue) // Only display this value if other than at the origin.
    {
        labelStart.setY(maximumYValue);
        labelEnd.setY(maximumYValue);
        painter.drawLine(labelStart, labelEnd);
        maximumLabel.setText(QString("%1").number(mMidline+mAmplitude));
        maximumLabel.adjustSize();
        maximumLabel.move(mYAxisXValue - maximumLabel.size().width() - 2, maximumYValue - maximumLabel.size().height()/2);
        maximumLabel.show();
    }
    else
    {
        maximumLabel.hide();
    }

    // Label x axis with quarter period values:
    for (int xValue = 0; xValue < 7; xValue++)
    {
        float t = mXStart + (mPeriod.value()*0.25)*(float)xValue;
        int xPixelValue = mBuffer + ((this->width()-2*mBuffer)/6)*xValue;
        PiNumber xDisplayValue(t);
        labelStart.setX(xPixelValue);
        labelStart.setY(mXAxisYValue - 3);
        labelEnd.setX(xPixelValue);
        labelEnd.setY(mXAxisYValue + 3);
        painter.drawLine(labelStart, labelEnd);
        xLabels[xValue]->setText(QString("%1").arg(xDisplayValue.displayValue()));
        xLabels[xValue]->adjustSize();
        switch (xValue)
        {
        case (0): // left most label needs to be right aligned.
            xLabels[xValue]->move(xPixelValue - mBuffer, mXAxisYValue + 4);
            break;
        case(6): // right most label needs to be left aligned.
            xLabels[xValue]->move(xPixelValue - xLabels[xValue]->size().width() + mBuffer, mXAxisYValue + 4);
            break;
        default: // All others are centered.
            xLabels[xValue]->move(xPixelValue - xLabels[xValue]->size().width()/2,mXAxisYValue + 4);
            break;
        }
        xLabels[xValue]->show();
    }

    float a, b, c, d; // f(x) = asin(b(x-c))+d

    functionString = QString("f(x) = ");
    a = mAmplitude;
    if (mNegative)
    {
        a *= -1.0;
        functionString.append("-");
    }
    if (std::abs(a) != 1.0)
    {
        functionString.append(QString::number(std::abs(a)));
    }
    switch (mFunction)
    {
    case FunctSine:
        functionString.append("sin(");
        break;
    case FunctCosine:
        functionString.append("cos(");
        break;
    default:
        break;
    }

    b = 2 * M_PI / mPeriod.value();
    PiNumber bPi(b);
    c = mPhaseShift.value();
    PiNumber cPi(c);
    if (b != 1.0)
    {
        functionString.append(QString("(%1)").arg(bPi.displayValue()));
        functionString.append("(");
    }
    functionString.append("x");
    if (c != 0)
    {   if (c > 0)
        {
            functionString.append("+");
        }
        functionString.append(cPi.displayValue());
    }
    if (b!= 1.0)
    {
        functionString.append(")");
    }
    functionString.append(")");
    d = mMidline;
    if (d > 0)
    {
        functionString.append("+");
    }
    if (d != 0)
    {
        functionString.append(QString::number(d));
    }
// Display the primary function graph
    painter.setPen(mCurvePen);
    displayCurve(&painter, a,b,c,d);
    if (showParentFunction())
    {
        painter.setPen(mAxisPen);
        displayCurve(&painter, 1, 1, 0, 0);
        painter.setPen(mCurvePen);
    }

    functionLabel.setText(functionString);
    functionLabel.adjustSize();
    functionLabel.move(mOrigin.x()+2,0);
    functionLabel.show();
}
