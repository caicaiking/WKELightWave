#include "clsHVConnection.h"
#include "clsSettings.h"
#include <QMessageBox>
#include "clsSelectFtdiChip.h"
#include "publicUtility.h"
#include <QDebug>

clsHVConnection::clsHVConnection(QObject *parent) : QObject(parent)
{
    isInit = false;
    timer = new QTimer(this);
    timer->setInterval(1000);
    this->instrument = "HVTTest";
    connect(timer,&QTimer::timeout,this,&clsHVConnection::timerProc);

}

clsHVConnection::~clsHVConnection()
{
    this->closeDevice();
}

void clsHVConnection::setConnectionType(QString cnntType)
{
    cnntType = "";
}

void clsHVConnection::setAddress(QString address)
{
    this->strAddress = address;
}

bool clsHVConnection::setupConnection()
{
    if(false == getDeviceList())
        return false;

    serialPort = new QSerialPort(this);
    serialPort->setPortName(portName);
    serialPort->setBaudRate(QSerialPort::Baud19200);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setStopBits(QSerialPort::OneStop);
    if(!serialPort->open(QIODevice::ReadWrite))
    {
        serialPort->close();
        isInit = false;
        return false;
    }

    isInit = true;

    QString idn = sendCommand("*IDN?", true);
    qDebug()<< idn;
    if(idn.contains("ASSOCIATED"))
        isInit = true;
    else
    {
        QMessageBox::critical(0, tr("硬件连线错误"), tr("请仔细检查串口连线，或者重新插拔！"),QMessageBox::Ok);
        return false;
    }

    return true;
}

QString clsHVConnection::sendCommand(QString command, bool hasReturn)
{
    if(isInit == false)
    {
        return "";
    }

    QString commd = command + "\n";

    serialPort->write(commd.toStdString().c_str(), commd.length());

    serialPort->waitForBytesWritten(1000);

    bool hasDataBack= serialPort->waitForReadyRead(3000);

    timer->start();

    QString strRes;
    if(hasDataBack)
    {
        publicUtility::sleepMs(80);
REREAD:
        char buffer[200];
        publicUtility::sleepMs(3);
        int readBack = serialPort->read(buffer, 200);
        qDebug()<<"Read from HV testor" <<readBack;
        if(forceQuit)
            goto END;

        strRes += QString(buffer);
        if(strRes.contains("\n") || strRes.contains(QChar(0x06)) || strRes.contains(QChar(0x15)))
            goto END;
        else
            goto REREAD;

    }

END:
    timer->stop();
    if(hasReturn)
    {
        int index = strRes.indexOf("\n");
        return strRes.left(index);
    }
    return strRes;
}

void clsHVConnection::disConnectInstrument()
{
    closeDevice();
    isInit = false;
}

bool clsHVConnection::hasInitSucess()
{
    return this->isInit;
}

double clsHVConnection::getRandomNumber(int max, int min)
{
    return (rand() % (max-min))+ min;
}

QString clsHVConnection::readSetings()
{
    clsSettings settings;
    QString strNode = "SerialPort/";
    QString tmpString;
    settings.readSetting(strNode + instrument, tmpString);
    if(tmpString.isEmpty())
        return "NotSet";
    return tmpString;

}

QString clsHVConnection::writeSettings(QString sn)
{
    clsSettings settings;
    QString strNode = "SerialPort/";
    settings.writeSetting(strNode + instrument, sn);
}

void clsHVConnection::timerProc()
{
    forceQuit = true;
}

bool clsHVConnection::getDeviceList()
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
        int index = clsSelectFtdiChip::selectIndex(list,&ok);

        if(ok)
            portName = list.at(index);
        else
            return false;
    }
    writeSettings(portName);
    return true;
}

bool clsHVConnection::closeDevice()
{
    if(this->isInit)
    {
        serialPort->close();
        return true;
    }
    return true;
}
