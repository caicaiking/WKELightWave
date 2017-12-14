#ifndef CLSFTDICONNECTION_H
#define CLSFTDICONNECTION_H

#include <QObject>
#include "singleton.h"
#include <QMutex>
#include <QReadWriteLock>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "clsSettings.h"

#include "Qextserial/qextserialport.h"

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
    QextSerialPort *serialPort;
    QString portName;
    QString instrument;

   QString readData;
signals:
    void commandMsg(QString);
    void showMessage(QString);
    void recievFinished(QString);

private slots:
    void readCom();
    bool closeDevice();
    bool getDeviceList();
    void writeSettings(QString sn);
    QString readSetings();
};
typedef Singleton< clsFtdiConnection> sngFtdiCnnt;
#endif // CLSFTDICONNECTION_H
