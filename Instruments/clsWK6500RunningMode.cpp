#include "clsWK6500RunningMode.h"
#include "clsLcrConnection.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QVariantMap>
clsWK6500RunningMode::clsWK6500RunningMode(clsInstrument *parent): clsInstrument(parent)
{

}

void clsWK6500RunningMode::initConnection()
{
    sngLCRCnnt::Ins()->setupConnection();
}

bool clsWK6500RunningMode::connectionStatus()
{
    isConnected = sngLCRCnnt::Ins()->hasInitSucess();
    emit this->setConnectStatus(isConnected);

}

void clsWK6500RunningMode::setCondition(QString value)
{
    this->strConditon = value;
    QJsonParseError error;
    QJsonDocument jsondocument=QJsonDocument::fromJson(strConditon.toUtf8(),&error);
    if(error.error==QJsonParseError::NoError)
    {
        if(!(jsondocument.isNull() || jsondocument.isEmpty()))
        {
            if(jsondocument.isObject())
            {
                QVariantMap conditionMap=jsondocument.toVariant().toMap();
                this->item1=conditionMap["item1"].toString();
                this->item2=conditionMap["item2"].toString();
                this->isItem2Enable = conditionMap["isItem2Enable"].toBool();
                this->frequency=conditionMap["frequency"].toDouble();
                this->level=conditionMap["level"].toDouble();
                this->levelUnit=conditionMap["levelUnit"].toString();
                this->range=conditionMap["range"].toString();
                this->speed=conditionMap["speed"].toString();
                this->equcct=conditionMap["equcct"].toString();
                this->bias=conditionMap["bias"].toDouble();
                this->biasSwitch=conditionMap["biasSwitch"].toString();
                this->biasType=conditionMap["biasType"].toString();
                this->relaySwitch=conditionMap["relaySwitch"].toString();
                this->item1HiLimit=conditionMap["item1Hilimit"].toDouble();
                this->item1LowLimit=conditionMap["item1LowLimit"].toDouble();
                this->item2HiLimit=conditionMap["item2Hilimit"].toDouble();
                this->item2LowLimit=conditionMap["item2LowLimit"].toDouble();
                this->suffix1=conditionMap["suffix1"].toString();
                this->suffix2=conditionMap["suffix2"].toString();
            }
        }
    }
}

QString clsWK6500RunningMode::getCondition()
{
   return this->strConditon;
}

bool clsWK6500RunningMode::trig()
{
    QString res = sngLCRCnnt::Ins()->sendCommand(":METER:TRIG",true);
    res +=",,";

    QStringList resList = res.split(",");

    results.append(resList.at(0).toDouble());
    results.append(resList.at(1).toDouble());

}

int clsWK6500RunningMode::getItemsCount()
{
    if(isItem2Enable)
        return 2;
    else
        return 1;
}

bool clsWK6500RunningMode::getItemStatus(int i)
{
    return true;
}

bool clsWK6500RunningMode::getTotleStatus()
{
    return true;
}

double clsWK6500RunningMode::getItemValue(int i)
{
    return results.at(i);
}

double clsWK6500RunningMode::getItemValueWithSuffix(int i)
{
    return results.at(i);
}

QString clsWK6500RunningMode::getInstrumentType()
{
    return "WK6500";
}

void clsWK6500RunningMode::turnOffOutput()
{

}
