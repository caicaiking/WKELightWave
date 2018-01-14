#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
class clsTcpIpThread : public QThread
{
    Q_OBJECT
public:
    explicit clsTcpIpThread(int Id, QObject *parent=0);

    void run();
    int getSocketDescriptor() const;

public slots:
    void readRead();
     void disconnected();

     void write(QString str);
signals:
     void error(QTcpSocket::SocketError err);
     void getCommand(QString str);
private:
   QTcpSocket *socket;
   int socketDescriptor;

};

#endif // MYTHREAD_H
