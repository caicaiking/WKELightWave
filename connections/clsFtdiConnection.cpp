#include "clsFtdiConnection.h"
#include <QTime>
#include "clsTestClass.h"
#include "clsSelectFtdiChip.h"
#include <QMessageBox>
#include "publicUtility.h"
#include <QDebug>
clsFtdiConnection::clsFtdiConnection(QObject *parent) : QObject(parent)
{
    isInit = false;
    this->instrument = "WKEC";

    connect(this, &clsFtdiConnection::recievFinished,this,&clsFtdiConnection::setResString);
}
void clsFtdiConnection::setResString(QString value)
{
   this->retData = value;
}

clsFtdiConnection::~clsFtdiConnection()
{
    this->closeDevice();
}

void clsFtdiConnection::setConnectionType(QString /*cnntType*/)
{
}

void clsFtdiConnection::setAddress(QString address)
{
    this->strAddress = address;
}

bool clsFtdiConnection::setupConnection()
{
    if(false == getDeviceList())
    {
        isInit = false;
        return false;
    }

    serialPort = new QSerialPort(this);
    serialPort->setPortName(portName);

    if(!serialPort->open(QIODevice::ReadWrite))
    {
        serialPort->close();
        isInit = false;
        return false;
    }
    serialPort->setBaudRate(QSerialPort::Baud57600);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setStopBits(QSerialPort::OneStop);

    isInit = true;

    connect(serialPort,&QSerialPort::readyRead,this,&clsFtdiConnection::readCom);

    QTime t1 = QTime::currentTime();
    QString idn = sendCommand("1");
    qDebug()<< idn;
    qDebug()<<"Read id need time: " << t1.msecsTo(QTime::currentTime())<<"ms";
    if(idn.contains("Scan"))
        isInit = true;
    else
    {
        isInit = false;
        serialPort->close();
        QMessageBox::critical(0, tr("WKE控制箱连线错误"), tr("请仔细检查串口连线，或者重新插拔！"),QMessageBox::Ok);
        return false;
    }
    return true;
}

QString clsFtdiConnection::sendCommand(QString command)
{
    if(!isInit)
        return "";

    if(isInit)
        emit commandMsg(command);

    readData.clear();
    retData.clear();
    QTime startTime= QTime::currentTime();
    QString cmd = command + "\r";
    serialPort->write(cmd.toUtf8(), cmd.length());
    serialPort->waitForBytesWritten(1000);
    publicUtility::sleepMs(20);

    int i=0;
    forever
    {
        if(!retData.isEmpty())
            break;

        if(i>1000)
            break;
        publicUtility::sleepMs(3);
        i++;
    }
    qDebug()<< "Send command time:\t" << startTime.msecsTo(QTime::currentTime())<< "ms";

    return retData;
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

void clsFtdiConnection::readCom()
{
    publicUtility::sleepMs(3);
    readData += serialPort->readAll();

    if(readData.contains("\r"))
    {
        emit recievFinished(readData);

        QStringList rec = readData.split("\r",QString::SkipEmptyParts);
        if(rec.length()==0)
            return;
        if(rec.last().toInt()==11)
        {
            emit trigSingal();
            qDebug()<<"Trig";
            readData.clear();
        }

        if(rec.last().toInt() ==12)
        {
            emit resetSignal();
            qDebug()<<"Reset";
            readData.clear();
        }
        return;
    }
}

bool clsFtdiConnection::closeDevice()
{
    if(this->isInit)
    {
        serialPort->close();
        return true;
    }
    return true;
}

QString clsFtdiConnection::readSetings()
{
    clsSettings settings;
    QString strNode = "SerialPort/";
    QString tmpString;
    settings.readSetting(strNode + instrument, tmpString);
    if(tmpString.isEmpty())
        return "NotSet";
    return tmpString;

}

void clsFtdiConnection::writeSettings(QString sn)
{
    clsSettings settings;
    QString strNode = "SerialPort/";
    settings.writeSetting(strNode + instrument, sn);
}


bool clsFtdiConnection::getDeviceList()
{
    QList< QSerialPortInfo > info = QSerialPortInfo::availablePorts();

    QStringList list;
    foreach (QSerialPortInfo tmp, info) {
        list.append(tmp.portName());
    }

    QString lastPortName = readSetings();
    if(list.length() <=0)
        return false;

    if(list.contains(lastPortName))
        portName = lastPortName;
    else
    {
        bool ok;
        int index = clsSelectFtdiChip::selectIndex(list,&ok, tr("WKE 控制箱"));

        if(ok)
            portName = list.at(index);
        else
            return false;
    }
    writeSettings(portName);
    return true;

}
