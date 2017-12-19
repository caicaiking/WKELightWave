#include "clsWK6500RunningMode.h"
#include "clsLcrConnection.h"
#include <QJsonDocument>
#include "clsSingleTrig.h"
#include <QJsonParseError>
#include <QVariantMap>
#include "doubleType.h"
#include "clsMeterLimit.h"
#include "clsFtdiOperation.h"
clsWK6500RunningMode::clsWK6500RunningMode(clsInstrument *parent): clsInstrument(parent)
{
    for(int i=0; i<4; i++)
    {
        limits << new clsMeterLimit();
        results <<0;
    }

}

void clsWK6500RunningMode::initConnection()
{
    sngLCRCnnt::Ins()->setupConnection();
}

bool clsWK6500RunningMode::connectionStatus()
{
    isConnected = sngLCRCnnt::Ins()->hasInitSucess();
    emit this->setConnectStatus(isConnected);
    return isConnected;

}

void clsWK6500RunningMode::setCondition(QString value)
{
    this->strConditon = value;
    QJsonParseError error;
    QJsonDocument jsondocument=QJsonDocument::fromJson(strConditon.toUtf8(),&error);
    if(error.error!=QJsonParseError::NoError)
        return;
    if(jsondocument.isNull() || jsondocument.isEmpty())
        return;

    QVariantMap tmpMap = jsondocument.toVariant().toMap();

    if(tmpMap["meter"].toString() != getInstrumentType()) //判断是否为当前的仪表设置条件
        return;

    if(tmpMap["channel"].toInt()==0)
        return;
    else
        this->channel=  tmpMap["channel"].toInt();

    QString tmpConditon = tmpMap["conditions"].toString();
    if(tmpConditon.isEmpty())
        return;

    jsondocument = QJsonDocument::fromJson(tmpConditon.toUtf8(), &error);
    if(error.error!=QJsonParseError::NoError)
        return;
    if(jsondocument.isNull() || jsondocument.isEmpty())
        return;

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
        this->item1HiLimit=conditionMap["item1HiLimit"].toDouble();
        this->item1LowLimit=conditionMap["item1LowLimit"].toDouble();
        this->item2HiLimit=conditionMap["item2HiLimit"].toDouble();
        this->item2LowLimit=conditionMap["item2LowLimit"].toDouble();
        this->suffix1=conditionMap["suffix1"].toString();
        this->suffix2=conditionMap["suffix2"].toString();

        limits.at(0)->setAbsHi(item1HiLimit);
        limits.at(0)->setAbsLo(item1LowLimit);
        limits.at(0)->setLimitType("Norm");

        limits.at(1)->setAbsHi(item2HiLimit);
        limits.at(1)->setAbsLo(item2LowLimit);
        limits.at(1)->setLimitType("Norm");

    }


}

QString clsWK6500RunningMode::getCondition()
{
    return this->strConditon;
}

bool clsWK6500RunningMode::trig()
{
    updateGpibCommand(); //更新GPIB 指令
    //TODO: 将来这儿会加入多通道的数值计算，如果没有使用多通道则使用仪器的原始数据
    QString res = sngLCRCnnt::Ins()->sendCommand(":METER:TRIG",true);
    res +=",,";

    QStringList resList = res.split(",");

    double res1, res2;
    res1 = resList.at(0).toDouble();
    res2 = resList.at(1).toDouble();

    clsSingleTrig d;
    d.setZm(res1);
    d.setAm(res2);

    d.setFrequency(this->frequency);
    d.setChannel(this->channel);

    d.doRCCalibration();


    results.clear();
    results.append(d.getItem(item1, this->equcct));
    results.append(d.getItem(item2, this->equcct));
    return true;
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
    bool status = limits.at(i)->comparaValue(results.at(i));
    return status;
}

bool clsWK6500RunningMode::getTotleStatus()
{
    bool status = true;
    for(int i=0; i< getItemsCount() ; i++)
    {
        status &= getItemStatus(i);
    }
    return status;
}

QString clsWK6500RunningMode::getItem(int i)
{
    QStringList items;
    items << item1 << item2;
    return items.at(i);
}

QString clsWK6500RunningMode::getItemSuffix(int i)
{
    QStringList suffix;
    suffix << suffix1 << suffix2;
    return suffix.at(i);
}

double clsWK6500RunningMode::getItemValue(int i)
{
    return results.at(i);
}

double clsWK6500RunningMode::getItemValueWithSuffix(int i)
{
    doubleType dt;
    QStringList suffix;
    suffix << suffix1 << suffix2;

    dt.setData(results.at(i));
    if(suffix.at(i)!= tr("自动"))
        return dt.formateWithUnit(suffix.at(i), 7).toDouble();
    else
        return getItemValue(i); //当设置用Auto的话，就返回原始值
}

QString clsWK6500RunningMode::getInstrumentType()
{
    return "WK6500";
}

void clsWK6500RunningMode::turnOffOutput()
{
    QString meter = ":METER:";
    QString tmpBiasStatusCmd = meter+"BIAS-STAT "+"OFF"+";";
    sngLCRCnnt::Ins()->sendCommand(tmpBiasStatusCmd,false);
    this->biasCommand = tmpBiasStatusCmd;

}

void clsWK6500RunningMode::clearGpibCommands()
{
    this->normCommands.clear();
    this->biasCommand.clear();
}
QString clsWK6500RunningMode::changeItemToGpib(QString value)
{
    if(value == "E'r")
        return "EPR";
    if(value == "E\"r")
        return "EPPR";
    if(value == "De")
        return "DE";
    if(value == "U'r")
        return "UPR";
    if(value == "U\"r")
        return "UPPR";
    if(value == "Du")
        return "DU";
    if(value == "A")
        return "ANGLE";

    return value;


}

void clsWK6500RunningMode::updateGpibCommand()
{
    QString meter = ":METER:";
    QStringList gpibCmd;
#ifdef USE_MULTI_CHANNEL
    gpibCmd.append(meter+"FUNC:1 "+changeItemToGpib("Z")+";");  //item1 GPIB
    gpibCmd.append(meter+"FUNC:2 "+changeItemToGpib("ANGLE")+";");  //Item2 GPIB
    gpibCmd.append(meter+"EQU-CCT "+"SER"+";");
#else
    gpibCmd.append(meter+"FUNC:1 "+changeItemToGpib(item1)+";");  //item1 GPIB
    gpibCmd.append(meter+"FUNC:2 "+changeItemToGpib(item2)+";");  //Item2 GPIB
    if(equcct==tr("串联"))                       //等效电路
        gpibCmd.append(meter+"EQU-CCT "+"SER"+";");
    else
        gpibCmd.append(meter+"EQU-CCT "+"PAR"+";");

#endif
    if(range ==tr("自动"))                        //档位
        gpibCmd.append(meter+"RANGE "+"AUTO"+";");
    else
        gpibCmd.append(meter+"RANGE "+range+";");

    if(speed ==tr("最快"))                        //速度
        gpibCmd.append(meter+"SPEED "+"MAX"+";");
    else if(speed ==tr("快速"))
        gpibCmd.append(meter+"SPEED "+"FAST"+";");
    else if(speed ==tr("中速"))
        gpibCmd.append(meter+"SPEED "+"MED"+";");
    else if(speed ==tr("慢速"))
        gpibCmd.append(meter+"SPEED "+"SLOW"+";");
    else
        gpibCmd.append(meter+"SPEED "+"MAX"+";");

    gpibCmd.append(meter+"FREQ "+QString::number(frequency,'f',6)+";");   //频率
    gpibCmd.append(meter+"LEVEL "+QString::number(level)+levelUnit+";");

    if(biasType=="V")                          //Bias
    {
        gpibCmd.append(meter+"BIAS-TYPE "+"VOL"+";");
        gpibCmd.append(meter+"BIAS "+QString::number(bias)+";");
    }
    else
    {
        gpibCmd.append(meter+"BIAS-TYPE "+"CUR"+";");
        gpibCmd.append(meter+"BIAS "+QString::number(bias)+";");
    }


    //更新GPIB的条件
    if(this->normCommands.length()!= gpibCmd.length())
    {
        for(int i=0; i< gpibCmd.length(); i++)
        {
            sngLCRCnnt::Ins()->sendCommand(gpibCmd.at(i),false);
        }
    }
    else
    {
        for(int i=0; i< gpibCmd.length(); i++)
        {
            if(normCommands.at(i) != gpibCmd.at(i))
            {
                sngLCRCnnt::Ins()->sendCommand(gpibCmd.at(i),false);
            }
        }
    }
    normCommands = gpibCmd;

    QString tmpBiasStatusCmd;

    if(this->biasSwitch==tr("开"))
        tmpBiasStatusCmd = meter+"BIAS-STAT "+"ON"+";";
    else
        tmpBiasStatusCmd = meter+"BIAS-STAT "+"OFF"+";";

    if(this->biasCommand != tmpBiasStatusCmd)
    {
        sngLCRCnnt::Ins()->sendCommand(tmpBiasStatusCmd,false);
        this->biasCommand == tmpBiasStatusCmd;
    }

    clsConnectSWBox::Ins()->setRelay(relaySwitch==tr("开")?false:true);

}

