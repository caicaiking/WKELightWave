#ifndef CLSRUNSERVICE_H
#define CLSRUNSERVICE_H

#include <QObject>
#include "singleton.h"
#include "clsInstrument.h"
#include "clsTestConditon.h"
#include <QTextStream>
#include <QFile>

class clsRunService : public QObject
{
    Q_OBJECT
public:
    explicit clsRunService(QObject *parent = nullptr);
~clsRunService();
signals:
    void showRes(QString);
    void showMsg(QString);

public slots:
    void setTestConditon(QString value);
    void switchToRunningMode(bool value);

public slots:
    void trig();
    void reset();

    void handlerTrig();
    QString lanTrig();
signals:
    void busyStatus(bool);
    void lcrPF(bool);
    void hvPF(bool);
    void trigSignal();
    void resetSignal();
    void currentStep(int i);
    void controlStatus(QString);

private:
    bool isRunningMode;
    bool isReset;
    QString strCondition;
    QList<clsTestConditons* > steps;
    clsInstrument *meter;
    QFile * file;
    QString sep;
    QString getLastFilePath();
};

typedef Singleton<clsRunService> sngRunService;

#endif // CLSRUNSERVICE_H
