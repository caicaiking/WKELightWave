#include "clsWKCommandProcess.h"
#include <QDebug>
#include <QStringListIterator>
#include "clsWK6500P.h"

clsWKCommandProcess::clsWKCommandProcess(QObject *parent) : QObject(parent)
{
    //注册所有的函数，用其GPIB指令注册其Key
    queryFunction.insert("*IDN?",&clsWKCommandProcess::queryId);
    queryFunction.insert("*OPT2?",&clsWKCommandProcess::querySWOption);
    queryFunction.insert("*BIASFITEXT?",&clsWKCommandProcess::queryBiasFitExit);
    queryFunction.insert("*SYSBIAS?",&clsWKCommandProcess::querySysBias);
    queryFunction.insert("*EXTBIASUNIT?",&clsWKCommandProcess::queryBiasUnit);

    queryFunction.insert("FUNC:1?",&clsWKCommandProcess::queryItem1);
    queryFunction.insert("FUNC:2?",&clsWKCommandProcess::queryItem2);
    queryFunction.insert("EQU-CCT?",&clsWKCommandProcess::queryEqucct);
    queryFunction.insert("RANGE?",&clsWKCommandProcess::queryRange);
    queryFunction.insert("FREQ?",&clsWKCommandProcess::queryFrequency);
    queryFunction.insert("DRIVE?",&clsWKCommandProcess::queryLevelType);
    queryFunction.insert("LEVEL?",&clsWKCommandProcess::queryLevelValue);
    queryFunction.insert("BIAS?",&clsWKCommandProcess::queryBiasValue);
    queryFunction.insert("BIAS-TYPE?",&clsWKCommandProcess::queryBiasType);
    queryFunction.insert("BIAS-STAT?",&clsWKCommandProcess::queryBiasStatus);
    queryFunction.insert("SPEED?",&clsWKCommandProcess::querySpeed);

    setFunction.insert("FUNC:1",&clsWKCommandProcess::setItem1);
    setFunction.insert("FUNC:2",&clsWKCommandProcess::setItem2);
    setFunction.insert("EQU-CCT",&clsWKCommandProcess::setEqucct);
    setFunction.insert("RANGE",&clsWKCommandProcess::setRange);
    setFunction.insert("FREQ",&clsWKCommandProcess::setFrequency);
    setFunction.insert("LEVEL",&clsWKCommandProcess::setLevelValue);
    setFunction.insert("BIAS",&clsWKCommandProcess::setBiasValue);
    setFunction.insert("BIAS-TYPE",&clsWKCommandProcess::setBiasType);
    setFunction.insert("BIAS-STAT",&clsWKCommandProcess::setBiasStatus);
    setFunction.insert("SPEED",&clsWKCommandProcess::setSpeed);
    setFunction.insert("FAST-GPIB",&clsWKCommandProcess::setFastGpib);
    setFunction.insert("TRIG",&clsWKCommandProcess::trig);
    this->lastCmmdType =0;
}

void clsWKCommandProcess::setIsRemote(bool value) {
    emit lanRemote(value);
}

void clsWKCommandProcess::setGpibCommand(QString str)
{

    qDebug()<< str;
    if(str == " ")
        return ;
    //根指令1st， 根指令2end
    QString strMode1st, strMode2end;

    QStringList cmdList = str.split(";",QString::SkipEmptyParts); //将指令分开用;，并且省略了空白部分。

    QListIterator<QString> it(cmdList);
    lastCmmdType=0;
    while(it.hasNext())
    {
        QString tmpStr = it.next();

        if(!tmpStr.isEmpty())
        {
            if(tmpStr.contains("?")) //查询指令开始
            {
                lastCmmdType =2;
                QStringList modes= tmpStr.split(":",QString::SkipEmptyParts);
                if(modes.length()==1 && queryFunction.keys().contains(modes.at(0)))//通用的IEE488指令查询
                {

                    (this->*(queryFunction.value(modes.at(0))))();
                }
                else if( modes.length()==2 && queryFunction.keys().contains(modes.at(1)))//通用的仪器指令查询
                {

                    (this->*(queryFunction.value(modes.at(1))))();
                }
                else if(modes.length()==3 && queryFunction.keys().contains(modes.at(1)+":"+modes.at(2)))//有副根指令的参数查询
                {

                    (this->*(queryFunction.value(modes.at(1)+":"+modes.at(2))))();
                }
                else//GPIB处理出错
                {
                    writeToClient("Send Command error!");
                }

            }
            else //设置指令开始
            {
                lastCmmdType =1;
                QStringList pars = tmpStr.split(" ",QString::SkipEmptyParts);

                if(pars.length()==1) //没有参数的设置指令 :METER:TRIG
                {
                    QStringList modes = pars.at(0).split(":",QString::SkipEmptyParts);
                    if(modes.length()==1 && setFunction.keys().contains(modes.at(0))) //如 *TRG
                        (this->*(setFunction.value(modes.at(0))))("");
                    else if(modes.length()==2 && setFunction.keys().contains(modes.at(1))) //如 :METER:TRIG
                        (this->*(setFunction.value(modes.at(1))))("");
                    else
                    {
                        writeToClient("Send Command error!");
                    }

                }
                else if(pars.length()==2) //有参数的设置指令
                {
                    QString par = pars.at(1);
                    QString strMode = pars.at(0);
                    QStringList modes = strMode.split(":",QString::SkipEmptyParts);

                    if(modes.length()==3) //有副根指令的命令， 如： :METER:FUNC:1 C
                    {
                        strMode1st = modes.at(0);
                        strMode2end = modes.at(1);
                        QString strItem = modes.at(2);

                        if(setFunction.keys().contains(strMode2end+":"+strItem))
                        {
                            (this->*(setFunction.value(strMode2end+":"+strItem)))(par);
                        }
                    }
                    else if(modes.length() ==2) //一般的设置指令
                    {
                        strMode1st = modes.at(0);
                        strMode2end = modes.at(1);

                        if(setFunction.keys().contains(strMode2end))
                        {
                            (this->*(setFunction.value(strMode2end)))(par);
                        }
                    }
                    else if(modes.length()==1) //如 2 D这样的指令
                    {
                        if(setFunction.keys().contains(strMode2end+":"+modes.at(0)))
                        {
                            (this->*(setFunction.value(strMode2end+":"+modes.at(0))))(par);

                        }
                    }
                    else
                    {
                        writeToClient("Send Command error!");
                    }
                }
            }
        }
    }

    if(this->lastCmmdType == 1)
        writeToClient(" ");
}

void clsWKCommandProcess::queryId()
{
    writeToClient("WAYNE KERR, 65120P, Simulator-Abama, 0.1");
}

void clsWKCommandProcess::querySWOption()
{
    writeToClient(sngWK6500::Instance()->getSWOption());
}

void clsWKCommandProcess::trig(const QString &/*empty*/ )
{
    this->lastCmmdType = 2;
    writeToClient(sngWK6500::Instance()->gpibTrig());
}

void clsWKCommandProcess::queryItem1()
{
    writeToClient(sngWK6500::Instance()->getGpibItem1());
}

void clsWKCommandProcess::queryItem2()
{

    writeToClient(sngWK6500::Instance()->getGpibItem2());
}

void clsWKCommandProcess::queryEqucct()
{
    writeToClient(sngWK6500::Instance()->getGpibEqucct());
}

void clsWKCommandProcess::queryRange()
{
    writeToClient(sngWK6500::Instance()->getGpibRange());
}

void clsWKCommandProcess::queryFrequency()
{
    writeToClient(sngWK6500::Instance()->getGpibFrequency());
}

void clsWKCommandProcess::queryLevelValue()
{
    writeToClient(sngWK6500::Instance()->getGpibLevelValue());
}

void clsWKCommandProcess::queryLevelType()
{
    writeToClient(sngWK6500::Instance()->getGpibLevelType());
}

void clsWKCommandProcess::queryBiasValue()
{
    writeToClient(sngWK6500::Instance()->getGpibBiasValue());
}

void clsWKCommandProcess::queryBiasType()
{
    writeToClient(sngWK6500::Instance()->getGpibBiasType());
}

void clsWKCommandProcess::queryBiasStatus()
{
    writeToClient(sngWK6500::Instance()->getGpibBiasONOFF());
}

void clsWKCommandProcess::querySpeed()
{
    writeToClient(sngWK6500::Instance()->getGpibSpeed());
}

void clsWKCommandProcess::queryBiasFitExit()
{
    writeToClient("1");
}

void clsWKCommandProcess::queryBiasUnit()
{
    writeToClient("4");
}

void clsWKCommandProcess::querySysBias()
{
   writeToClient("BIAS EXT");
}

void clsWKCommandProcess::setItem1(const QString &value)
{
    sngWK6500::Instance()->setGpibItem1(value);
}

void clsWKCommandProcess::setItem2(const QString &value)
{
    sngWK6500::Instance()->setGpibItem2(value);
}

void clsWKCommandProcess::setEqucct(const QString &value)
{
    sngWK6500::Instance()->setGpibEqucct(value);
}

void clsWKCommandProcess::setRange(const QString &value)
{
    sngWK6500::Instance()->setGpibRange(value);
}

void clsWKCommandProcess::setFrequency(const QString &value)
{
    sngWK6500::Instance()->setGpibFrequency(value);
}

void clsWKCommandProcess::setLevelValue(const QString &value)
{
    sngWK6500::Instance()->setGpibLevelValue(value);
}

void clsWKCommandProcess::setBiasValue(const QString &value)
{
    sngWK6500::Instance()->setGpibBiasValue(value);
}

void clsWKCommandProcess::setBiasType(const QString &value)
{
    sngWK6500::Instance()->setGpibBiasType(value);
}

void clsWKCommandProcess::setBiasStatus(const QString &value)
{
    sngWK6500::Instance()->setGpibBiasONOFF(value);
}

void clsWKCommandProcess::setSpeed(const QString &value)
{
    sngWK6500::Instance()->setGpibSpeed(value);
}

void clsWKCommandProcess::setFastGpib(const QString &value)
{
   sngWK6500::Instance()->setGpibFastGpib(value);
}

