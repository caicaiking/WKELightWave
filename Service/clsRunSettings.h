#ifndef CLSRUNSETTINGS_H
#define CLSRUNSETTINGS_H

#include <QObject>
#include "singleton.h"
class clsRunSettings: public QObject
{
    Q_OBJECT

public:
    explicit clsRunSettings(QObject *parent =0);

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

    QString getStrIp() const;
    QString getPort() const;
    void setPort(const QString &value);
    void setStrIp(const QString &value);

signals:
    void remoteType(QString);
private:
    TrigSource remoteControlType;
    bool jumpOut;

    QString strIp;
    QString port;
};

typedef Singleton<clsRunSettings> sngRunSettings;
#endif // CLSRUNSETTINGS_H
