#ifndef CLSRUNNINGTHREAD_H
#define CLSRUNNINGTHREAD_H

#include <QObject>
#include <QThread>
///
/// \brief 用来识别Trigger信号和 Reset 信号
///
class clsRunningThread : public QThread
{
    Q_OBJECT
public:
    void run() override;
    bool captrueSignal(int bit);
    void setCaptureBit(int bit);
    void stop();

signals:
    void getSignal();
public slots:
private:
    bool blStop;
    int bit;

    void sleepMs(int svalue);
    QString getInput(int bit);
};

#endif // CLSRUNNINGTHREAD_H
