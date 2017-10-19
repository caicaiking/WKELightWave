#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "ui_MainDialog.h"
#include <QGridLayout>
#include "clsChannelSettings.h"
#include "clsRunningStatus.h"
#include "clsRunService.h"

class MainDialog : public QDialog, private Ui::MainDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);

    void updateChannelSettings(QVariantMap map);

private slots:
    void on_btnNewSetup_clicked();
    void on_btnSettings_clicked();

    void on_btnRunning_clicked();
    void on_btnSaveSetup_clicked();

    void on_btnOpenSetup_clicked();

private slots:
    void deleteChannel(int index);
    void showChannelRes(QString res);


private:
    QGridLayout *layout;
    int channel;
    QMap<int,clsChannelSettings*> channelMap;
    QMap<int,clsRunningStatus*> runningMap;
    QVariantMap conditionMap;
    int num;

    clsRunService runService;
};

#endif // MAINDIALOG_H
