#include "clsTcpIpThread.h"
#include <QApplication>
clsTcpIpThread::clsTcpIpThread(int Id, QObject *parent):
    QThread(parent)
{
    this->socketDescriptor = Id;
}

void clsTcpIpThread::run()
{
    this->socket = new QTcpSocket(this);
    qDebug()<<this->socketDescriptor<< " " "Starting thread";
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }

    connect(socket,SIGNAL(readyRead()),this,SLOT(readRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);

    qDebug()<< this->socketDescriptor << " Client connected";

    exec();
}

void clsTcpIpThread::readRead()
{
    QByteArray data = socket->readAll();
    if(data.length() <= 0)
        return ;

    QString tmpData = QString(data);
    tmpData = tmpData.remove("\r");
    tmpData = tmpData.remove("\n");
    emit getCommand(tmpData);
}

void clsTcpIpThread::disconnected()
{
    qDebug()<< socketDescriptor << " disconnected";
    socket->deleteLater();
    exit(0);
}

void clsTcpIpThread::write(QString str)
{
    socket->write(str.toStdString().c_str());
    socket->flush();
}

int clsTcpIpThread::getSocketDescriptor() const
{
    return socketDescriptor;
}
