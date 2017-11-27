#ifndef CLSSIGNALPROCESS_H
#define CLSSIGNALPROCESS_H

#include <QObject>
#include "singleton.h"

#define BUSYCMMD "Set Busy command"
#define IDELCMMD "Set Idel command"
#define LCRPASSCMMD "Set Lcr Pass Command"
#define LCRFAILCMMD "Set Lcr Fail Command"
#define HVPASSCMMD "Set Hv Pass Command"
#define HVFAILCMMD "Set Hv Fail Command"
#define SETCHANNEL "Set Channel command"

class clsSignalProcess : public QObject
{
    Q_OBJECT
public:
    explicit clsSignalProcess(QObject *parent = nullptr);

    void setBusy(bool value);
    void setLcrPassFail(bool value);
    void setHvPassFail(bool value);
    void setChannel(int channel);       //切换通道，这里是采用互斥的方法
    QString getValue();                 //主要是为了判定用户是否是输入了Trig 或者reset指令

signals:
    void channelChanged(int value);
    void lcrStatusChanged(bool value);
    void hvStatusChanged(bool value);
    void busyStatusChanged(bool value);
public slots:
};

typedef Singleton<clsSignalProcess> sngSgnlProcess;
#endif // CLSSIGNALPROCESS_H
