#ifndef CLSRUNSETTINGS_H
#define CLSRUNSETTINGS_H

#include <QObject>
#include "singleton.h"
class clsRunSettings: public QObject
{
    Q_OBJECT

public:
    explicit clsRunSettings(QObject *parent =nullptr);

    enum TrigSource
    {
        LanTrig = 1,
        HandlerTrig =2,
        ManualTrig =0
    };

    void readSettings();
    void writeSettings();
    TrigSource getRemoteControlType() const;
    void setRemoteControlType(TrigSource value);

    bool getJumpOut() const;
    void setJumpOut(bool value);
signals:
    void remoteType(QString);
private:
    TrigSource remoteControlType;
    bool jumpOut;
};

typedef Singleton<clsRunSettings> sngRunSettings;
#endif // CLSRUNSETTINGS_H
