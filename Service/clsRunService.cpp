#include "clsRunService.h"
#include <QDir>
#include "clsSettings.h"
#include <QDate>
#include "publicUtility.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QVariantMap>
#include "clsRunningMeterFactory.h"
#include "clsSignalStatus.h"
#include "clsFtdiOperation.h"
#include <QTextStream>
#include <stdio.h>
#include <QApplication>
#include "clsRunSettings.h"
#include "clsConnectToServer.h"
clsRunService::clsRunService(QObject *parent) : QObject(parent)
{
    isRunningMode = false;
    isReset = false;
    file =0;
    isInTesting = false;

}

clsRunService::~clsRunService()
{
    if(file != 0 && file->isOpen())
    {
        file->flush();
        file->close();
    }

}

void clsRunService::setTestConditon(QString value)
{
    this->strCondition = value;

    QJsonDocument jsonDocument;
    QJsonParseError error;

    jsonDocument = QJsonDocument::fromJson(this->strCondition.toUtf8(),&error);

    if(error.error != QJsonParseError::NoError)
        return;

    if(jsonDocument.isEmpty() || jsonDocument.isNull())
        return;

    QVariantList list = jsonDocument.toVariant().toList();

    steps.clear();
    for(int i=0; i<list.length(); i++)
    {
        clsTestConditons *tmp = new clsTestConditons();
        tmp->setJson(list.at(i).toString());
        steps.append(tmp);
    }

    sngWK6500Run::Ins()->clearGpibCommands();
    sngHVRun::Ins()->clearGpibCommands();

    emit showMsg(tr("步骤总数 %1 ").arg(steps.length()));
}

void clsRunService::switchToRunningMode(bool value)
{
    this->isRunningMode = value;
    this->isReset = false;


    if(isRunningMode)
    {
        if(file != 0)
        {
            file->flush();
            file->close();
        }

        QDir d(getLastFilePath() + "/AutoSaveData");
        if(!d.exists())
            d.mkdir(getLastFilePath() + "/AutoSaveData");

        file = new QFile(getLastFilePath() + "/AutoSaveData/" + QDate::currentDate().toString("yyyy_MM_dd")+" "+
                         QTime::currentTime().toString("HH_mm_ss") +".csv");
        if(!file->open(QIODevice::Append |QIODevice::Text))
        {
            qDebug()<<"Open Data file error!";
            return ;
        }

        QTextStream out(file);
        QStringList title ;     //写入数据文件标题
        for(int i=0; i< steps.length(); i++)
        {
            meter = clsRunningMeterFactory::getMeter(steps.at(i)->meter);

            clsTestConditons * tmpStep = steps.at(i);
            meter->setCondition(tmpStep->condition);
            title.append(tr("Channel"));

            for(int j=0; j< meter->getItemsCount(); j++)
            {
                title.append(meter->getItem(j));
            }
            title.append("Status");
        }
        title.append("Date");
        title.append("Time");

        if(QLocale::system().decimalPoint() =='.')
            sep = ",";
        else
            sep = ";";

        QString strTitle = title.join(sep) +"\n";
        out<<strTitle.toUtf8();
        out.flush();
    }
    else
    {
        if(file != 0)
        {
            file->flush();
            file->close();
            file =0;
        }
    }
}
QString clsRunService::getLastFilePath()
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

void clsRunService::manulTrig()
{

    if(!isRunningMode)
        return;
    emit trigSignal();

    if(isInTesting)
        return;

    isInTesting = true;

    //Set busy
    clsConnectSWBox::Ins()->setBusy(true);

    //触发测试
    trig();

    int sendValue =0;
    if(sngSignalStatus::Ins()->getLcrStatus())
        sendValue +=2;
    if(sngSignalStatus::Ins()->getHvStatus())
        sendValue += 4;
    if(sngSignalStatus::Ins()->getLcrStatus() && sngSignalStatus::Ins()->getHvStatus())
        sendValue += 8;
    clsConnectSWBox::Ins()->setIo(sendValue);

    isInTesting = false;
}

void clsRunService::handlerTrig()
{
    if(!isRunningMode)
        return;
    emit trigSignal();

    if(isInTesting)
        return;

    isInTesting = true;

    //Set busy
    clsConnectSWBox::Ins()->setBusy(true);

    //触发测试
    trig();

    int sendValue =0;

    if(sngSignalStatus::Ins()->getLcrStatus())
        sendValue +=2;
    if(sngSignalStatus::Ins()->getHvStatus())
        sendValue += 4;
    if(sngSignalStatus::Ins()->getLcrStatus() && sngSignalStatus::Ins()->getHvStatus())
        sendValue += 8;
    clsConnectSWBox::Ins()->setIo(sendValue);

//    //set bing PASS Fail
//    clsConnectSWBox::Ins()->setLcrPassFail(sngSignalStatus::Ins()->getLcrStatus());
//    //set binning HV Pass Fail
//    clsConnectSWBox::Ins()->setHvPassFail(sngSignalStatus::Ins()->getHvStatus());
//    //set binning Busy line down
//    clsConnectSWBox::Ins()->setBusy(false);
    emit controlStatus(tr("Handler Remote"));

    isInTesting = false;
}

void clsRunService::lanTrig()
{
    if(!isRunningMode)
        return ;

    emit controlStatus(tr("Lan Remote"));

    emit trigSignal();

    trig();

    bool lcrStatus = sngSignalStatus::Ins()->getLcrStatus();
    bool hvStatus = sngSignalStatus::Ins()->getHvStatus();

    QStringList totleStatus;
    totleStatus.append((lcrStatus && hvStatus) ? "1":"0");
    totleStatus.append((lcrStatus) ? "1":"0");
    totleStatus.append((hvStatus) ? "1":"0");

    QString strTotleStatus = totleStatus.join(",");

    sngConnectServer::Ins()->writeRes(strTotleStatus);

}

void clsRunService::trig()
{
    QStringList results;
    sngSignalStatus::Ins()->resetHVStatus(); //恢复原始值
    sngSignalStatus::Ins()->resetLCRStatus();//恢复原始值

    emit busyStatus(true);
    qApp->processEvents();
    for(int i=0; i<steps.length(); i++)
    {
        emit currentStep(i);
        qApp->processEvents();
        meter = clsRunningMeterFactory::getMeter(steps.at(i)->meter);

        if(meter ==0)
            continue;

        if(isReset)
            goto RESET;
        //get current test step
        clsTestConditons *tmpStep = steps.at(i);

        //切换通道
        clsConnectSWBox::Ins()->setChannel(QPoint(tmpStep->channel.x(),tmpStep->channel.y()),tmpStep->meter);
        //数据记录
        results.append(QString("c%1-%2").arg(tmpStep->channel.x()).arg(tmpStep->channel.y()));

        //更新仪表的测试条件
        meter->setCondition(tmpStep->condition);
        //仪表测试
        meter->trig();
        //设置单步状态
        sngSignalStatus::Ins()->setStatus(tmpStep->meter,meter->getTotleStatus());

        //关闭仪表的输出
        meter->turnOffOutput();

        //For output result for display & save
        QVariantMap tmpMap;
        tmpMap.insert("step", i);
        tmpMap.insert("meter", tmpStep->meter);
        tmpMap.insert("channelStart", tmpStep->channel.x());
        tmpMap.insert("channelStop", tmpStep->channel.y());

        QVariantList res;
        for(int j=0; j< meter->getItemsCount(); j++)
        {
            QVariantMap tmpRes;
            tmpRes.insert("item", meter->getItem(j));
            tmpRes.insert("result", meter->getItemValue(j));
            tmpRes.insert("suffix", meter->getItemSuffix(j));
            tmpRes.insert("status", meter->getItemStatus(j));

            res.append(tmpRes);

            results.append(QString::number(meter->getItemValue(j),'E',6));
        }
        results.append(meter->getTotleStatus()?"PASS": "FAIL");


        tmpMap.insert("data", res);
        QJsonDocument jsd = QJsonDocument::fromVariant(tmpMap);
        emit showRes(jsd.toJson()); //显示测试结果

        if(meter->getTotleStatus()== false && sngRunSettings::Ins()->getJumpOut()) //当测试当前步骤失败就跳出循环
            break;
    }
    emit currentStep(-1);

    emit lcrPF(sngSignalStatus::Ins()->getLcrStatus());
    emit hvPF(sngSignalStatus::Ins()->getHvStatus());
    emit busyStatus(false);
    qApp->processEvents();

    if(file->isOpen())
    {
        QTextStream out(file);
        QString timeDate = QDate::currentDate().toString("yyyy/MM/dd")+sep + QTime::currentTime().toString("HH:mm:ss");
        QString strRes = results.join(sep)+ sep+ timeDate +"\n";
        out<<strRes.toUtf8();
      //  out.flush();
    }
    goto END;
RESET:
    emit busyStatus(false);
    qApp->processEvents();
END:
    return;
}

void clsRunService::reset()
{
    emit resetSignal();
    isReset = true;
    clsConnectSWBox::Ins()->setBusy(false);
    emit busyStatus(false);
}
