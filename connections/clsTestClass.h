#ifndef CLSTESTCLASS_H
#define CLSTESTCLASS_H
#include "singleton.h"
#include <QMutex>
#include <QReadWriteLock>
class clsTestClass
{
public:

    explicit clsTestClass();



    QString getFtdiReadString() const;
    void setFtdiReadString(const QString &value);

private:
    QString ftdiReadString;

private:
    QMutex mutex;
    QReadWriteLock locker;
};

typedef Singleton<clsTestClass> sngTest;
#endif // CLSTESTCLASS_H

clsTestClass::clsTestClass()
{
    this->ftdiReadString = "00000000";
}

QString clsTestClass::getFtdiReadString() const
{
    return ftdiReadString;
}

void clsTestClass::setFtdiReadString(const QString &value)
{
    mutex.lock();

    const bool lock = locker.lockForWrite();
    if(lock)
    {
        ftdiReadString = value;
        locker.unlock();
    }
    mutex.unlock();
}
