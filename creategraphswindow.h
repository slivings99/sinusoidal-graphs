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

private:
    Ui::CreateGraphsWindow *ui;
};

#endif // CREATEGRAPHSWINDOW_H
