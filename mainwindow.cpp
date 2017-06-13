#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "creategraphswindow.h"
#include "pinumber.h"
#include <cmath>
#include "pinumbertest.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    PiNumberTest    runTest(1);

    ui->setupUi(this);

    // This is a class pointer to put the window on the heap and
    // be able to use it and the parent without deleting it. i.e. non-modal.
    createGraphsWindow = new CreateGraphsWindow(this); // setting this as parent

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCreateGraphs_clicked()
{
//    This is an example of Modal - which does
//      not allow both windows to be accessed
//      and this window dies on closure.
//    CreateGraphsWindow  createGraphsWindow;
//    createGraphsWindow.setModal(true);
//    createGraphsWindow.exec();

    createGraphsWindow->show();
    createGraphsWindow->activateWindow();
}
