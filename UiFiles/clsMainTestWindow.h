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
#include "clsSignalDisplayWidget.h"
#include <QThread>
#include "clsRunningThread.h"
class clsMainTestWindow : public QMainWindow, private Ui::clsMainTestWindow
{
    Q_OBJECT
public:
    explicit clsMainTestWindow(QWidget *parent = 0);

    void showAllStep();
    QString getTestCondition(void) const;


private slots:
    void on_btnNewSetup_clicked();
    void on_btnSaveSetup_clicked();
    void on_btnOpenSetup_clicked();
    void on_btnTrig_clicked();
    void deleteChannel(int index);
    void showChannelRes(QString res);
    void deleteAllSteps();   //删除所有步骤
    void editStep(int step);

    void saveLastFile(QString file); //保存最后打开的文件的名称 和 路径
    QString getLastFilePath();          //获取最后打开的文件的路径
    QString getLastFile();          //获取最后打开的文件的名称
    void openTaskFile(QString strPath);
    void saveTaskFile(QString strPath);

    void on_btnSettings_clicked(bool checked);
    void on_btnRunning_clicked(bool checked);
    void on_btnReptive_clicked();

    void installSignalDispaly();


    void trig();
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void switchMode(bool);
private:
    QList<clsTestConditons*> steps;
    QList<clsMeter *> items;
    QFlowLayout *layout;
    clsSignalDisplayWidget * signalWidget;
    clsRunningThread *trigThread;
};

#endif // CLSMAINTESTWINDOW_H
