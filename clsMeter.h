#ifndef CLSMETER_H
#define CLSMETER_H

#include <QDialog>

class clsMeter : public QDialog
{
public:
    clsMeter(QDialog *parent=0);

    virtual void setCondition(const QString condition)=0;
    virtual void setChannel(const int channel)=0;
    virtual void setChannelSettings()=0;
    virtual void setChannelRunnings()=0;
    virtual void setCloseEnabled(const bool bl)=0;
    virtual void updateLabels()=0;
};

#endif // CLSMETER_H
