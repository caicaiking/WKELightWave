#ifndef CLSSELECTUPDATESTEP_H
#define CLSSELECTUPDATESTEP_H

#include "ui_clsSelectUpdateStep.h"

class clsSelectUpdateStep : public QDialog, private Ui::clsSelectUpdateStep
{
    Q_OBJECT

public:
    explicit clsSelectUpdateStep(QWidget *parent = 0);
    static int selectStep(QWidget *parent, QList<int> steps);
private slots:
    void on_btnOk_clicked();
};

#endif // CLSSELECTUPDATESTEP_H
