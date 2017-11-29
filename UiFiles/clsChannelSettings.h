#ifndef CLSCHANNELSETTINGS_H
#define CLSCHANNELSETTINGS_H

#include "ui_clsChannelSettings.h"
#include "clsMeter.h"

class clsChannelSettings : public clsMeter, private Ui::clsChannelSettings
{
    Q_OBJECT

public:
    explicit clsChannelSettings(clsMeter *parent = 0);
    void setChannel(const int channel);
    void setCondition(const QString condition);

    void updateLabels();
    void setChannelSettings();
    void setChannelRunnings();
    void setCloseEnabled(bool bl);
    void updateRes(const QString res);

    void setStep(int i) override;
    int getStep() const override;

private slots:
  void onLabelCloseClicked();



private:
    QString condition;
    int channel;
    QString item1,item2;
    bool isItem2Enable;
    double frequency,level,bias;
    QString levelUnit;
    QString speed;
    QString range;
    QString equcct;
    QString biasSwitch,biasType;
    double item1HiLimit,item1LowLimit,item2HiLimit,item2LowLimit;
    QString suffix1,suffix2;
    QString relaySwitch;

private:
    int intStep;
};

#endif // CLSCHANNELSETTINGS_H
