#include "clsRunSettings.h"
#include "clsSettings.h"
#include "clsRunService.h"
#include "clsWKServer.h"
#include "clsWKCommandProcess.h"
#include "clsRunningThread.h"

clsRunSettings::clsRunSettings(QObject *parent): QObject(parent)
{
}

void clsRunSettings::readSettings()
{

    clsSettings settings;
    QString strNode ="RunSettings/";
    settings.readSetting(strNode + "JumpOut", this->jumpOut);

    int tmp;
    settings.readSetting(strNode +"remoteControlType", tmp);
    this->remoteControlType = (clsRunSettings::TrigSource)tmp;
    this->setRemoteControlType(this->remoteControlType);


}

void clsRunSettings::writeSettings()
{

    clsSettings settings;
    QString strNode ="RunSettings/";
    settings.writeSetting(strNode +"remoteControlType",this->remoteControlType);
    settings.writeSetting(strNode + "JumpOut", this->jumpOut);
}

clsRunSettings::TrigSource clsRunSettings::getRemoteControlType() const
{
    return remoteControlType;
}

void clsRunSettings::setRemoteControlType(TrigSource value)
{
    remoteControlType = value;

    sngWKServer::Ins()->stopServer();
    sngTrigThread::Ins()->stop();
    switch (remoteControlType) {
    case ManualTrig:
        sngWKServer::Ins()->stopServer();
        sngTrigThread::Ins()->stop();
        emit remoteType(tr("手动"));
        break;
    case HandlerTrig:
        sngWKServer::Ins()->stopServer();

        sngTrigThread::Ins()->setName("Trig");
        sngTrigThread::Ins()->setCaptureBit(1);
        connect(sngTrigThread::Ins(),SIGNAL(getSignal()),sngRunService::Ins(),SLOT(handlerTrig()));
        sngTrigThread::Ins()->start();
        emit remoteType(tr("硬件"));
        break;
    case LanTrig:
        sngTrigThread::Ins()->stop();
        sngWKServer::Ins()->startServer();

        emit remoteType(tr("网口"));
        break;
    default:
        break;

    }

}

bool clsRunSettings::getJumpOut() const
{
    return jumpOut;
}

void clsRunSettings::setJumpOut(bool value)
{
    jumpOut = value;
}
