#ifndef CLSTESTCLASS_H
#define CLSTESTCLASS_H
#include "singleton.h"
#include <QMutex>
#include <QReadWriteLock>
#include <QString>

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



