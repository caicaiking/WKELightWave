#ifndef CLSWK6500METER_H
#define CLSWK6500METER_H

#include "ui_clsWK6500Meter.h"
#include "clsMeterLimit.h"

class clsWK6500Meter : public QDialog, private Ui::clsWK6500Meter
{
    Q_OBJECT

public:
    explicit clsWK6500Meter(QWidget *parent = 0);

    QString trig() const;
    QString getCondtion() const;
    void setCondition(const QString condition);

private slots:
    void onLabellimit1Clicked();
    void onLabellimit2Clicked();

private slots:
    void on_btnFreq_clicked();
    void on_btnOK_clicked();
    void on_btnLevel_clicked();
    void on_btnEqucct_clicked();
    void on_btnRange_clicked();
    void on_btnSpeed_clicked();
    void on_btnBiasType_clicked();
    void on_btnBiasSwitch_clicked();
    void on_btnCancel_clicked();
    void on_btnRelay_clicked();
    void on_btnBias_clicked();
private slots:
    QString readSettings();
    void saveSettings();
    void on_btnItem2Unit_clicked();
    void on_btnItem1Unit_clicked();
    void on_btnItem1_clicked();
    void on_btnItem2_clicked();
    void on_grpItem2_clicked(bool checked);
private:
    double limitCheck( double value, const double max, const double min);
    void updateButtons();
private:
    QString item1,item2;
    int item1Index,item2Index;
    bool isItem2Enable;
    double frequency;
    double level, levelA, levelV;
    QString levelUnit;
    QString equcct;
    QString speed;
    QString range;
    double bias, biasA, biasV;
    QString biasType;
    QString biasSwitch;
    clsMeterLimit mlItem1,mlItem2;
    double item1HiLimit,item1LowLimit,item2HiLimit,item2LowLimit;
    QString suffix1,suffix2;

    QString relaySwitch;

};

#endif // CLSWK6500METER_H

