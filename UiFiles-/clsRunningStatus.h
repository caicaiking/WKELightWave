#ifndef CLSRUNNINGSTATUS_H
#define CLSRUNNINGSTATUS_H

#include "ui_clsRunningStatus.h"

class clsRunningStatus : public QDialog, private Ui::clsRunningStatus
{
    Q_OBJECT

public:
    explicit clsRunningStatus(QWidget *parent = 0);

    void setChannel(const int channel);
    void setItem1(const QString item);
    void setItem2(const QString item);
    void setStatus1(const bool status);
    void setStatus2(const bool status);

    void updateLabels();
    void updateStatusLabels();

private:
    int channel;
    QString item1,item2;
    bool status1,status2;
};

#endif // CLSRUNNINGSTATUS_H
