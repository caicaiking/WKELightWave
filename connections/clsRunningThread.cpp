#include "clsRunningThread.h"
#include <QApplication>
#include <QDebug>
#include "clsFtdiOperation.h"
#include <QTime>
#include "publicUtility.h"
void clsRunningThread::run()
{
    qDebug()<<strName<< " thread running";


    blStop = false;

    while(!blStop)
    {
        if(captrueSignal(bit))
        {
            emit getSignal();
        }
        qApp->processEvents();
        sleepMs(5);
    }

}

void clsRunningThread::setName(QString name)
{
    this->strName = name;
}

bool clsRunningThread::captrueSignal(int bit)
{
    blStop=false;

    int status = getInput(bit).toInt();
    if(status !=0)
    {
        while((getInput(bit)!="0") && (!blStop))
        {
            qApp->processEvents();
            sleepMs(1);
        }
        //   qDebug()<<"1";
    }
    // qDebug()<<"11";

    if(blStop)
        return false;

    //0->1
    while((getInput(bit)=="0") && (!blStop))
    {
        qApp->processEvents();
        sleepMs(1);
    }
    if(blStop)
        return false;
    //1->0
    while((getInput(bit)=="1") && (!blStop))
    {
        qApp->processEvents();
        sleepMs(1);
    }

    if(blStop)
        return false;
    // qDebug()<<"2";
    sleepMs(1);
    status=getInput(bit).toInt();

    if(status==0)
        return true;
    else
        return false;
}

void clsRunningThread::setCaptureBit(int bit)
{
   this->bit = bit;
}

void clsRunningThread::stop()
{
    blStop = true;
    qApp->processEvents();
}

void clsRunningThread::sleepMs(int svalue)
{
   publicUtility::sleepMs(svalue);
}

QString clsRunningThread::getInput(int bit)
{
    QString statusString = clsConnectSWBox::Ins()->getReadString();

    if(statusString.length()>bit)
        return QString(statusString.at(bit));
    else
        return "0";
}
