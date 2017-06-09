#include "creategraphswindow.h"
#include "ui_creategraphswindow.h"
#include "pinumber.h"
#include <cstdio>

CreateGraphsWindow::CreateGraphsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGraphsWindow)
{
    ui->setupUi(this);
}

CreateGraphsWindow::~CreateGraphsWindow()
{
    delete ui;
}

void CreateGraphsWindow::on_btnCloseWindow_clicked()
{
    this->hide();
}

void CreateGraphsWindow::on_btnResetDefaults_clicked()
{
    this->ui->spinAmplitude->setValue(1.0);
    this->ui->checkNegative->setChecked(false);
    this->ui->spinMidline->setValue(0);
    this->ui->spinPeriod->setValue(2);
    this->ui->checkPeriodTimesPi->setChecked(true);
    this->ui->spinPhaseShift->setValue(0);
    this->ui->checkPhaseShiftTimesPi->setChecked(true);
    this->ui->renderArea->repaint();
}

void CreateGraphsWindow::on_spinMidline_valueChanged(double midline)
{
    this->ui->renderArea->setMidline(midline);
    this->ui->renderArea->repaint();
}

void CreateGraphsWindow::updatePhaseShift()
{
    float   value = this->ui->spinPhaseShift->value();
    float   period = this->ui->renderArea->period().value();
    float   maxValue;

    maxValue = period;
    if (this->ui->checkPhaseShiftTimesPi->isChecked())
    {
        maxValue = maxValue / M_PI;
    }
    this->ui->spinPhaseShift->setMaximum(maxValue);
    this->ui->spinPhaseShift->setMinimum(-maxValue);
    if (this->ui->checkPhaseShiftTimesPi->isChecked())
    {
        value *= M_PI;
    }
    if (value >= period)
    {
        value = std::fmod(value,period);
    }
    PiNumber phaseShift(value);
    this->ui->renderArea->setPhaseShift(phaseShift);
    this->ui->renderArea->repaint();
}

void CreateGraphsWindow::on_spinPhaseShift_valueChanged(double value)
{
    Q_UNUSED(value);

    updatePhaseShift();
}

void CreateGraphsWindow::on_checkPhaseShiftTimesPi_stateChanged(int checkState)
{
    Q_UNUSED(checkState);

    updatePhaseShift();
}

void CreateGraphsWindow::on_checkPhaseShiftTimesPi_clicked()
{

}

void CreateGraphsWindow::updatePeriod()
{
    float   value = this->ui->spinPeriod->value();

    if (value > 0.0) // Period must always be more than 0.
    {
        if (this->ui->checkPeriodTimesPi->isChecked())
        {
            value *= M_PI;
        }
        PiNumber period(value);
        this->ui->renderArea->setPeriod(period);
        this->ui->renderArea->repaint();
    }

}

void CreateGraphsWindow::on_spinPeriod_valueChanged(double value)
{
    Q_UNUSED(value);

    updatePeriod();
}

void CreateGraphsWindow::on_checkPeriodTimesPi_stateChanged(int checkState)
{
    Q_UNUSED(checkState);

    updatePeriod();
}

void CreateGraphsWindow::on_checkPeriodTimesPi_clicked()
{

}

void CreateGraphsWindow::on_spinAmplitude_valueChanged(double amplitude)
{
    if (amplitude > 0)
    {
        this->ui->renderArea->setAmplitude(amplitude);
        this->ui->renderArea->repaint();
    }
}

void CreateGraphsWindow::on_checkNegative_stateChanged(int checkState)
{
    this->ui->renderArea->setNegative(checkState == Qt::Checked);
    this->ui->renderArea->repaint();
}

