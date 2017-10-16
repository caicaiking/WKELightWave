#ifndef CLSADU200_H
#define CLSADU200_H

#include <QObject>
#include "AduHid.h"

class clsADU200 : public QObject
{
    Q_OBJECT
public:
    explicit clsADU200(QObject *parent = nullptr);
    ~clsADU200();
    bool initADU200();

    QString sendCommand(QString cmmd,bool hasReturn);
    QString getInput(int port);
    bool getInputSignal(int port);
    QString shortRelay(int port);
    QString openRelay(int port);
    void setPass();
    void setFail();
    void setBDA();
    void resetBDA();
    void stop();
signals:

public slots:
private:
    void sleepMs(int t);

private:
    void *hDevice;
    bool isInit;
    bool blStop;

};

#endif // CLSADU200_H
