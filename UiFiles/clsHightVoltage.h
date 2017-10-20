#ifndef CLSHIGHTVOLTAGE_H
#define CLSHIGHTVOLTAGE_H

#include "ui_clsHightVoltage.h"
#include "clsMeterLimit.h"

class clsHightVoltage : public QDialog, private Ui::clsHightVoltage
{
    Q_OBJECT

public:
    explicit clsHightVoltage(QWidget *parent = 0);
    QString getVoltageSwitch() const;
    double getVoltage() const;

    QString getCondition() const;
    void setCondition(const QString condition);
    void updateButtons();
    void updateCommand();
private slots:
    void on_btnSwitch_clicked();

    void on_btnVoltage_clicked();

    void on_btnOK_clicked();

    void on_btnCancel_clicked();

    void on_btnRelay_clicked();

    void onLabelLimitClicked();

private:
    QString volSwitch;
    double voltage;
    QString relaySwitch;
    clsMeterLimit mLimit;
    double hiLimit,lowLimit;
};

#endif // CLSHIGHTVOLTAGE_H
