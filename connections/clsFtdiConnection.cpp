#include "clsFtdiConnection.h"
#include <QTime>
#include "clsTestClass.h"
#include "clsSelectFtdiChip.h"
#include <QMessageBox>
#include "publicUtility.h"
#include <QDebug>
#include "clsRunningThread.h"
clsFtdiConnection::clsFtdiConnection(QObject *parent) : QObject(parent)
{
    isInit = false;
    this->instrument = "WKEC";

    this->moveToThread(sngTrigThread::Ins()->thread());
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

    serialPort = new QextSerialPort(QextSerialPort::EventDriven, this->parent());
    serialPort->setPortName(portName);


    serialPort->setBaudRate(BAUD9600);
    serialPort->setParity(PAR_NONE);
    serialPort->setDataBits(DATA_8);
    serialPort->setStopBits(STOP_1);
    serialPort->setFlowControl(FLOW_OFF);

    if(!serialPort->open(QIODevice::ReadWrite))
    {
        serialPort->close();
        isInit = false;
        return false;
    }
    connect(serialPort, &QextSerialPort::readyRead,this,&clsFtdiConnection::readCom);
    isInit = true;
    QTime t1 = QTime::currentTime();
    QString idn = sendCommand("1", true);
    qDebug()<< idn;
    qDebug()<<"Read id need time: " << t1.msecsTo(QTime::currentTime())<<"ms";
    if(idn.contains("Scan"))
        isInit = true;
    else
    {
        isInit = false;
        QMessageBox::critical(0, tr("WKE控制箱连线错误"), tr("请仔细检查串口连线，或者重新插拔！"),QMessageBox::Ok);
        return false;
    }
    return true;
}

QString clsFtdiConnection::sendCommand(QString command, bool hasReturn)
{
    if(!isInit)
        return "";

    if(isInit)
        emit commandMsg(command);

    readData.clear();
    disconnect(serialPort, &QextSerialPort::readyRead,this,&clsFtdiConnection::readCom);
    QString cmd = command + "\r";
    serialPort->write(cmd.toUtf8(), cmd.length());
    serialPort->waitForBytesWritten(1000);

    if(!hasReturn)
        return "";

    connect(serialPort, &QextSerialPort::readyRead,this,&clsFtdiConnection::readCom);
    int i=0;
    forever
    {
        if(!readData.isEmpty())
            break;

        if(i>1000)
            break;
        publicUtility::sleepMs(3);
        i++;
    }
    return readData;
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
    publicUtility::sleepMs(45);
REREAD:
    publicUtility::sleepMs(3);
    readData += serialPort->readAll();

    if(readData.contains("\r"))
        emit recievFinished(readData);
    else
        goto REREAD;

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
