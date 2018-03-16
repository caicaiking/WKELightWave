#include "clsConnectToServer.h"
#include <QDebug>
#include "publicUtility.h"
clsConnectToServer::clsConnectToServer(QObject *parent):QTcpSocket(parent)
{
    isInit = false;
    connect(this,SIGNAL(readyRead()),this, SLOT(readPort()));
}

void clsConnectToServer::setIpAddressAndPort(QString ip, int port)
{
    this->ip = ip;
    this->port = port;
}

void clsConnectToServer::startConnect()
{
    this->connectToHost(ip, port, QIODevice::ReadWrite);
    if(this->waitForConnected(5000))
    {
        isInit = true;
        emit lanRemote(true);
    }
    else
    {
       emit lanRemote(false);
        isInit = false;
    }

}

void clsConnectToServer::readPort()
{
    QString strRead = this->readAll();
    if(strRead =="1")
        emit trigSignal();
    if(strRead == "0")
        writeRes(QString("WAYNE KERR, LightWave, Lan Remote, %1").arg(publicUtility::getVersion()));

}

void clsConnectToServer::writeRes(QString res)
{
    this->write(res.toStdString().c_str()) ;
    this->flush();
}

bool clsConnectToServer::getIsInit() const
{
    return isInit;
}
