#include "clsHVConnection.h"
#include "clsSettings.h"
#include <QMessageBox>
#include "clsSelectFtdiChip.h"
#include "publicUtility.h"
#include <QDebug>

clsHVConnection::clsHVConnection(QObject *parent) : QObject(parent)
{
    isInit = false;
    this->instrument = "HVTTest";

}

clsHVConnection::~clsHVConnection()
{
    this->closeDevice();
}

void clsHVConnection::setConnectionType(QString /*cnntType*/)
{
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
    if(!serialPort->open(QIODevice::ReadWrite))
    {
        serialPort->close();
        isInit = false;
        return false;
    }

    serialPort->setBaudRate(QSerialPort::Baud19200);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setStopBits(QSerialPort::OneStop);

    isInit = true;

    QString idn = sendCommand("*IDN?", true);
    qDebug()<< idn;
    if(idn.contains("ASSOCIATED"))
        isInit = true;
    else
    {
        isInit = false;
        serialPort->close();
        QMessageBox::critical(0, tr("高压机连线错误"), tr("请仔细检查串口连线，或者重新插拔！"),QMessageBox::Ok);
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

    serialPort->write(commd.toUtf8());

    serialPort->waitForBytesWritten(1000);
    bool hasDataBack= serialPort->waitForReadyRead(3000);

    QByteArray requestData;
    if(hasDataBack)
    {
        requestData = serialPort->readAll();
        while(serialPort->waitForReadyRead(100))
        {
            requestData += serialPort->readAll();
        }
    }

    QString strRes = QString(requestData);
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

void clsHVConnection::writeSettings(QString sn)
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
        int index = clsSelectFtdiChip::selectIndex(list,&ok, tr("高压机"));

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
