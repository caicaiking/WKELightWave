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
        sngFtdiCnnt::Ins()->sendCommand(BUSYCMMD, false);
    }
    else
    {
        qDebug() << IDELCMMD;
        sngFtdiCnnt::Ins()->sendCommand(IDELCMMD, false);
    }
}

void clsFtdiOperation::setLcrPassFail(bool value)
{
    emit lcrStatusChanged(value);

    if(value)
    {
        qDebug()<< LCRPASSCMMD;
        sngFtdiCnnt::Ins()->sendCommand(LCRPASSCMMD,false);
    }
    else
    {
        qDebug()<<LCRFAILCMMD;
        sngFtdiCnnt::Ins()->sendCommand(LCRFAILCMMD,false);
    }
}

void clsFtdiOperation::setHvPassFail(bool value)
{
    emit hvStatusChanged(value);

    if(value)
    {
        qDebug()<<HVPASSCMMD;
        sngFtdiCnnt::Ins()->sendCommand(HVPASSCMMD,false);
    }
    else
    {
        qDebug()<<HVFAILCMMD;
        sngFtdiCnnt::Ins()->sendCommand(HVFAILCMMD,false);
    }

}

void clsFtdiOperation::setChannel(int channel)
{
    if(this->channel == channel)
        return;

    emit channelChanged(channel);

    QString cmmd = SETCHANNEL + QString::number(channel);
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
        sngFtdiCnnt::Ins()->sendCommand(SETRELAY,false);
    }
    else
    {
        qDebug()<< OPENRELAY;
        sngFtdiCnnt::Ins()->sendCommand(OPENRELAY,false);
    }
    relayStatus = value;
}

QString clsFtdiOperation::getValue()
{
    // qDebug()<< QUERYCMMD;
    return sngFtdiCnnt::Ins()->sendCommand(QUERYCMMD, true);
}

void clsFtdiOperation::updataFTDIdata()
{
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
