#include "clsSignalThread.h"
#include <QApplication>
#include <QDebug>
clsSignalThread::clsSignalThread(QObject *parent) :
    QThread(parent)
{
    isStop =true;
}

clsSignalThread::~clsSignalThread()
{
    this->quit();
    this->wait();
}

void clsSignalThread::stop()
{
    isStop =true;
}

void clsSignalThread::setPass()
{
}

void clsSignalThread::setFail()
{
}

void clsSignalThread::setBusy()
{
}

void clsSignalThread::resetBusy()
{
}

void clsSignalThread::emitBDA()
{
}

void clsSignalThread::run()
{
}
