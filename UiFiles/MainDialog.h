#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "ui_MainDialog.h"
#include <QGridLayout>
#include "clsChannelSettings.h"
#include "clsRunningStatus.h"
#include "clsRunService.h"
#include "clsMeter.h"
#include "singleton.h"

class MainDialog : public QDialog, private Ui::MainDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);

    void updateChannelSettings(QVariantMap map);
    QString getCondition() const;

private slots:
    void on_btnNewSetup_clicked();
    void on_btnSettings_clicked();

    void on_btnRunning_clicked();
    void on_btnSaveSetup_clicked();

    void on_btnOpenSetup_clicked();

private slots:
    void deleteChannel(int index);
    void showChannelRes(QString res);

signals:
    void startTrig();
    void switchMode(bool);

private:
    QGridLayout *layout;
    int channel;
    QMap<int,clsMeter*> channelMap;
    QMap<int,clsRunningStatus*> runningMap;
    QVariantMap conditionMap;
    int num;

    clsMeter *meterType;
    QString meter;
};

#endif // MAINDIALOG_H
