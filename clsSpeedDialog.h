#ifndef CLSSPEEDDIALOG_H
#define CLSSPEEDDIALOG_H

#include "ui_clsSpeedDialog.h"

class clsSpeedDialog : public QDialog, private Ui::clsSpeedDialog
{
    Q_OBJECT

public:
    explicit clsSpeedDialog(QWidget *parent = 0);
    QString getSpeed();
private slots:
    void on_btnMax_clicked();
    void on_btnFast_clicked();
    void on_btnMed_clicked();
    void on_btnSlow_clicked();

    //void on_btnClose_clicked();

private:
    QString speed;
};

#endif // CLSSPEEDDIALOG_H
