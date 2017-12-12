#include "clsFT232.h"
#include <QDebug>
#include "clsSettings.h"
#include "clsSelectFtdiChip.h"
clsFT232::clsFT232(QObject *parent): QObject(parent)
{
    isInit = false;

    timer = new QTimer(this);
    timer->setInterval(1000);

}

QStringList clsFT232::getOutputs() const
{
    return outputs;
}

QString clsFT232::sendCommand(QString cmmd, bool hasReturn)
{
    if(!isInit)
    {
        qWarning()<<"FTDI not init, "<< this->instrument;
        return "";
    }

    DWORD noOfBytesWriten =0;
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

    if(!hasReturn)
        return "";

    forceQuit = false;
    timer->start();

    HANDLE winHandle;
    DWORD     dwEventMask;              // Event Mask for setting conditions for triggering the event
    DWORD     RxQueueBytes = 0;			// No Of Bytes in Receive  Queue
    DWORD     TxQueueBytes = 0;			// No Of Bytes in Transmit Queue
    DWORD     EventStatus  = 0;			// current state of	the event status

    char      RxBuffer[256];            // Buffer for received data
    DWORD     BytesReceived = 0;		// number of bytes read from the device(for FT_Read())

    /* winHandle = CreateEventA(NULL,FALSE,FALSE,(LPCSTR)("FT232Event"));

    if(winHandle == INVALID_HANDLE_VALUE)
    {
        qWarning()<< "Error in creat event";
        return "";
    }

    dwEventMask = FT_EVENT_RXCHAR;

    ftStatus = FT_SetEventNotification(ftHandle, dwEventMask,winHandle);
    qApp->processEvents();
    if(ftStatus != FT_OK)
    {
        qWarning()<<"Set Event notification error!";
    }

    DWORD ret= WaitForSingleObject(winHandle,5000);

    //  Sleep(40);

    if(ret != WAIT_OBJECT_0)
    {
        qWarning()<< "Wait for read time out";
        return "";
    }*/

    Sleep(35);
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
        if(!tmpRecieved.contains("\n"))
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

void clsFT232::setInstrument(const QString &value)
{
    instrument = value;
}

QString clsFT232::readSettings()
{
    clsSettings settings;
    QString strNode = "SerialPort/";
    QString tmpString;
    settings.readSetting(strNode + instrument, tmpString);
    if(tmpString.isEmpty())
        return "NotSet";
    return tmpString;
}

void clsFT232::writeSettings(QString sn)
{
    clsSettings settings;
    QString strNode = "SerialPort/";
    settings.writeSetting(strNode + instrument, sn);

}

void clsFT232::timerProc()
{
    forceQuit = true;
}

bool clsFT232::getDeviceList()
{
    ftStatus = FT_CreateDeviceInfoList(&numDevs);

    if(ftStatus == FT_OK)
        outputs<<"Number of devices is " + QString::number(numDevs);
    else
        outputs<< "Faild to get FTDI device list";

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
            outputs<<"Failed to get device list";
            Sleep(3000);
            return false;
        }
        return true;
    }
    return false;
}


bool clsFT232::initConnection()
{
    if(false == getDeviceList())
        return false;

    QString sn = readSettings();

    int index=0;

    if(deviceInfo.contains(sn))
    {
        index = deviceInfo.indexOf(sn);
    }
    else
    {
        bool ok;
        index = clsSelectFtdiChip::selectIndex(deviceInfo ,&ok);
        if(!ok)
            return false;
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
        return false;
    }

    ftStatus = FT_SetBaudRate(ftHandle,FT_BAUD_19200); //设置波特率
    if(FT_OK != ftStatus)
    {
        qWarning()<< "Set baudrate error!";
        return false;
    }

    ftStatus = FT_SetDataCharacteristics(ftHandle,
                                         FT_BITS_8,
                                         FT_STOP_BITS_1,
                                         FT_PARITY_NONE);
    if(ftStatus != FT_OK)
    {
        qWarning()<<"Set data characterisetics error!";
        return false;
    }

    ftStatus = FT_SetFlowControl(ftHandle,
                                 FT_FLOW_NONE,
                                 NULL,
                                 NULL);
    if(ftStatus != FT_OK)
    {
        qWarning()<< "Set flow control error!";
    }

    writeSettings(deviceInfo.at(index));
    isInit = true;
    return true;
}

bool clsFT232::closeDevice()
{
    ftStatus = FT_Close(ftHandle);

    if(ftStatus != FT_OK)
        return false;
    else
        return true;
    return false;
}
