#ifndef CLSSIGNALDISPLAYWIDGET_H
#define CLSSIGNALDISPLAYWIDGET_H

#include "ui_clsSignalDisplayWidget.h"
#include <QPixmap>
#include "clsDataStatistics.h"
class clsSignalDisplayWidget : public QWidget, private Ui::clsSignalDisplayWidget
{
    Q_OBJECT

public:
    explicit clsSignalDisplayWidget(QWidget *parent = 0);

public slots:
    void setBusy(bool value); //设置Busy的状态
    void setLCR(bool value); //设置LCR的P/F状态
    void setHV(bool value); //设置HV的P/F状态
    void setTrig(); //显示Trig的状态
    void reset();//显示Reset的状态


    void lcrOutput(bool value); //显示LCR的输出状态
    void hvOutput(bool value); //显示HV的输出状态

    void setCurrentStep(int value);
protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
private:
    void setLabelPixmap(QLabel *lbl, bool status);
    void setLcdNumberStyle();
private:
    QString passPix, failPix;
    clsDataStatistics *totle, *lcrData, *hvData;
};

#endif // CLSSIGNALDISPLAYWIDGET_H
