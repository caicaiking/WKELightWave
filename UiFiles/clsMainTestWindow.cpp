#include "clsMainTestWindow.h"
#include "clsCalibrationDbOp.h"
#include "clsWK6500CalibrationMeter.h"
#include "clsInstrumentCalibration.h"
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
#include "clsSettings.h"
#include "clsWK6500Meter.h"
#include "clsHightVoltage.h"
#include <QFile>
#include <QDir>
#include "clsRunningThread.h"
#include "clsCalibration.h"
#include <QDesktopServices>
#include <QProcess>
#include "clsRunningSettings.h"
#include "clsRunSettings.h"

//TODO: 主界面增加运行时候的设定
//TODO: 增加服务器设置，端口号2018
//TODO: 增加软件自动更新功能

clsMainTestWindow::clsMainTestWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint
                         | Qt::WindowMaximizeButtonHint);
    // this->showMaximized();

    layout = new QFlowLayout(6,6,6);
    this->itemWidget->setLayout(layout);

    this->initDataBase();
    installSignalDispaly();
    wgtSignalPannel->setVisible(true);
    connect(sngRunService::Ins(),SIGNAL(showRes(QString)),this,SLOT(showChannelRes(QString)));

    //软件初始化后打开最后一次保存的文件
    QString lastFile = getLastFile();
    if(!lastFile.isEmpty())
    {
        this->deleteAllSteps();
        openTaskFile(lastFile);

    }

    runningMode = true;
    setRunningMode(false);

    sngRunSettings::Ins()->readSettings();
    btnReptive->setEnabled(sngRunSettings::Ins()->getRemoteControlType() == clsRunSettings::ManualTrig);
}


/*!
     * \brief  初始化数据库文件。
     */
void clsMainTestWindow::initDataBase()
{
    clsCalDb::getInst()->setStrDataBaseName(QString("./McbCal.db"));
    clsCalDb::getInst()->openDataBase();
    clsCalDb::getInst()->initTable();
}


void clsMainTestWindow::showAllStep()
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
    for(int i=0; i<steps.length(); i++)
    {
        clsMeter *tmp;
        clsTestConditons* js = steps[i];

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
        connect(tmp,SIGNAL(editStep(int)),this,SLOT(editStep(int)));
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

        showAllStep();
    }
}

void clsMainTestWindow::deleteChannel(int index)
{
    steps.removeAt(index);

    showAllStep();
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
    showAllStep();

}

void clsMainTestWindow::editStep(int step)
{
    clsTestConditons * tmpStep = steps[step];
    clsTestConditons ts;
    ts.setJson(tmpStep->condition);

    if(tmpStep->meter == "WK6500")
    {
        clsWK6500Meter * dlg = new clsWK6500Meter(this);
        dlg->setCondition(ts.condition);
        if(dlg->exec() == QDialog::Accepted)
        {
            ts.condition = dlg->getCondition();
            tmpStep->condition = ts.toJson();
            showAllStep();
        }
    }
    else
    {
        clsHightVoltage * dlg = new clsHightVoltage(this);
        dlg->setCondition(ts.condition);
        if(dlg->exec() == QDialog::Accepted)
        {
            ts.condition = dlg->getCondition();
            tmpStep->condition = ts.toJson();
            showAllStep();
        }

    }
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
    showAllStep();
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
    btnTrig->setEnabled(false);

    sngRunService::Ins()->trig();

    btnTrig->setEnabled(true);
}

void clsMainTestWindow::setRunningMode(bool value)
{
    if(runningMode == value)
        return ;

    runningMode = value;

    bool checked = !value;
    if(checked) //Setting Mode
    {
        for(int i=0; i< items.length(); i++)
        {
            items[i]->setChannelSettings();
            items[i]->setCloseEnabled(true);
        }

        sngRunService::Ins()->switchToRunningMode(false);
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
    }

    btnNewSetup->setVisible(checked);
    btnOpenSetup->setVisible(checked);
    btnSaveSetup->setVisible(checked);
    btnTrig->setVisible(!checked);
    btnReptive->setVisible(!checked);
    btnRunning->setVisible(checked);
    btnSettings->setVisible(!checked);
    btnChannelCalibration->setVisible(!checked);
    btnRunSettings->setVisible(!checked);
    btnReptive->setChecked(false);

}

void clsMainTestWindow::on_btnSettings_clicked()
{
    this->setRunningMode(false);
}

void clsMainTestWindow::on_btnRunning_clicked()
{
    this->setRunningMode(true);
}

void clsMainTestWindow::on_btnReptive_clicked()
{
    while(btnReptive->isChecked())
    {
        this->btnTrig->clicked();
        publicUtility::sleepMs(2);
    }
}

void clsMainTestWindow::installSignalDispaly()
{
    signalWidget = new clsSignalDisplayWidget();

    QVBoxLayout * hLayout = new QVBoxLayout();
    hLayout->addWidget(signalWidget);
    hLayout->setContentsMargins(0,0,0,0);
    wgtSignalPannel->setLayout(hLayout);
}

void clsMainTestWindow::closeEvent(QCloseEvent *event)
{
    btnReptive->setChecked(false);
    sngTrigThread::Ins()->stop();
    qApp->processEvents();
    publicUtility::sleepMs(10);
    event->accept();
}



void clsMainTestWindow::on_btnChannelCalibration_clicked()
{
    clsCalibration * dlg = new clsCalibration(this);
    dlg->setWindowTitle(tr("通道校准"));

    clsInstrumentCalibration * meter = new clsWK6500CalibrationMeter();
    dlg->setMeter(meter);

    dlg->setSteps(steps);

    dlg->exec();

    sngRunService::Ins()->setTestConditon(getTestCondition());

    //QList<clsTestConditons*> steps;
}


void clsMainTestWindow::on_btnAboutMe_clicked()
{
    QString DEFT_URL= "https://raw.githubusercontent.com/Leroy888/DelphiTestSystem/abama/Installer/updates.json";
    QDesktopServices::openUrl (QUrl::fromLocalFile (QString("./WKEProgramUpdater.exe")));

}


void clsMainTestWindow::on_btnRunSettings_clicked()
{
    clsRunningSettings *dlg = new clsRunningSettings(this);
    dlg->setWindowTitle(tr("运行设定"));
    dlg->exec();
    btnReptive->setChecked(false);
    btnReptive->setEnabled(sngRunSettings::Ins()->getRemoteControlType() == clsRunSettings::ManualTrig);
}
