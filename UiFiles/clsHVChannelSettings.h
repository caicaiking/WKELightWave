#ifndef CLSHVCHANNELSETTINGS_H
#define CLSHVCHANNELSETTINGS_H

#include "ui_clsHVChannelSettings.h"
#include "clsMeter.h"

class clsHVChannelSettings : public clsMeter, private Ui::clsHVChannelSettings
{
    Q_OBJECT

public:
    explicit clsHVChannelSettings(clsMeter *parent = 0);
    void setCondition(const QString condition);
    void setChannel(const int channel);
    void updateLabels();
    void setChannelSettings();
    void setChannelRunnings();
    void setCloseEnabled(const bool bl);
    void updateRes(const QString res);

public slots:
    void onCloseLabelClicked();

signals:
    void deleteChannelSettings(int i);

private:
    int channel;
    QString condition;
    QString item;
    QString resStatus;
    double res;
    QString relaySwitch;
};

#endif // CLSHVCHANNELSETTINGS_H
