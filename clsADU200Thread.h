#ifndef CLSADU200THREAD_H
#define CLSADU200THREAD_H

#include <QThread>
#include "clsADU200.h"

class clsADU200Thread : public QThread
{
    Q_OBJECT
public:
    explicit clsADU200Thread(QObject *parent = nullptr);
    void run();
    void setPass();
    void setFail();
    void setBDA();
    void resetBDA();

signals:
    void adu200Trig();

public slots:

private:
    clsADU200 *adu200;
    bool isInit;
};

#endif // CLSADU200THREAD_H
