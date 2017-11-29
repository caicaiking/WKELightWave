#include "clsTestClass.h"

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

    const bool lock = locker.tryLockForWrite();
    if(lock)
    {
        ftdiReadString = value;
        locker.unlock();
    }
    mutex.unlock();
}
