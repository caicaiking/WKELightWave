#include "clsADU200.h"
#include <QApplication>
#include <QTime>

clsADU200::clsADU200(QObject *parent) : QObject(parent)
{
    blStop=false;
    //initADU200();
}

clsADU200::~clsADU200()
{
    CloseAduDevice(hDevice);
}

bool clsADU200::initADU200()
{
    hDevice=OpenAduDevice(0);
    int i=(int)hDevice;
    if(i!=-1)
        isInit=true;
    else
        isInit= false;
    return isInit;
}

QString clsADU200::sendCommand(QString cmmd, bool hasReturn)
{
    char sBuffer[8];

    WriteAduDevice(hDevice, cmmd.toStdString().c_str(), 4, 0, 0);
    memset(sBuffer, 0, sizeof(sBuffer));
    if(!hasReturn)
        return "";

    ReadAduDevice(hDevice, sBuffer, 7, 0, 0);
    QString ret = sBuffer;
    return ret;
}

QString clsADU200::getInput(int port)
{
    QString cmmd = QString("RPA%1").arg(QString::number(port));
    QString status= sendCommand(cmmd,true);
    return status;
}

bool clsADU200::getInputSignal(int port)
{
    blStop=false;
    int status=getInput(port).toInt();
    if(status!=0)
    {
        while ((getInput(port))!="0" && (!blStop))
        {
            qApp->processEvents();
            sleepMs(10);
        }
    }
    if(blStop)
        return false;
    while((getInput(port)=="0")&&(!blStop))
    {
        qApp->processEvents();
        sleepMs(10);
    }
    if(blStop)
        return false;
    while((getInput(port)=="1")&&(!blStop))
    {
        qApp->processEvents();
        sleepMs(10);
    }
    if(blStop)
        return false;
    sleepMs(20);
    status=getInput(port).toInt();
    if(status==0)
        return true;
    else
        return false;
}

QString clsADU200::shortRelay(int port)
{
    QString cmmd=QString("SK%1").arg(QString::number(port));
    return sendCommand(cmmd,false);
}

QString clsADU200::openRelay(int port)
{
    QString cmmd=QString("RK%%1").arg(QString::number(port));
    return sendCommand(cmmd,false);
}

void clsADU200::setPass()
{
    shortRelay(1);
    openRelay(0);
}

void clsADU200::setFail()
{
    shortRelay(0);
    openRelay(1);
}

void clsADU200::setBDA()
{
    shortRelay(2);
}

void clsADU200::resetBDA()
{
    openRelay(2);
}

void clsADU200::stop()
{
    this->blStop=true;
}

void clsADU200::sleepMs(int t)
{
    QTime stopTime=QTime::currentTime().addMSecs(t);
    while(QTime::currentTime()<stopTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}
