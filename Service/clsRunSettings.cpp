#include "clsRunSettings.h"
#include "clsSettings.h"
#include "clsRunService.h"
#include "clsWKServer.h"
#include "clsWKCommandProcess.h"
#include "clsFtdiOperation.h"
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
    switch (remoteControlType) {
    case ManualTrig:
        sngWKServer::Ins()->stopServer();
        disconnect(clsConnectSWBox::Ins(),SIGNAL(trigSignal()),sngRunService::Ins(),SLOT(handlerTrig()));
        emit remoteType(tr("手动"));
        break;
    case HandlerTrig:
        sngWKServer::Ins()->stopServer();

        connect(clsConnectSWBox::Ins(),SIGNAL(trigSignal()),sngRunService::Ins(),SLOT(handlerTrig()));
        emit remoteType(tr("硬件"));
        break;
    case LanTrig:
        sngWKServer::Ins()->startServer();

        disconnect(clsConnectSWBox::Ins(),SIGNAL(trigSignal()),sngRunService::Ins(),SLOT(handlerTrig()));
        emit remoteType(tr("网络"));
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
