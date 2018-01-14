#include "clsWKServer.h"
#include "clsTcpIpThread.h"
#include <QDebug>
#include "clsWKCommandProcess.h"
#include <QApplication>
clsWKServer::clsWKServer(QObject *parent) :QTcpServer(parent)
{
}

void clsWKServer::startServer()
{
    if(!this->listen(QHostAddress::Any,2018))
    {
        qDebug()<< "Could not start server";
    }
    else
    {
        qDebug()<< "listening....";
    }
}

void clsWKServer::stopServer()
{
    QMapIterator <int, clsTcpIpThread * > it (pool);

    while(it.hasNext())
    {
        it.next().value()->exit(0);
    }
}

clsWKServer::~clsWKServer()
{
    stopServer();
}

void clsWKServer::incomingConnection(int socketDescriptor)
{
    qDebug()<< socketDescriptor << " comming..." ;

    if(pool.size() > 0)
    {
        qDebug()<<"Already has connected, refuse other connection!";
        return ;
    }
    clsTcpIpThread * thread  = new clsTcpIpThread(socketDescriptor, this);
    qDebug()<< pool.size();
    pool.insert(socketDescriptor, thread);
    emit lanRemote(true);
    //建立接收命令 -> 处理命令的程序中
    connect(thread,SIGNAL(getCommand(QString)),sngWkCommandProcess::Ins(),SLOT(setGpibCommand(QString)));
    //处理命令程序 写入程序的内容 -> 线程中写入
    connect(sngWkCommandProcess::Ins(),SIGNAL(writeToClient(QString)),thread,SLOT(write(QString)));

    connect(thread,&clsTcpIpThread::destroyed,[=]{

        int id = thread->getSocketDescriptor();
        pool.remove(id);

    });

    connect (thread,SIGNAL(finished()),thread,SLOT(deleteLater()));

    connect(thread,&clsTcpIpThread::finished,[=]()
    {
        qDebug()<< socketDescriptor << " Lan remote off";
        emit lanRemote(false);
    });

    thread->start();
}
