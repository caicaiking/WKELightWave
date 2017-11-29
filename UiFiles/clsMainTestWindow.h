#ifndef CLSMAINTESTWINDOW_H
#define CLSMAINTESTWINDOW_H

#include "ui_clsMainTestWindow.h"
#include "clsChannelSettings.h"
#include "clsRunService.h"
#include "clsMeter.h"
#include "singleton.h"
#include <QFlowLayout.h>
#include <QJsonDocument>
#include "clsRunningThread.h"
#include "clsTestConditon.h"
class clsMainTestWindow : public QMainWindow, private Ui::clsMainTestWindow
{
    Q_OBJECT

public:
    explicit clsMainTestWindow(QWidget *parent = 0);

    void updateChannelSettings(const QList<clsTestConditons *> map);

    QString getTestCondition(void) const;


private slots:
    void on_btnNewSetup_clicked();
    void on_btnSettings_clicked();
    void on_btnRunning_clicked();
    void on_btnSaveSetup_clicked();
    void on_btnOpenSetup_clicked();

private slots:
    void deleteChannel(int index);
    void showChannelRes(QString res);
    void on_btnTrig_clicked();

signals:
    void switchMode(bool);
private:
    QList<clsTestConditons*> steps;
    QList<clsMeter *> items;
    QFlowLayout *layout;
    clsRunningThread *trigThread, *resetThread;
};

#endif // CLSMAINTESTWINDOW_H
