#ifndef CLSHIGHTVOLTAGE_H
#define CLSHIGHTVOLTAGE_H

#include "ui_clsHightVoltage.h"

class clsHightVoltage : public QDialog, private Ui::clsHightVoltage
{
    Q_OBJECT

public:
    explicit clsHightVoltage(QWidget *parent = 0);
    QString getVoltageSwitch() const;
    double getVoltage() const;
    void updateCommand();
private slots:
    void on_btnSwitch_clicked();

    void on_btnVoltage_clicked();

    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    QString volSwitch;
    double voltage;
};

#endif // CLSHIGHTVOLTAGE_H
