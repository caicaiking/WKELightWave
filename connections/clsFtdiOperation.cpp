#include "clsFtdiOperation.h"
#include "clsTestClass.h"
#include "clsFtdiConnection.h"
#include <QApplication>
#include <QTime>
#include <QDebug>
#include "publicUtility.h"
clsFtdiOperation::clsFtdiOperation(QObject *parent) : QObject(parent)
{

    this->channel =99;
    blStop = false;
}

void clsFtdiOperation::setBusy(bool value)
{
    emit busyStatusChanged(value);

    if(value)
    {
        qDebug() << BUSYCMMD;
        sngFtdiCnnt::Ins()->sendCommand("4,6", false);
    }
    else
    {
        qDebug() << IDELCMMD;
        sngFtdiCnnt::Ins()->sendCommand("4,5", false);
    }
}

void clsFtdiOperation::setLcrPassFail(bool value)
{
    emit lcrStatusChanged(value);

    if(value)
    {
        qDebug()<< LCRPASSCMMD;
        sngFtdiCnnt::Ins()->sendCommand("4,10",false);
    }
    else
    {
        qDebug()<<LCRFAILCMMD;
        sngFtdiCnnt::Ins()->sendCommand("4,11",false);
    }
}

void clsFtdiOperation::setHvPassFail(bool value)
{
    emit hvStatusChanged(value);

    if(value)
    {
        qDebug()<<HVPASSCMMD;
        sngFtdiCnnt::Ins()->sendCommand("4,10",false);
    }
    else
    {
        qDebug()<<HVFAILCMMD;
        sngFtdiCnnt::Ins()->sendCommand("4,9",false);
    }

}

void clsFtdiOperation::setChannel(int channel)
{
    if(this->channel == channel)
        return;

    emit channelChanged(channel);

    QString cmmd = "4," + QString::number(channel);
    qDebug() << SETCHANNEL << QString::number(channel);

    sngFtdiCnnt::Ins()->sendCommand( cmmd,false);

    this->channel = channel;
}

void clsFtdiOperation::setRelay(bool value)
{
    if(value == relayStatus)
        return;

    if(value)
    {
        qDebug()<< SETRELAY;
        sngFtdiCnnt::Ins()->sendCommand("4,8",false);
    }
    else
    {
        qDebug()<< OPENRELAY;
        sngFtdiCnnt::Ins()->sendCommand("4,7",false);
    }
    relayStatus = value;
}

void clsFtdiOperation::turnOffAllLight()
{

}

void clsFtdiOperation::setOnlyOneOrangeLEDON(int)
{

}

QString clsFtdiOperation::getValue()
{
    // qDebug()<< QUERYCMMD;
    return sngFtdiCnnt::Ins()->sendCommand("12", true);
}

void clsFtdiOperation::updataFTDIdata()
{
    blStop = false;
    while(!blStop)
    {
        QString  retValue = getValue();
        setReadString(retValue);
        qApp->processEvents();
        sleepMs(1);
    }
}

void clsFtdiOperation::stop()
{
    blStop = true;
}

QString clsFtdiOperation::getReadString() const
{
    return readString;
}

void clsFtdiOperation::setReadString(const QString &value)
{
    mutex.lock();
    const bool isLocked = locker.tryLockForWrite();
    if(isLocked)
    {
        readString = value;
        // qDebug()<< value;
        locker.unlock();
    }
    mutex.unlock();
}

void clsFtdiOperation::sleepMs(int svalue)
{
    publicUtility::sleepMs(svalue);
}
