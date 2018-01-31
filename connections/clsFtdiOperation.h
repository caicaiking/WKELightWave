#ifndef CLSSIGNALPROCESS_H
#define CLSSIGNALPROCESS_H

#include <QObject>
#include "singleton.h"

#define BUSYCMMD    "\tFtdi-->Set Busy Command"
#define IDELCMMD    "\tFtdi-->Reset Busy Command"
#define LCRPASSCMMD "\tFtdi-->Set Lcr * Pass * Command"
#define LCRFAILCMMD "\tFtdi-->Set Lcr * Fail * Command"
#define HVPASSCMMD  "\tFtdi-->Set Hv * Pass * Command"
#define HVFAILCMMD  "\tFtdi-->Set Hv * Fail * Command"
#define SETCHANNEL  "\tFtdi-->Set Channel Command"
#define QUERYCMMD   "\tFtdi-->Query Status Command"
#define SETRELAY    "\tFtdi-->Set Relay Command"
#define OPENRELAY   "\tFtdi-->Reset Relay Command"

class clsFtdiOperation : public QObject
{
    Q_OBJECT
public:
    explicit clsFtdiOperation(QObject *parent = 0);

    void setBusy(bool value);
    void setLcrPassFail(bool value);
    void setHvPassFail(bool value);
    void setChannel(QPoint channel, QString type);       //切换通道，这里是采用互斥的方法
    void setRelay(bool value);          //设置Relay
    void setIo(int value);
signals:
    void channelChanged(QString value);
    void lcrStatusChanged(bool value);
    void hvStatusChanged(bool value);
    void busyStatusChanged(bool value);
    void trigSignal();
    void resetSignal();
public slots:
    void sleepMs(int svalue);
private:
    int portValue;
    bool relayStatus;
};

typedef Singleton<clsFtdiOperation> clsConnectSWBox;
#endif // CLSSIGNALPROCESS_H
