#ifndef CLSLCRCONNECTION_H
#define CLSLCRCONNECTION_H

#include <QObject>
#include "clsConnection.h"
#include "singleton.h"
class clsLcrConnection : public QObject
{
    Q_OBJECT
public:
    explicit clsLcrConnection(QObject *parent = nullptr);

    void setConnectionType(QString cnntType);
    void setAddress(QString address);

    bool setupConnection();
    QString sendCommand(QString command, bool hasReturn);

    void disConnectInstrument();
    bool hasInitSucess();

private:
    QString connectionType;
    QString strAddress;
    bool isInit;

    clsConnection *cnnt;
signals:
    void showMessage(QString msg);
public slots:
};

typedef Singleton<clsLcrConnection> sngLCRCnnt;

#endif // CLSLCRCONNECTION_H
