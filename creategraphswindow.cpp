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
