#ifndef CLSNEWSETUP_H
#define CLSNEWSETUP_H

#include "ui_clsNewSetup.h"

class clsNewSetup : public QDialog, private Ui::clsNewSetup
{
    Q_OBJECT

public:
    explicit clsNewSetup(QWidget *parent = 0);
    int getChannelStart() const;
    int getChannelStop() const;
    QPoint getChannel() const;
    void setChannel(int channelStart, int channelStop);
    void setMeter(QString meter);
    QString getCondtion() const;

    QString getMeter() const;
private slots:
    void on_btnLCR_clicked();
    void on_btnHV_clicked();
    void on_btnCancel_clicked();

    void on_cmbTerminal1_currentIndexChanged(int index);

    void on_cmbTerminal2_currentIndexChanged(int index);

private:
    int channelStart, channelStop;
    QString condition;
    QString meter;
};

#endif // CLSNEWSETUP_H
