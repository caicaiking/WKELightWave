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
    void trig(const QString &empty);

private:
    QMap<QString, QUERY_FUNCTION> queryFunction;
    QMap<QString, SET_FUNCTION> setFunction;
    int lastCmmdType;
};

typedef Singleton < clsWKCommandProcess> sngWkCommandProcess;
#endif // CLSWKCOMMANDPROCESS_H
