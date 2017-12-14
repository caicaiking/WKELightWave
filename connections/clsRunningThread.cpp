#include "clsRunningThread.h"
#include <QTime>
#include <QApplication>
#include <QDebug>
#include "clsFtdiOperation.h"
#include <QTime>
#include "publicUtility.h"
#include <QDebug>

void clsRunningThread::run()
{
    qDebug()<<strName<< " thread running";
    blStop = false;
    while(!blStop)
    {
        if(captrueSignal(bit))
        {
            emit getSignal();
            qDebug()<< "Get Trig signal";
            blStop = true;
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
    //QTime t1 = QTime::currentTime();
    QString statusString = clsConnectSWBox::Ins()->getReadString();
    //qDebug()<<statusString;
    //qDebug()<< "Get status need time: " << t1.msecsTo(QTime::currentTime()) <<"ms";

    int  recValue = statusString.toInt();

    int xAnd = 1<< bit;

    int retValue = (recValue & xAnd)>>bit;

    return QString::number(retValue);


}
