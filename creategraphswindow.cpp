#include "creategraphswindow.h"
#include "ui_creategraphswindow.h"
#include "pinumber.h"
#include <cstdio>

CreateGraphsWindow::CreateGraphsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateGraphsWindow)
{
    int numerator, denominator;
    char buffer[50];

    PiNumber::ClosestFraction(0.33333333, 1000, numerator, denominator);
    ui->setupUi(this);
    sprintf(buffer,"%d / %d",numerator, denominator);
    ui->inputAmplitude->setText(buffer);
}

CreateGraphsWindow::~CreateGraphsWindow()
{
    delete ui;
}

void CreateGraphsWindow::on_btnCloseWindow_clicked()
{
    hide();
}
