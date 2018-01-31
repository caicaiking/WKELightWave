#include "clsFtdiOperation.h"
#include "clsTestClass.h"
#include "clsFtdiConnection.h"
#include <QApplication>
#include <QTime>
#include <QDebug>
#include "publicUtility.h"
clsFtdiOperation::clsFtdiOperation(QObject *parent) : QObject(parent)
{

    connect(sngFtdiCnnt::Ins(),&clsFtdiConnection::trigSingal,this,&clsFtdiOperation::trigSignal);
    connect(sngFtdiCnnt::Ins(),&clsFtdiConnection::resetSignal,this,&clsFtdiOperation::resetSignal);

    portValue =0;
    relayStatus = false;
}

void clsFtdiOperation::setBusy(bool value)
{

    int mask;
    if(value)
    {
        qDebug() << BUSYCMMD;
        mask = 0x01<< 0;
        portValue |= mask;
    }
    else
    {
        qDebug() << IDELCMMD;
        mask = 0xFF-(1<<0);
        portValue &= mask;
    }
    emit busyStatusChanged(value);
    sngFtdiCnnt::Ins()->sendCommand("3,"+ QString::number(portValue));
}

void clsFtdiOperation::setLcrPassFail(bool value)
{

    int mask;
    if(value)
    {
        qDebug() << LCRPASSCMMD;
        mask = 0x01<< 1;
        portValue |= mask;
    }
    else
    {
        qDebug() << LCRFAILCMMD;
        mask = 0xFF-(1<<1);
        portValue &= mask;
    }
    emit lcrStatusChanged(value);
    sngFtdiCnnt::Ins()->sendCommand("3,"+ QString::number(portValue));
}

void clsFtdiOperation::setHvPassFail(bool value)
{

    int mask;
    if(value)
    {
        qDebug() << HVFAILCMMD;
        mask = 0x01<< 2;
        portValue |= mask;
    }
    else
    {
        qDebug() << HVFAILCMMD;
        mask = 0xFF-(1<<2);
        portValue &= mask;
    }
    emit hvStatusChanged(value);
    sngFtdiCnnt::Ins()->sendCommand("3,"+ QString::number(portValue));

}

void clsFtdiOperation::setIo(int value)
{

    qDebug() << "\tFtdi-->Set IO Command "<<value;
    sngFtdiCnnt::Ins()->sendCommand("3,"+ QString::number(value));
    this->portValue = value;
}

void clsFtdiOperation::setChannel(QPoint channel, QString type)
{
    QString channelStr = QString("%1-%2").arg(channel.x()).arg(channel.y());


    emit channelChanged(channelStr);

    QString cmmd;
    if(type == "WK6500")
        cmmd = QString("7,%1,%2,0,0").arg(channel.x()).arg(channel.y());
    else
        cmmd = QString("7,0,0,%1,%2").arg(channel.x()).arg(channel.y());

    qDebug() << SETCHANNEL <<channelStr;

    sngFtdiCnnt::Ins()->sendCommand(cmmd);

}

void clsFtdiOperation::setRelay(bool value)
{

    if(value)
    {
        qDebug()<< SETRELAY;
        sngFtdiCnnt::Ins()->sendCommand("13,2");
    }
    else
    {
        qDebug()<< OPENRELAY;
        sngFtdiCnnt::Ins()->sendCommand("13,0");
    }
    relayStatus = value;
}

void clsFtdiOperation::sleepMs(int svalue)
{
    publicUtility::sleepMs(svalue);
}
