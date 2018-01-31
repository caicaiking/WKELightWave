#ifndef CLSHVCONNECTION_H
#define CLSHVCONNECTION_H

#include <QObject>
#include "singleton.h"
#include <QSerialPort>
#include <QSerialPortInfo>

//
/// \brief 这是个假的类，用来实现和高压设备的连接。
///         后面如果要有高压机的话，需要将此类从新的实现。
///

class clsHVConnection : public QObject
{
    Q_OBJECT
public:
    explicit clsHVConnection(QObject *parent = 0);
    ~clsHVConnection();

    void setConnectionType(QString);
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


    QString instrument;

    bool forceQuit;

    QString portName;
    QSerialPort *serialPort;

private slots:
    QString readSetings();
    void writeSettings(QString sn);
    void timerProc();

    bool getDeviceList();

public slots:
    bool closeDevice();
};

typedef Singleton<clsHVConnection> sngHVCnnt;
#endif // CLSHVCONNECTION_H
