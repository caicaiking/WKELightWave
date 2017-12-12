#ifndef CLSHVCNNTWINDOW_H
#define CLSHVCNNTWINDOW_H

#include "ui_clsHVCnntWindow.h"

class clsHVCnntWindow : public QDialog, private Ui::clsHVCnntWindow
{
    Q_OBJECT

public:
    explicit clsHVCnntWindow(QWidget *parent = 0);

    static bool setupConnection();
private slots:
    void on_btnTest_clicked();
};

#endif // CLSHVCNNTWINDOW_H
