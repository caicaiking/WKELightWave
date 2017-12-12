#ifndef CLSHIGHTVOLTAGE_H
#define CLSHIGHTVOLTAGE_H

#include "ui_clsHightVoltage.h"
#include "clsMeterLimit.h"

class clsHightVoltage : public QDialog, private Ui::clsHightVoltage
{
    Q_OBJECT

public:
    explicit clsHightVoltage(QWidget *parent = 0);

    QString getCondition() const;
    void setCondition(const QString condition);
private slots:
    void on_btnVoltage_clicked();
    void on_btnOK_clicked();
    void on_btnCancel_clicked();
    void on_btnRelay_clicked();
    void onLabelLimitClicked();
    void on_btnItem_clicked();
    void on_btnUnit_clicked();
    void updateButtons();
    void saveSettings();
    QString readSettings();
    void on_btnRampUp_clicked();

    void on_btnDelay_clicked();

    void on_btnRampDown_clicked();

private:
    double voltage;
    QString item, suffix;
    QString relaySwitch;
    clsMeterLimit mLimit;
    double hiLimit,lowLimit;
    double dblRampUp, dblDelay, dblRampDown;
};

#endif // CLSHIGHTVOLTAGE_H
