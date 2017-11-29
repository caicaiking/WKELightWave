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

clsMainTestWindow::clsMainTestWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint
                         | Qt::WindowMaximizeButtonHint);
    this->showMaximized();

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

void clsMainTestWindow::on_btnSettings_clicked()
{
    for(int i=0; i< items.length(); i++)
    {
        items[i]->setChannelSettings();
        items[i]->setCloseEnabled(true);
    }

    btnNewSetup->setEnabled(true);
    btnOpenSetup->setEnabled(true);
    btnSaveSetup->setEnabled(true);
    btnTrig->setEnabled(false);

    sngRunService::Ins()->switchToRunningMode(false);
    disconnect(trigThread,SIGNAL(getSignal()),sngRunService::Ins(),SLOT(trig()));
    disconnect(resetThread,SIGNAL(getSignal()),sngRunService::Ins(),SLOT(reset()));


}

void clsMainTestWindow::on_btnRunning_clicked()
{
    for(int i=0; i< items.length(); i++)
    {
        items[i]->setChannelRunnings();
        items[i]->setCloseEnabled(false);
    }
    btnNewSetup->setEnabled(false);
    btnOpenSetup->setEnabled(false);
    btnSaveSetup->setEnabled(false);
    btnTrig->setEnabled(true);

    sngRunService::Ins()->setTestConditon(getTestCondition());
    sngRunService::Ins()->switchToRunningMode(true);

    connect(trigThread,SIGNAL(getSignal()),sngRunService::Ins(),SLOT(trig()));
    connect(resetThread,SIGNAL(getSignal()),sngRunService::Ins(),SLOT(reset()));



}

void clsMainTestWindow::deleteChannel(int index)
{
    steps.removeAt(index);

    updateChannelSettings(steps);
}

void clsMainTestWindow::showChannelRes(QString res)
{
    qDebug()<<res;
}

void clsMainTestWindow::on_btnSaveSetup_clicked()
{
    QString strPath=QFileDialog::getSaveFileName(this,tr("保存测试任务"), ".",
                                                 tr("WKE FactoryView 任务 (*.wket)"),0);
    QString strSetup;
    strSetup = getTestCondition();

    if(strPath.isEmpty())
        return;
    else
    {
        QFile file(strPath);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream outStream(&file);
        outStream<<strSetup;
        outStream.flush();
        file.close();
    }
}

void clsMainTestWindow::on_btnOpenSetup_clicked()
{
    QString strPath=QFileDialog::getOpenFileName(this,tr("保存测试任务"), ".",
                                                 tr("WKE FactoryView 任务 (*.wket)"),0);
    QString strSetup;
    if(strPath.isEmpty())
        return;
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
                clsTestConditons* tmp = new clsTestConditons();
                tmp->setJson(tmpConditionList.at(i).toString());

                steps.append(tmp);
            }
        }
    }
    updateChannelSettings(steps);
}

void clsMainTestWindow::on_btnTrig_clicked()
{
   sngRunService::Ins()->trig();
}
