#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "creategraphswindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnCreateGraphs_clicked();

private:
    Ui::MainWindow *ui;
    CreateGraphsWindow  *createGraphsWindow;
};

#endif // MAINWINDOW_H
