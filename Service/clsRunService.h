#ifndef CLSRUNSERVICE_H
#define CLSRUNSERVICE_H

#include <QObject>
#include "singleton.h"
#include "clsInstrument.h"
#include "clsTestConditon.h"

class clsRunService : public QObject
{
    Q_OBJECT
public:
    explicit clsRunService(QObject *parent = nullptr);

signals:
    void showRes(QString);
    void showMsg(QString);

public slots:
    void setTestConditon(QString value);
    void switchToRunningMode(bool value);

public slots:
    void trig();
    void reset();
private:
    bool isRunningMode;
    bool isReset;
    QString strCondition;
    QList<clsTestConditons* > steps;
    clsInstrument *meter;
};

typedef Singleton<clsRunService> sngRunService;

#endif // CLSRUNSERVICE_H
