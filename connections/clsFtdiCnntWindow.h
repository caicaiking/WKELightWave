#ifndef CLSFTDICNNTWINDOW_H
#define CLSFTDICNNTWINDOW_H

#include "ui_clsFtdiCnntWindow.h"

class clsFtdiCnntWindow : public QDialog, private Ui::clsFtdiCnntWindow
{
    Q_OBJECT

public:
    explicit clsFtdiCnntWindow(QWidget *parent = 0);

    static bool setupConnection();
private slots:
    void on_btnTest_clicked();
private:
    void readSettings();
    void writeSettings();

};

#endif // CLSFTDICNNTWINDOW_H