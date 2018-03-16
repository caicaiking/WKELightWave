#ifndef CLSTCPIP_H
#define CLSTCPIP_H

#include <QObject>

#include "singleton.h"
#include <QTcpSocket>

class clsConnectToServer : public QTcpSocket
{
    Q_OBJECT
public:
    explicit clsConnectToServer(QObject *parent=0);

    void setIpAddressAndPort(QString ip, int port);
    void startConnect();
    bool getIsInit() const;

public slots:
    void readPort();
    void writeRes(QString res);



signals:
    void getCommand(QString strCmmd);
    void trigSignal();
    void lanRemote(bool value);
private:
    QString ip;
    int port;
    bool isInit;

};

typedef Singleton<clsConnectToServer> sngConnectServer;
#endif // CLSTCPIP_H
