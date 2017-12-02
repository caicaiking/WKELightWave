#ifndef CLSNEWSETUP_H
#define CLSNEWSETUP_H

#include "ui_clsNewSetup.h"

class clsNewSetup : public QDialog, private Ui::clsNewSetup
{
    Q_OBJECT

public:
    explicit clsNewSetup(QWidget *parent = 0);
    int getChannel() const;
    void setChannel(int channel);
    void setMeter(QString meter);
    QString getCondtion() const;

    QString getMeter() const;
private slots:
    void on_cmbChannel_currentIndexChanged(int index);
    void on_btnLCR_clicked();
    void on_btnHV_clicked();
    void on_btnCancel_clicked();

private:
    int channel;
    QString condition;
    QString meter;
};

#endif // CLSNEWSETUP_H
