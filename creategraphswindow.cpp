#include "creategraphswindow.h"
#include "ui_creategraphswindow.h"

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
