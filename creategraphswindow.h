#ifndef CREATEGRAPHSWINDOW_H
#define CREATEGRAPHSWINDOW_H

#include <QDialog>

namespace Ui {
class CreateGraphsWindow;
}

class CreateGraphsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreateGraphsWindow(QWidget *parent = 0);
    ~CreateGraphsWindow();

private slots:
    void on_btnCloseWindow_clicked();

    void on_btnResetDefaults_clicked();

    void on_spinMidline_valueChanged(double arg1);

    void on_checkPhaseShiftTimesPi_clicked();

    void on_spinPhaseShift_valueChanged(double arg1);

    void on_spinPeriod_valueChanged(double arg1);

    void on_checkPeriodTimesPi_clicked();

    void on_checkPhaseShiftTimesPi_stateChanged(int arg1);

    void on_spinAmplitude_valueChanged(double arg1);

    void on_checkNegative_stateChanged(int arg1);

    void on_checkPeriodTimesPi_stateChanged(int arg1);

    void on_radioSine_clicked();

    void on_radioCosine_clicked();

private:
    void updatePeriod();
    void updatePhaseShift();
    Ui::CreateGraphsWindow *ui;
    float mAmplitude;
    float mPeriod;
    float mMidline;
};

#endif // CREATEGRAPHSWINDOW_H
