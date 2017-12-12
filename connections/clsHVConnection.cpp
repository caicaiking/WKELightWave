#include "clsHVConnection.h"
#include "clsSettings.h"
#include "clsSelectFtdiChip.h"
#include <QDebug>

clsHVConnection::clsHVConnection(QObject *parent) : QObject(parent)
{
    isInit = false;
    timer = new QTimer(this);
    timer->setInterval(1000);
    this->instrument = "HVTTest";
    connect(timer,&QTimer::timeout,this,&clsHVConnection::timerProc);

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
    {
        isInit = false;
        return isInit;
    }

    QString sn = readSetings();
    int index =0;

    if(deviceInfo.contains(sn))
    {
        index = deviceInfo.indexOf(sn);
    }
    else
    {
        bool ok;
        index = clsSelectFtdiChip::selectIndex(deviceInfo, &ok);
        if(!ok)
        {
            isInit = false;
            return isInit;
        }
    }

    ftStatus = FT_Open(index,&devInfo[index].ftHandle);

    if(ftStatus == FT_OK)
    {
        ftHandle = devInfo[index].ftHandle;
        qDebug()<< "Open ftdi chip ok, descriptor: " << deviceInfo.at(index);
    }
    else
    {
        qWarning()<< "Can not open ftdi chip! " ;
        isInit = false;
        return false;
    }

    ftStatus = FT_SetBaudRate(ftHandle,FT_BAUD_19200); //设置波特率
    if(FT_OK != ftStatus)
    {
        qWarning()<< "Set baudrate error!";
        isInit = false;
        return false;
    }

    ftStatus = FT_SetDataCharacteristics(ftHandle,
                                         FT_BITS_8,
                                         FT_STOP_BITS_1,
                                         FT_PARITY_NONE);
    if(ftStatus != FT_OK)
    {
        qWarning()<<"Set data characterisetics error!";
        isInit = false;
        return false;
    }

    ftStatus = FT_SetFlowControl(ftHandle,
                                 FT_FLOW_NONE,
                                 NULL,
                                 NULL);
    if(ftStatus != FT_OK)
    {
        isInit = false;
        qWarning()<< "Set flow control error!";
    }

    isInit = true;
    qDebug()<< sendCommand("*IDN?", true);


    writeSettings(deviceInfo.at(index));

    if(isInit)
        emit showMessage(tr("高压设备已经连接"));

    return isInit;
}

QString clsHVConnection::sendCommand(QString command, bool hasReturn)
{
    if(!isInit)
    {
        qWarning()<<"HV connection not setup conrrectly!";
        emit showMessage("HV设备没有连接");
        return "";
    }

    DWORD noOfBytesWriten =0;
    QString cmmd = command;
    cmmd += QChar(10);
    ftStatus = FT_Write(ftHandle,
                        (LPVOID*)cmmd.toStdString().c_str(),
                        cmmd.length(),
                        &noOfBytesWriten);
    if(ftStatus != FT_OK)
    {
        qWarning()<<"Send command error "<< instrument;
        return "";
    }

    forceQuit = false;
    timer->start();

    DWORD     RxQueueBytes = 0;			// No Of Bytes in Receive  Queue
    DWORD     TxQueueBytes = 0;			// No Of Bytes in Transmit Queue
    DWORD     EventStatus  = 0;			// current state of	the event status

    char      RxBuffer[256];            // Buffer for received data
    DWORD     BytesReceived = 0;		// number of bytes read from the device(for FT_Read())


    Sleep(75);
    QString tmpRecieved;
REREAD:
    ftStatus = FT_GetStatus(ftHandle,
                            &RxQueueBytes,
                            &TxQueueBytes,
                            &EventStatus);
    qApp->processEvents();
    Sleep(3);
    if(RxQueueBytes>0)
    {
        ftStatus = FT_Read(ftHandle,
                           RxBuffer,
                           RxQueueBytes,
                           &BytesReceived);
        tmpRecieved += QString(RxBuffer);
        if(forceQuit)
        {
            qDebug()<< "Force quit, read time out";
            timer->stop();
            return "";
        }
        if(!(tmpRecieved.contains("\n") || tmpRecieved.contains(QChar(0x06))))
            goto REREAD;
    }
    else
    {
        if(forceQuit)
        {
            qDebug()<< "Force quit, read time out";
            timer->stop();
            return "";
        }

        goto REREAD;
    }

    int length = tmpRecieved.indexOf("\n");
    tmpRecieved = tmpRecieved.left(length);

    timer->stop();
    return tmpRecieved;




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
    ftStatus = FT_CreateDeviceInfoList(&numDevs);

    if(ftStatus != FT_OK)
        qDebug()<< "Faild to get FTDI device list";

    if(numDevs > 0)
    {
        devInfo = (FT_DEVICE_LIST_INFO_NODE *)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);

        ftStatus = FT_GetDeviceInfoList(devInfo,&numDevs);
        if(ftStatus == FT_OK)
        {
            deviceInfo.clear();
            for(int i =0; i< numDevs; i++)
            {
                deviceInfo.append(devInfo[i].SerialNumber);
            }
        }
        else
        {
            qDebug()<<"Failed to get device list";
            Sleep(1000);
            return false;
        }
        return true;
    }
    return false;

}

bool clsHVConnection::closeDevice()
{
    if(this->isInit)
    {
        ftStatus = FT_Close(ftHandle);

        if(ftStatus != FT_OK)
            return false;
        else
            return true;
    }

    return true;
}
