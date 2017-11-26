#ifndef CLSSIGNALTHREAD_H
#define CLSSIGNALTHREAD_H

#include <QThread>
#include "singleton.h"
class clsSignalThread : public QThread
{
    Q_OBJECT
public:
    explicit clsSignalThread(QObject *parent = 0);
    ~clsSignalThread();
    void stop();

    void setPass();
    void setFail();
    void setBusy();
    void resetBusy();
    void emitBDA();


signals:
    void trigCaptured();
    void initOk();
    void showStatus(QString);

public slots:

protected:
    void run();

private:
    bool isStop;
};

typedef Singleton<clsSignalThread> sngSignalThread;

#endif // CLSSIGNALTHREAD_H
