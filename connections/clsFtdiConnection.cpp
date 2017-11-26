#include "clsFtdiConnection.h"

clsFtdiConnection::clsFtdiConnection(QObject *parent) : QObject(parent)
{
    isInit = false;
}

void clsFtdiConnection::setAddress(QString address)
{
    this->strAddress = address;
}

bool clsFtdiConnection::setupConnection()
{
    isInit = true;
    if(isInit)
        emit showMessage("WKE Control Box已连接");
    return isInit;
}

QString clsFtdiConnection::sendCommand(QString command, bool hasReturn)
{
    if(isInit)
        emit switchChannel(command);

    if(hasReturn)
        return "1";
    else
        return "0";
}

void clsFtdiConnection::disConnectInstrument()
{
    if(isInit)
        isInit = false;
}

bool clsFtdiConnection::hasInitSucess()
{
    return isInit;
}
