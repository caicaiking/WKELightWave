#include "clsHVRunningMode.h"
#include <QTextStream>
#include <stdio.h>
#include <QJsonDocument>
#include "clsTestConditon.h"
#include <QJsonParseError>
#include <QDebug>
#include "clsHVConnection.h"
#include "publicUtility.h"
#include "doubleType.h"
#include "clsFtdiOperation.h"
clsHVRunningMode::clsHVRunningMode(clsInstrument *parent): clsInstrument(parent)
{
    for(int i=0; i<4; i++)
    {
        limits << new clsMeterLimit();
        results <<0;
    }
}

void clsHVRunningMode::initConnection()
{
    isConnected = sngHVCnnt::Ins()->setupConnection();
}

bool clsHVRunningMode::connectionStatus()
{
    return isConnected;
}

void clsHVRunningMode::setCondition(QString value)
{
    this->strCondition = value;
    QJsonParseError error;
    QJsonDocument jsonDoucment = QJsonDocument::fromJson(strCondition.toUtf8(), &error);
    if(error.error != QJsonParseError::NoError)
        return;

    if(jsonDoucment.isNull() || jsonDoucment.isEmpty())
        return;

    QVariantMap tmpMap = jsonDoucment.toVariant().toMap();
    if(tmpMap["meter"].toString() != getInstrumentType()) //判断是否为当前仪表设置条件
        return;

    QString tmpCondition = tmpMap["conditions"].toString();
    if(tmpCondition.isEmpty())
        return;

    jsonDoucment = QJsonDocument::fromJson(tmpCondition.toUtf8(), &error);
    if(error.error != QJsonParseError::NoError)
        return;
    if(jsonDoucment.isEmpty() || jsonDoucment.isNull())
        return;

    if(jsonDoucment.isObject())
    {
        QVariantMap conditionMap = jsonDoucment.toVariant().toMap();
        this->item = conditionMap["item"].toString();
        this->suffix = conditionMap["suffix"].toString();
        this->voltage=conditionMap["voltage"].toDouble();
        this->relaySwitch=conditionMap["relaySwitch"].toString();
        this->hiLimit=conditionMap["hiLimit"].toDouble();
        this->lowLimit=conditionMap["lowLimit"].toDouble();

        limits.at(0)->setAbsHi(hiLimit);
        limits.at(0)->setAbsLo(lowLimit);
        limits.at(0)->setLimitType("Norm");
    }
}

QString clsHVRunningMode::getCondition()
{
    return this->strCondition;
}

bool clsHVRunningMode::trig()
{
    updateGpibCommands(); //更新指令
    emit voltageOutput(true);
    publicUtility::sleepMs(200);

    QString res = sngHVCnnt::Ins()->sendCommand(HVTRGCMD, true);
    res +=",,";
    results.clear();

    QStringList  resList = res.split(",");
    results.append(resList.at(0).toDouble());

    return true;

}

int clsHVRunningMode::getItemsCount()
{
    return 1; //只有一个返回值
}

bool clsHVRunningMode::getItemStatus(int i)
{
    return limits.at(i)->comparaValue(results.at(i));
}

bool clsHVRunningMode::getTotleStatus()
{
    bool status = true;
    for(int i =0; i< getItemsCount(); i++)
    {
        status &= getItemStatus(i);
    }
    return status;
}

QString clsHVRunningMode::getItem(int i)
{
    QStringList items;
    items<< item << "" << "";
    return items.at(i);
}

QString clsHVRunningMode::getItemSuffix(int i)
{
    QStringList suffixs;
    suffixs<< suffix << "" << "";
    return suffixs.at(i);

}

double clsHVRunningMode::getItemValue(int i)
{
    return results.at(i);
}

double clsHVRunningMode::getItemValueWithSuffix(int i)
{
    doubleType dt;
    dt.setData(results.at(i));
    if(suffix == tr("自动"))
    {
        return getItemValue(i); //如果是自动的话，就返回原始数据
    }
    else
    {
        return dt.formateWithUnit(suffix, 7).toDouble();
    }
}

QString clsHVRunningMode::getInstrumentType()
{
    return "HV";
}

void clsHVRunningMode::turnOffOutput()
{
    sngHVCnnt::Ins()->sendCommand(HVTURNOFFCMD,false);
    emit voltageOutput(false);
}

void clsHVRunningMode::updateGpibCommands()
{
    //仪表的GPIB指令


    //控制盒的开关通断
    sngFtdiOp::Ins()->setRelay(relaySwitch==tr("开")?false:true);
}
