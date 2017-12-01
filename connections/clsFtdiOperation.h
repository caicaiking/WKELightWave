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

#include <QMutex>
#include <QReadWriteLock>
class clsFtdiOperation : public QObject
{
    Q_OBJECT
public:
    explicit clsFtdiOperation(QObject *parent = nullptr);

    void setBusy(bool value);
    void setLcrPassFail(bool value);
    void setHvPassFail(bool value);
    void setChannel(int channel);       //切换通道，这里是采用互斥的方法
    void setRelay(bool value);          //设置Relay
    QString getValue();                 //主要是为了判定用户是否是输入了Trig 或者reset指令

    void updataFTDIdata();              //开始更新串口用户读取的数据
    void stop();

    QString getReadString() const;
    void setReadString(const QString &value);

signals:
    void channelChanged(int value);
    void lcrStatusChanged(bool value);
    void hvStatusChanged(bool value);
    void busyStatusChanged(bool value);
public slots:
    void sleepMs(int svalue);
private:
    bool blStop;

    int channel;
    bool relayStatus;

    QString readString;         //用于更新Binning口的数据
    QMutex mutex;
    QReadWriteLock locker;
};

typedef Singleton<clsFtdiOperation> sngFtdiOp;
#endif // CLSSIGNALPROCESS_H
