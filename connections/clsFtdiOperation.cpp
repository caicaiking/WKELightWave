#include "clsFtdiOperation.h"
#include "clsTestClass.h"
#include "clsFtdiConnection.h"
#include <QApplication>
#include <QTime>
#include <QDebug>
#include "publicUtility.h"
clsFtdiOperation::clsFtdiOperation(QObject *parent) : QObject(parent)
{

    blStop = false;
}

void clsFtdiOperation::setBusy(bool value)
{
    emit busyStatusChanged(value);

    if(value)
        sngFtdiCnnt::Ins()->sendCommand(BUSYCMMD, false);
    else
        sngFtdiCnnt::Ins()->sendCommand(IDELCMMD, false);
}

void clsFtdiOperation::setLcrPassFail(bool value)
{
    emit lcrStatusChanged(value);

    if(value)
        sngFtdiCnnt::Ins()->sendCommand(LCRPASSCMMD,false);
    else
        sngFtdiCnnt::Ins()->sendCommand(LCRFAILCMMD,false);
}

void clsFtdiOperation::setHvPassFail(bool value)
{
    emit hvStatusChanged(value);

    if(value)
        sngFtdiCnnt::Ins()->sendCommand(HVPASSCMMD,false);
    else
        sngFtdiCnnt::Ins()->sendCommand(HVFAILCMMD,false);


}

void clsFtdiOperation::setChannel(int channel)
{
    emit channelChanged(channel);

    sngFtdiCnnt::Ins()->sendCommand(QString(SETCHANNEL) + QString::number(channel),false);
}

QString clsFtdiOperation::getValue()
{
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
