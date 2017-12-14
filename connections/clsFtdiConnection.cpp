#include "clsFtdiConnection.h"
#include "clsTestClass.h"
#include "clsSelectFtdiChip.h"
#include "publicUtility.h"
#include <QDebug>
clsFtdiConnection::clsFtdiConnection(QObject *parent) : QObject(parent)
{
    isInit = false;
    this->instrument = "WKEC";

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

    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setStopBits(QSerialPort::OneStop);

    isInit = true;
    return true;

}

QString clsFtdiConnection::sendCommand(QString command, bool hasReturn)
{
    if(!isInit)
        return "0";

    QString strRes;
    mutex.lock();
    const bool isLocked = lock.tryLockForWrite();
    if(isLocked)
    {
        //在此处插入代码
        if(isInit)
            emit commandMsg(command);

        QString commd = command + "\r";
        serialPort->write(commd.toStdString().c_str(), commd.length());
        serialPort->waitForBytesWritten(1000);

        bool hasDataBack = serialPort->waitForReadyRead(3000);

        if(hasDataBack)
        {
            publicUtility::sleepMs(40);
REREAD:
            char buffer[200];
            publicUtility::sleepMs(3);
            int readBack = serialPort->read(buffer,200);
            qDebug()<<"Read from WKEC: " <<readBack<< " \tDATA: "<< QString(buffer);

            strRes += QString(buffer);
            if(strRes.contains("\r"))
                goto END;
            else
                goto REREAD;

        }
END:
        //在此处插入代码结束
        lock.unlock();
    }
    mutex.unlock();

    if(hasReturn)
    {
        int index = strRes.indexOf("\r");
        return strRes.left(index);
        //  return sngTest::Ins()->getFtdiReadString(); //For demo test use.
    }
    else
        return strRes;
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

void clsFtdiConnection::timerProc()
{
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
