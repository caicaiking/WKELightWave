#include "clsRunService.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QVariantMap>
#include "clsRunningMeterFactory.h"
#include "clsSignalStatus.h"
#include "clsFtdiOperation.h"

#include <QTextStream>
#include <stdio.h>


clsRunService::clsRunService(QObject *parent) : QObject(parent)
{
    isRunningMode = false;
    isReset = false;

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

    emit showMsg(tr("步骤总数 %1 ").arg(steps.length()));
}

void clsRunService::switchToRunningMode(bool value)
{
    this->isRunningMode = value;
    this->isReset = false;
}

void clsRunService::trig()
{

    if(!isRunningMode)
        return;

    sngSignalStatus::Ins()->resetHVStatus(); //恢复原始值
    sngSignalStatus::Ins()->resetLCRStatus();//恢复原始值


    for(int i=0; i<steps.length(); i++)
    {
        meter = clsRunningMeterFactory::getMeter(steps.at(i)->meter);

        if(meter ==0)
            continue;

        if(isReset)
            goto RESET;
        //get current test step
        clsTestConditons *tmpStep = steps.at(i);

        //Set busy
        sngFtdiOp::Ins()->setBusy(true);
        //切换通道
        sngFtdiOp::Ins()->setChannel(tmpStep->channel);
        //更新仪表的测试条件
        meter->setCondition(tmpStep->condition);
        //仪表测试
        meter->trig();
        //关闭仪表的输出
        meter->turnOffOutput();
        //设置单步状态
        sngSignalStatus::Ins()->setStatus(tmpStep->meter,meter->getTotleStatus());

        //For output result for display & save
        QVariantMap tmpMap;
        tmpMap.insert("step", i);
        tmpMap.insert("meter", tmpStep->meter);
        tmpMap.insert("channel", tmpStep->channel);

        QVariantList res;
        for(int i=0; i< meter->getItemsCount(); i++)
        {
            QVariantMap tmpRes;
            tmpRes.insert("item", meter->getItem(i));
            tmpRes.insert("result", meter->getItemValue(i));
            tmpRes.insert("suffix", meter->getItemSuffix(i));
            tmpRes.insert("status", meter->getItemStatus(i));

            res.append(tmpRes);
        }

        tmpMap.insert("data", res);
        QJsonDocument jsd = QJsonDocument::fromVariant(tmpMap);
        emit showRes(jsd.toJson());

    }

    //set bing PASS Fail
    sngFtdiOp::Ins()->setLcrPassFail(sngSignalStatus::Ins()->getLcrStatus());
    //set binning HV Pass Fail
    sngFtdiOp::Ins()->setHvPassFail(sngSignalStatus::Ins()->getHvStatus());
    //set binning Busy line down
    sngFtdiOp::Ins()->setBusy(false);
    goto END;

RESET:
    sngFtdiOp::Ins()->setBusy(false);
    qDebug()<<"Reset";
END:
    qDebug()<<"End";

}

void clsRunService::reset()
{
    isReset = true;
    sngFtdiOp::Ins()->setBusy(false);
}
