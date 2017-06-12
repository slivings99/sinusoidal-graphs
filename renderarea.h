#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>
#include <QPen>
#include <QLabel>
#include <QString>
#include <QPaintEvent>
#include <QPainter>
#include "pinumber.h"

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    enum FunctionType {
        FunctSine,
        FunctCosine
    };

    explicit RenderArea(QWidget *parent = 0);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setBackgroundColor (QColor color) { mBackgroundColor = color; } // setter
    QColor backgroundColor () const { return mBackgroundColor; } // getter

    void setCurveColor (QColor color) { mCurvePen.setColor(color); } // setter
    QColor curveColor () const { return mCurvePen.color(); } // getter

    void setAxisColor (QColor color) { mAxisPen.setColor(color); } // setter
    QColor axisColor () const { return mAxisPen.color(); } // getter

    void setScale (float scale) { mScale = scale; repaint(); } // setter
    float scale () const { return mScale; } // getter

    void setInterval (float interval) { mIntervalLength = interval; repaint(); } // setter
    float interval () const { return mIntervalLength; } // getter

    void setStepCount (int stepCount) { mStepCount = stepCount; repaint(); } // setter
    int stepCount () const { return mStepCount; } // getter

    void setPeriod (PiNumber period) { mPeriod = period; repaint(); } // setter
    PiNumber period () const { return mPeriod; } // getter

    void setAmplitude (float amplitude) { mAmplitude = amplitude; repaint(); } // setter
    float amplitude () const { return mAmplitude; } // getter

    void setPhaseShift (PiNumber phaseShift) { mPhaseShift = phaseShift; repaint(); } // setter
    PiNumber phaseShift () const { return mPhaseShift; } // getter

    void setMidline (float midline) { mMidline = midline; repaint(); } // setter
    float midline () const { return mMidline; } // getter

    void setNegative (bool negative) { mNegative = negative; repaint(); } // setter
    bool negative () const { return mNegative; } // getter

    void setShowParentFunction (bool showParent) { mShowParentFunction = showParent; repaint(); } // setter
    bool showParentFunction () const { return mShowParentFunction; } // getter

    void setFunctionType (FunctionType function) { mFunction = function; repaint(); }
    FunctionType functionType () const {return mFunction;}

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:

private:
    QColor mBackgroundColor;
    QPen mCurvePen;
    QPen mAxisPen;
    QPen mMidLinePen;

    float mIntervalLength;
    int mStepCount;
    float mScale;

    PiNumber mPeriod; // Always positive number
    float mAmplitude; // Always positive, with mNegative implementing x-axis reflections.
    PiNumber mPhaseShift; // Positive or negative, but checks to keep it less than 1 whole period.
    float mMidline;
    bool mNegative;

    bool mShowParentFunction;

    static int mBuffer; // used for the buffer around the curve in the drawing area
    float mXRatio;
    float mYRatio;
    QPoint mOrigin;
    int mXAxisYValue;
    int mYAxisXValue;
    int mMidlineYValue;
    float mXStart;
    FunctionType mFunction;

    void setXRatio () ;
    void setYRatio () ;
    float calculate (float t, float a, float b, float c, float d);
    void displayCurve (QPainter *painter, float a, float b, float c, float d);
    QLabel functionLabel;
    QLabel midlineLabel;
    QLabel maximumLabel;
    QLabel minimumLabel;
    QLabel *xLabels[7];
    QLabel phaseShiftLabel;
    QString functionString;
};

#endif // RENDERAREA_H
