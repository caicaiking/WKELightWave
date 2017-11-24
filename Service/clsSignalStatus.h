#ifndef CLSSIGNALCONTROL_H
#define CLSSIGNALCONTROL_H

#include <QObject>
#include "singleton.h"

class clsSignalStatus : public QObject
{
    Q_OBJECT
public:
    explicit clsSignalStatus(QObject *parent = nullptr);

    void resetLCRStatus();
    void resetHVStatus();
    bool getLcrStatus() const;
    bool getHvStatus() const;

signals:

public slots:

    void setLCRStatus(bool value);
    void setHVStatus(bool value);

private:
    bool lcrStatus;
    bool hvStatus;
};

typedef Singleton<clsSignalStatus> sngSignalStatus;
#endif // CLSSIGNALCONTROL_H
