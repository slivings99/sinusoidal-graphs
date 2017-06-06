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

private:
    Ui::CreateGraphsWindow *ui;
    float mAmplitude;
    float mPeriod;
    float mMidline;
};

#endif // CREATEGRAPHSWINDOW_H
