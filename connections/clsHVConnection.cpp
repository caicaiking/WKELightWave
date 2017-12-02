#include "clsHVConnection.h"
#include <QDebug>

clsHVConnection::clsHVConnection(QObject *parent) : QObject(parent)
{
    isInit = true;

}

void clsHVConnection::setConnectionType(QString cnntType)
{
    cnntType = "";
}

void clsHVConnection::setAddress(QString address)
{
    this->strAddress = address;

}

bool clsHVConnection::setupConnection()
{
    isInit = true;

    if(isInit)
        emit showMessage(tr("高压设备已经连接"));

    return isInit;
}

QString clsHVConnection::sendCommand(QString command, bool hasReturn)
{
    if(!isInit)
    {
        qWarning()<<"HV connection not setup conrrectly!";
        emit showMessage("HV设备没有连接");
        return "";
    }

    command = "";

    if(hasReturn)
    {
        int number = getRandomNumber(1E5,20E3);
        return QString::number(number*10);
    }
    else
        return "0";

}

void clsHVConnection::disConnectInstrument()
{
    isInit = false;
}

bool clsHVConnection::hasInitSucess()
{
    return this->isInit;
}

double clsHVConnection::getRandomNumber(int max, int min)
{
   return (rand() % (max-min))+ min;
}
