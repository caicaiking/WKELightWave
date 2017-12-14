#ifndef CLSRUNNINGTHREAD_H
#define CLSRUNNINGTHREAD_H

#include <QObject>
#include <QThread>
#include "singleton.h"
///
/// \brief 用来识别Trigger信号和 Reset 信号
///
///
class clsRunningThread: public QThread
{
    Q_OBJECT
public:
    void run() override ;
    void setName(QString name);
    bool captrueSignal(int bit);
    void setCaptureBit(int bit);
    void stop();

signals:
    void getSignal();
public slots:
private:
    bool blStop;
    int bit;

    QString strName;
    void sleepMs(int svalue);
    QString getInput(int bit);
};

typedef Singleton<clsRunningThread> sngTrigThread;
#endif // CLSRUNNINGTHREAD_H
