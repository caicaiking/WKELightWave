#ifndef CLSMAINTESTWINDOW_H
#define CLSMAINTESTWINDOW_H

#include "ui_clsMainTestWindow.h"
#include "clsChannelSettings.h"
#include "clsRunService.h"
#include "clsMeter.h"
#include "singleton.h"
#include <QFlowLayout.h>
#include <QJsonDocument>
#include "clsTestConditon.h"
#include "clsSignalDisplayWidget.h"
#include <QThread>
class clsMainTestWindow : public QMainWindow, private Ui::clsMainTestWindow
{
    Q_OBJECT
public:
    explicit clsMainTestWindow(QWidget *parent = 0);

    void showAllStep();
    QString getTestCondition(void) const;


public slots:
    void setRunningMode(bool value);
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

    void on_btnSettings_clicked();
    void on_btnRunning_clicked();
    void on_btnReptive_clicked();

    void installSignalDispaly();
    void on_btnChannelCalibration_clicked();
    void on_btnAboutMe_clicked();
    void on_btnRunSettings_clicked();


    void on_btnExitRemote_clicked();

    void setRemote(QString str);
    void setRemoteType(QString str);
    void setLanRemote(bool value);
    void on_btnSignal_toggled(bool checked);

protected:
    void closeEvent(QCloseEvent *event);
signals:
    void switchMode(bool);
private:
    QList<clsTestConditons*> steps;
    QList<clsMeter *> items;
    QFlowLayout *layout;
    clsSignalDisplayWidget * signalWidget;
    void initDataBase();
    bool runningMode;
};

#endif // CLSMAINTESTWINDOW_H
