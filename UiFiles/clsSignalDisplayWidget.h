#ifndef CLSSIGNALDISPLAYWIDGET_H
#define CLSSIGNALDISPLAYWIDGET_H

#include "ui_clsSignalDisplayWidget.h"

class clsSignalDisplayWidget : public QWidget, private Ui::clsSignalDisplayWidget
{
    Q_OBJECT

public:
    explicit clsSignalDisplayWidget(QWidget *parent = 0);
};

#endif // CLSSIGNALDISPLAYWIDGET_H
