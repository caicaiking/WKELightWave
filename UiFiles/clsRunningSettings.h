#ifndef CLSRUNNINGSETTINGS_H
#define CLSRUNNINGSETTINGS_H

#include "ui_clsRunningSettings.h"

class clsRunningSettings : public QDialog, private Ui::clsRunningSettings
{
    Q_OBJECT

public:
    explicit clsRunningSettings(QWidget *parent = 0);
private slots:
    void on_btnOk_clicked();
    void on_btnCancel_clicked();
    void on_btnConnect_clicked();
};

#endif // CLSRUNNINGSETTINGS_H
