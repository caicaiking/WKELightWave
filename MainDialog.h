#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "ui_MainDialog.h"
#include <QGridLayout>
#include "clsChannelSettings.h"
#include "clsRunningStatus.h"

class MainDialog : public QDialog, private Ui::MainDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
private slots:
    void on_btnNewSetup_clicked();
    void on_btnSettings_clicked();

    void on_btnRunning_clicked();

private slots:
    void deleteChannel(int index);

private:
    QGridLayout *layout;
    int channel;
    QMap<int,clsChannelSettings*> channelMap;
    QMap<int,clsRunningStatus*> runningMap;
    int num;
};

#endif // MAINDIALOG_H
