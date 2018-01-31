#ifndef CLSFTDICONNECTION_H
#define CLSFTDICONNECTION_H

#include <QObject>
#include "singleton.h"
#include <QMutex>
#include <QReadWriteLock>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "clsSettings.h"

class clsFtdiConnection : public QObject
{
    Q_OBJECT
public:
    explicit clsFtdiConnection(QObject *parent = 0);
    ~clsFtdiConnection();
    void setConnectionType(QString);
    void setAddress(QString address);
    bool setupConnection();
    QString sendCommand(QString command);
    void disConnectInstrument();
    bool hasInitSucess();

private:
    QString strAddress;
    bool isInit;
    QSerialPort *serialPort;
    QString portName;
    QString instrument;

   QString readData;
   QString retData;
signals:
    void commandMsg(QString);
    void showMessage(QString);
    void recievFinished(QString);
    void trigSingal();
    void resetSignal();

private slots:
    void readCom();
    bool closeDevice();
    bool getDeviceList();
    void writeSettings(QString sn);
    QString readSetings();
    void setResString(QString value);
};
typedef Singleton< clsFtdiConnection> sngFtdiCnnt;
#endif // CLSFTDICONNECTION_H
