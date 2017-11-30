#include "clsMainTestWindow.h"
#include "clsNewSetup.h"
#include "clsChannelSettings.h"
#include <QGridLayout>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonParseError>
#include "publicUtility.h"
#include "clsMeterFactory.h"
#include "clsRunService.h"
#include <QDebug>
#include <QMessageBox>
#include "clsWarningBox.h"
#include "clsSelectUpdateStep.h"
#include "clsRunService.h"
#include "clsUpdateFtdiDataThread.h"
#include "clsSettings.h"
#include <QFile>
#include <QDir>
//TODO: 增加信号显示面板
//TODO: 增加多通道校准界面
//TODO: 信号模拟
clsMainTestWindow::clsMainTestWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint
                         | Qt::WindowMaximizeButtonHint);
    // this->showMaximized();

    layout = new QFlowLayout(6,6,6);

    this->itemWidget->setLayout(layout);

    trigThread = new clsRunningThread();
    trigThread->setCaptureBit(0);

    resetThread = new clsRunningThread();
    resetThread->setCaptureBit(1);


    trigThread->start();
    resetThread->start();

    sngFtdiData::Ins()->start();

    connect(sngRunService::Ins(),SIGNAL(showRes(QString)),this,SLOT(showChannelRes(QString)));

    QString lastFile = getLastFile();
    if(!lastFile.isEmpty())
    {
        this->deleteAllSteps();
        openTaskFile(lastFile);

        btnRunning->clicked(true);
        on_btnSettings_clicked(false);
    }
    else
        on_btnSettings_clicked(true);
}

void clsMainTestWindow::updateChannelSettings(const QList<clsTestConditons *> map)
{
    QJsonDocument jsDocument;
    QJsonParseError error;

    //删除所有的步骤
    for(int i=items.length()-1; i>=0;i--)
    {
        clsMeter * tmp =0;
        tmp =items.at(i);

        layout->removeWidget(tmp);
        items.removeAt(i);

        if(tmp !=0)
        {
            layout->removeWidget(tmp);
            delete tmp;
        }
    }

    items.clear();
    //重新开始生成步骤
    for(int i=0; i<map.length(); i++)
    {
        clsMeter *tmp;
        clsTestConditons* js = map[i];

        tmp = clsMeterFactory::getMeter(js->meter);

        jsDocument = QJsonDocument::fromJson(js->condition.toUtf8(),&error);

        if(error.error != QJsonParseError::NoError)
            continue;

        if(jsDocument.isEmpty() || jsDocument.isNull())
            continue;
        QVariantMap cMap = jsDocument.toVariant().toMap();

        QString condition = cMap["conditions"].toString();
        int channel = cMap["channel"].toInt();
        tmp->setCondition(condition);
        tmp->setChannel(channel);
        tmp->setCloseEnabled(true);
        tmp->updateLabels();
        tmp->setStep(i) ; //以0为开始
        connect(tmp,SIGNAL(deleteChannelSettings(int)),this,SLOT(deleteChannel(int)));
        items.append(tmp);
        layout->addWidget(tmp);

    }

    layout->update();
}

//获取这个测试条件转换成 Json 语句
QString clsMainTestWindow::getTestCondition() const
{
    QString strSetup;
    QVariantList list;

    for(int i=0; i<steps.length(); i++)
    {
        //QString tmp = steps[i].toJson();
        list.append(steps[i]->toJson());
    }

    QJsonDocument jsonDocument=QJsonDocument::fromVariant(list);
    if(!(jsonDocument.isNull()))
    {
        strSetup=jsonDocument.toJson(QJsonDocument::Indented);
    }

    return strSetup;
}

void clsMainTestWindow::on_btnNewSetup_clicked()
{
    clsNewSetup *dlg=new clsNewSetup(this);


    clsTestConditons* tmp = new clsTestConditons();
    if(dlg->exec()==QDialog::Accepted)
    {
        tmp->channel = dlg->getChannel();
        tmp->meter = dlg->getMeter();
        tmp->condition = dlg->getCondtion();

        auto getKeys = [](QList<clsTestConditons *> items)
        {
            QList<int> tmp;
            for(int i = 0; i< items.length(); i++)
                tmp.append(items.at(i)->channel);
            return tmp;
        };

        QList<int> keys =getKeys(steps);

        if(keys.contains(dlg->getChannel()))
        {
            int index = keys.indexOf(dlg->getChannel());
            int value = clsWarningBox::warning(0,tr("警告"),
                                               QString(tr("通道 %1 已经存在设置,请选择操作.")).arg(dlg->getChannel()));

            if(value == QMessageBox::No)
                return ;
            else if(value == QMessageBox::Ok) //更新步骤
            {
                QList<int> tmpList;

                for(int i=0; i<keys.length(); i++)
                {
                    if(keys.at(i)==dlg->getChannel())
                        tmpList.append(i);
                }

                int tmpIndex = clsSelectUpdateStep::selectStep(0,tmpList);

                steps[tmpIndex] = tmp;
            }
            else //插入新步骤
                steps.append(tmp);
        }
        else
            steps.append(tmp);

        updateChannelSettings(steps);
    }
}

void clsMainTestWindow::deleteChannel(int index)
{
    steps.removeAt(index);

    updateChannelSettings(steps);
}

void clsMainTestWindow::showChannelRes(QString res)
{
    /* Res Json 语句示例
    {
        "channel": 1,
        "data": [
            {
                "item": "R",
                "result": 584880.54,
                "status": false,
                "suffix": "k"
            },
            {
                "item": "L",
                "result": 523.44221,
                "status": true,
                "suffix": "u"
            }
        ],
        "meter": "WK6500",
        "step": 0
    }
    */
    QString strRes = res;

    QJsonDocument jsDocument;
    QJsonParseError error;

    jsDocument = QJsonDocument::fromJson(strRes.toUtf8(), &error);

    if(error.error != QJsonParseError::NoError)
        return;

    if(jsDocument.isEmpty() || jsDocument.isNull())
        return;

    QVariantMap tmpMap = jsDocument.toVariant().toMap();

    int currentStep = tmpMap["step"].toInt();

    if(currentStep > items.length())
        return;

    items.at(currentStep)->updateRes(strRes);
}

void clsMainTestWindow::deleteAllSteps()
{
    steps.clear();
    updateChannelSettings(steps);

}
//!
//! \param file 文件的全路径包含文件名称
//!
void clsMainTestWindow::saveLastFile(QString file)
{
    if(file.isEmpty())
        return;

    QFileInfo fileInfo(file);
    if(!fileInfo.exists())
        return;

    clsSettings settings;
    QString strNode = "File/";

    settings.writeSetting(strNode + "lastDir", fileInfo.absoluteDir().canonicalPath());
    settings.writeSetting(strNode + "lastFile", fileInfo.absoluteFilePath());
}

QString clsMainTestWindow::getLastFilePath()
{
    clsSettings settings;
    QString strNode = "File/";
    QString filePath;
    settings.readSetting(strNode + "lastDir", filePath);
    QDir d;
    if(d.exists(filePath))
        return filePath;
    else
        return ".";
}

QString clsMainTestWindow::getLastFile()
{
    clsSettings settings;
    QString strNode = "File/";
    QString fileName;
    settings.readSetting(strNode + "lastFile", fileName);

    if(QFile::exists(fileName))
        return fileName;
    else
        return "";
}

void clsMainTestWindow::openTaskFile(QString strPath)
{
    QString strSetup;
    QFile file(strPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream inStream(&file);
    strSetup=inStream.readAll();
    file.close();

    QVariantList tmpConditionList;

    QJsonParseError error;
    QJsonDocument jsonDocument=QJsonDocument::fromJson(strSetup.toUtf8(),&error);
    if(error.error==QJsonParseError::NoError)
    {
        if(!(jsonDocument.isNull() || jsonDocument.isEmpty()))
        {
            tmpConditionList=jsonDocument.toVariant().toList();

            steps.clear();

            for(int i=0; i<tmpConditionList.length(); i++)
            {
                clsTestConditons *tmp = new clsTestConditons();
                tmp->setJson(tmpConditionList.at(i).toString());
                steps.append(tmp);
            }
        }
    }
    saveLastFile(strPath);
    myStatusBar->showMessage(tr("成功打开步骤文件：%1").arg(strPath),3000);
    updateChannelSettings(steps);
}

void clsMainTestWindow::saveTaskFile(QString strPath)
{
    QString strSetup;
    QFile file(strPath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    strSetup = getTestCondition();
    QTextStream outStream(&file);
    outStream<<strSetup;
    outStream.flush();
    file.close();
    saveLastFile(strPath);
    myStatusBar->showMessage(tr("文件已保存至：%1").arg(strPath),3000);
}

void clsMainTestWindow::on_btnSaveSetup_clicked()
{
    QString strPath=QFileDialog::getSaveFileName(this,tr("保存测试任务"), getLastFilePath(),
                                                 tr("WKE FactoryView 任务 (*.wket)"),0);

    if(strPath.isEmpty())
        return;
    saveTaskFile(strPath);
}

void clsMainTestWindow::on_btnOpenSetup_clicked()
{
    QString strPath=QFileDialog::getOpenFileName(this,tr("保存测试任务"), getLastFilePath(),
                                                 tr("WKE FactoryView 任务 (*.wket)"),0);
    if(strPath.isEmpty())
        return;
    this->deleteAllSteps();
    openTaskFile(strPath);
}

void clsMainTestWindow::on_btnTrig_clicked()
{
    sngRunService::Ins()->trig();
}

void clsMainTestWindow::on_btnSettings_clicked(bool checked)
{
    btnSettings->setChecked(checked);
    btnRunning->setChecked(!checked);
    if(checked) //Setting Mode
    {
        for(int i=0; i< items.length(); i++)
        {
            items[i]->setChannelSettings();
            items[i]->setCloseEnabled(true);
        }

        sngRunService::Ins()->switchToRunningMode(false);
        disconnect(trigThread,SIGNAL(getSignal()),sngRunService::Ins(),SLOT(trig()));
        disconnect(resetThread,SIGNAL(getSignal()),sngRunService::Ins(),SLOT(reset()));
    }
    else //Running Mode
    {
        for(int i=0; i< items.length(); i++)
        {
            items[i]->setChannelRunnings();
            items[i]->setCloseEnabled(false);
        }

        sngRunService::Ins()->setTestConditon(getTestCondition());
        sngRunService::Ins()->switchToRunningMode(true);

        connect(trigThread,SIGNAL(getSignal()),sngRunService::Ins(),SLOT(trig()));
        connect(resetThread,SIGNAL(getSignal()),sngRunService::Ins(),SLOT(reset()));
    }
}

void clsMainTestWindow::on_btnRunning_clicked(bool checked)
{
    btnSettings->clicked(!checked);
}
