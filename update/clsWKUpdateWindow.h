#ifndef CLSWKUPDATEWINDOW_H
#define CLSWKUPDATEWINDOW_H

#include "ui_clsWKUpdateWindow.h"

class clsWKUpdateWindow : public QDialog, private Ui::clsWKUpdateWindow
{
    Q_OBJECT

public:
    explicit clsWKUpdateWindow(QWidget *parent = 0);
};

#endif // CLSWKUPDATEWINDOW_H
