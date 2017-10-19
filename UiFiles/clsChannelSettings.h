#ifndef CLSCHANNELSETTINGS_H
#define CLSCHANNELSETTINGS_H

#include "ui_clsChannelSettings.h"

class clsChannelSettings : public QDialog, private Ui::clsChannelSettings
{
    Q_OBJECT

public:
    explicit clsChannelSettings(QWidget *parent = 0);
    void setChannel(const int channel);
    void setCondition(const QString condition);

    void updateLabels();
    void setChannelSettings();
    void setChannelRunnings();
    void setCloseEnabled(bool bl);

private slots:
  void onLabelCloseClicked();


signals:
  void deleteChannelSettings(int index);


private:
    QString condition;
    int channel;
    QString item1,item2;
    double frequency,level,bias;
    QString levelUnit;
    QString speed;
    QString range;
    QString equcct;
    QString biasSwitch,biasType;
    double item1HiLimit,item1LowLimit,item2HiLimit,item2LowLimit;
};

#endif // CLSCHANNELSETTINGS_H
