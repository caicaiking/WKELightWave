#ifndef CLSABAMATESTWINDOW_H
#define CLSABAMATESTWINDOW_H

#include "ui_clsAbamaTestWindow.h"

class clsAbamaTestWindow : public QDialog, private Ui::clsAbamaTestWindow
{
    Q_OBJECT

public:
    explicit clsAbamaTestWindow(QWidget *parent = 0);
};

#endif // CLSABAMATESTWINDOW_H
