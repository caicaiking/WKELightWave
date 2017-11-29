#ifndef CLSUPDATEFTDIDATATHREAD_H
#define CLSUPDATEFTDIDATATHREAD_H

#include <QThread>
#include <QObject>
#include "singleton.h"
///
/// \brief 更新串口数据，用于判定Trig和Reset信号
///
class clsUpdateFtdiDataThread : public QThread
{
    Q_OBJECT
public:
    void run() override;
    void stop();
private:
    bool blStop;
};

typedef Singleton<clsUpdateFtdiDataThread> sngFtdiData;
#endif // CLSUPDATEFTDIDATATHREAD_H
