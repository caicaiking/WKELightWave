#ifndef CLSHVCONNECTION_H
#define CLSHVCONNECTION_H

#include <QObject>
#include "singleton.h"
#include <windows.h>
#include "FTD2XX.H"
#include <QTimer>

//
/// \brief 这是个假的类，用来实现和高压设备的连接。
///         后面如果要有高压机的话，需要将此类从新的实现。
///

class clsHVConnection : public QObject
{
    Q_OBJECT
public:
    explicit clsHVConnection(QObject *parent = nullptr);

    void setConnectionType(QString cnntType);
    void setAddress(QString address);

    bool setupConnection();
    QString sendCommand(QString command, bool hasReturn);

    void disConnectInstrument();
    bool hasInitSucess();
signals:
    void showMessage(QString msg);
private:
    bool isInit;
    QString strAddress;
    double getRandomNumber(int max, int min);


    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;

    DWORD numDevs;
    FT_DEVICE_LIST_INFO_NODE *devInfo;
    QStringList deviceInfo;
    QStringList outputs;
    QString instrument;

    bool forceQuit;
    QTimer *timer;

private slots:
    QString readSetings();
    QString writeSettings(QString sn);
    void timerProc();

    bool getDeviceList();

public slots:
    bool closeDevice();
};

typedef Singleton<clsHVConnection> sngHVCnnt;
#endif // CLSHVCONNECTION_H
