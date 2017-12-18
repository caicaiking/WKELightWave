#ifndef CLSSAMPLETEST_H
#define CLSSAMPLETEST_H

#include "ui_clsSampleTest.h"
#include "clsInstrumentCalibration.h"
class clsSampleTest : public QDialog, private Ui::clsSampleTest
{
    Q_OBJECT

public:
    explicit clsSampleTest(clsInstrumentCalibration *value,QWidget *parent = 0);

private slots:
    void on_btnClose_clicked();

    void on_btnTrig_clicked();

    void on_btnOk_clicked();

private:
    clsInstrumentCalibration *meter;
};

#endif // CLSSAMPLETEST_H
