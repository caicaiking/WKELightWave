#ifndef CLSRUNSERVICE_H
#define CLSRUNSERVICE_H

#include <QObject>
#include "singleton.h"

class clsRunService : public QObject
{
    Q_OBJECT
public:
    explicit clsRunService(QObject *parent = nullptr);

signals:
    void showRes(QString);
public slots:
    void setTestConditions(QString);
    void switchToRunningMode(bool value);


private slots:
    void getTrigSignal();
};

typedef Singleton <clsRunService> sngRunService;
#endif // CLSRUNSERVICE_H
