#ifndef CLSFTDICONNECTION_H
#define CLSFTDICONNECTION_H

#include <QObject>
#include "singleton.h"
#include <QMutex>
#include <QReadWriteLock>

class clsFtdiConnection : public QObject
{
    Q_OBJECT
public:
    explicit clsFtdiConnection(QObject *parent = nullptr);

    void setAddress(QString address);
    bool setupConnection();
    QString sendCommand(QString command, bool hasReturn);
    void disConnectInstrument();
    bool hasInitSucess();
private:
    QString strAddress;
    bool isInit;
    QMutex mutex;
    QReadWriteLock lock;

signals:
    void commandMsg(QString);
    void showMessage(QString);

public slots:
};
typedef Singleton< clsFtdiConnection> sngControlBox;
#endif // CLSFTDICONNECTION_H
