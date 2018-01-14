#ifndef CLSWKCOMMANDPROCESS_H
#define CLSWKCOMMANDPROCESS_H

#include <QObject>
#include <QDebug>
#include "clsWKServer.h"
#include "singleton.h"
#include <QMap>

class clsWKCommandProcess : public QObject
{
    Q_OBJECT
public:
    explicit clsWKCommandProcess(QObject *parent = nullptr);
    void setIsRemote(bool value);

    typedef void (clsWKCommandProcess::* QUERY_FUNCTION)();
    typedef void (clsWKCommandProcess::* SET_FUNCTION)(const QString &);


signals:
    void writeToClient(QString str);
    void lanRemote(bool value);
public slots:
    void setGpibCommand(QString str);


    void queryId();
    void querySWOption();
    void trig(const QString &empty);

    void queryItem1();
    void queryItem2();
    void queryEqucct();
    void queryRange();
    void queryFrequency();
    void queryLevelValue();
    void queryLevelType();
    void queryBiasValue();
    void queryBiasType();
    void queryBiasStatus();
    void querySpeed();
    void queryBiasFitExit();
    void queryBiasUnit();
    void querySysBias();

    void setItem1(const QString &value);
    void setItem2(const QString &value);
    void setEqucct(const QString &value);
    void setRange(const QString &value);
    void setFrequency(const QString &value);
    void setLevelValue(const QString &value);
    void setBiasValue(const QString &value);
    void setBiasType(const QString &value);
    void setBiasStatus(const QString &value);
    void setSpeed(const QString &value);
    void setFastGpib(const QString &value);

private:
    QMap<QString, QUERY_FUNCTION> queryFunction;
    QMap<QString, SET_FUNCTION> setFunction;
    int lastCmmdType;
};

typedef Singleton < clsWKCommandProcess> sngWkCommandProcess;
#endif // CLSWKCOMMANDPROCESS_H
