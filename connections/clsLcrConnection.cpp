#include "clsLcrConnection.h"
#include "QDebug"

clsLcrConnection::clsLcrConnection(QObject *parent) : QObject(parent)
{
    cnnt =nullptr;
    isInit = false;
}

void clsLcrConnection::setConnectionType(QString cnntType)
{
    this->connectionType = cnntType;
}

void clsLcrConnection::setAddress(QString address)
{
    this->strAddress = address;
}

bool clsLcrConnection::setupConnection()
{
    if(isInit)
        return true;

    cnnt = connectionFactory::getConnection(this->connectionType);
    cnnt->setAddress(this->strAddress);

    this->isInit = cnnt->init();
    if(isInit)
        emit showMessage("LCR设备已连接");
    return isInit;
}

QString clsLcrConnection::sendCommand(QString command, bool hasReturn)
{
    if(isInit)
        return cnnt->sendCommand(command,hasReturn);
    else
        emit showMessage("LCR设备没有连接");
        qDebug()<<"The connection does't setup conrrectly!";
        return "";

}

void clsLcrConnection::disConnectInstrument()
{
    if(isInit)
        cnnt->disConnect();
}

bool clsLcrConnection::hasInitSucess()
{
    return isInit;
}
