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

void CreateGraphsWindow::on_spinPhaseShift_valueChanged(double value)
{
    PiNumber    phaseShift;

    if (this->ui->checkPhaseShiftTimesPi->isChecked())
    {
        phaseShift.setValue(value * M_PI);
    }
    else
    {
        phaseShift.setValue(value);
    }
    this->ui->renderArea->setPhaseShift(phaseShift);
    this->ui->renderArea->repaint();
}

void CreateGraphsWindow::on_checkPhaseShiftTimesPi_stateChanged(int checkState)
{
    PiNumber    phaseShift;
    float       value;

    value = this->ui->spinPhaseShift->value();
    if (checkState == Qt::Checked)
    {
        phaseShift.setValue(value * M_PI);
    }
    else
    {
        phaseShift.setValue(value);
    }
    this->ui->renderArea->setPhaseShift(phaseShift);
    this->ui->renderArea->repaint();
}

void CreateGraphsWindow::on_checkPhaseShiftTimesPi_clicked()
{

}

void CreateGraphsWindow::on_spinPeriod_valueChanged(double value)
{
    PiNumber    period;

    if (this->ui->checkPeriodTimesPi->isChecked())
    {
        period.setValue(value * M_PI);
    }
    else
    {
        period.setValue(value);
    }
    this->ui->renderArea->setPeriod(period);
    this->ui->renderArea->repaint();
}

void CreateGraphsWindow::on_checkPeriodTimesPi_stateChanged(int checkState)
{
    PiNumber    period;
    float       value;

    value = this->ui->spinPeriod->value();
    if (checkState == Qt::Checked)
    {
        period.setValue(value * M_PI);
    }
    else
    {
        period.setValue(value);
    }
    this->ui->renderArea->setPeriod(period);
    this->ui->renderArea->repaint();
}

void CreateGraphsWindow::on_checkPeriodTimesPi_clicked()
{

}

void CreateGraphsWindow::on_spinAmplitude_valueChanged(double amplitude)
{
    this->ui->renderArea->setAmplitude(amplitude);
    this->ui->renderArea->repaint();
}

void CreateGraphsWindow::on_checkNegative_stateChanged(int checkState)
{
    this->ui->renderArea->setNegative(checkState == Qt::Checked);
    this->ui->renderArea->repaint();
}

