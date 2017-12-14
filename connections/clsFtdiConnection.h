#ifndef CLSFTDICONNECTION_H
#define CLSFTDICONNECTION_H

#include <QObject>
#include "singleton.h"
#include <QMutex>
#include <QReadWriteLock>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include "clsSettings.h"
class clsFtdiConnection : public QObject
{
    Q_OBJECT
public:
    explicit clsFtdiConnection(QObject *parent = nullptr);
    ~clsFtdiConnection();
    void setConnectionType(QString);
    void setAddress(QString address);
    bool setupConnection();
    QString sendCommand(QString command, bool hasReturn);
    void disConnectInstrument();
    bool hasInitSucess();

private:
    QString strAddress;
    bool isInit;

    QSerialPort *serialPort;
    QString portName;

    QMutex mutex;
    bool forceQuit;
    QString instrument;
    QReadWriteLock lock;
signals:
    void commandMsg(QString);
    void showMessage(QString);

private slots:
    bool closeDevice();
    void timerProc();
    bool getDeviceList();
    void writeSettings(QString sn);
    QString readSetings();
};
typedef Singleton< clsFtdiConnection> sngFtdiCnnt;
#endif // CLSFTDICONNECTION_H
