#include "clsRunSettings.h"
#include "clsSettings.h"
#include "clsRunService.h"
#include "clsFtdiOperation.h"
#include "clsConnectToServer.h"
clsRunSettings::clsRunSettings(QObject *parent): QObject(parent)
{
}

void clsRunSettings::readSettings()
{

    clsSettings settings;
    QString strNode ="RunSettings/";
    settings.readSetting(strNode + "JumpOut", this->jumpOut);

    settings.readSetting(strNode + "ServerIp", this->strIp);
    if(strIp.isEmpty())
        this->strIp = "127.0.0.1";

    settings.readSetting(strNode + "ServerPort", this->port);
    if(port.isEmpty())
        this->port = "5700";

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
    settings.writeSetting(strNode + "ServerIp", this->strIp);
    settings.writeSetting(strNode + "ServerPort", this->port);
}

clsRunSettings::TrigSource clsRunSettings::getRemoteControlType() const
{
    return remoteControlType;
}

void clsRunSettings::setRemoteControlType(TrigSource value)
{
    remoteControlType = value;

    switch (remoteControlType) {
    case ManualTrig:
        disconnect(clsConnectSWBox::Ins(),SIGNAL(trigSignal()),sngRunService::Ins(),SLOT(handlerTrig()));
        disconnect(sngConnectServer::Ins(),&clsConnectToServer::trigSignal,sngRunService::Ins(),&clsRunService::handlerTrig);
        emit remoteType(tr("手动"));
        break;
    case HandlerTrig:

        connect(clsConnectSWBox::Ins(),SIGNAL(trigSignal()),sngRunService::Ins(),SLOT(handlerTrig()),Qt::UniqueConnection);
        disconnect(sngConnectServer::Ins(),&clsConnectToServer::trigSignal,sngRunService::Ins(),&clsRunService::handlerTrig);
        emit remoteType(tr("硬件"));
        break;
    case LanTrig:

        sngConnectServer::Ins()->setIpAddressAndPort(this->strIp,port.toInt());
        sngConnectServer::Ins()->startConnect();

        connect(sngConnectServer::Ins(),&clsConnectToServer::trigSignal,sngRunService::Ins(),&clsRunService::lanTrig,Qt::UniqueConnection);
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

QString clsRunSettings::getStrIp() const
{
    return strIp;
}

QString clsRunSettings::getPort() const
{
    return port;
}

void clsRunSettings::setPort(const QString &value)
{
    port = value;
}

void clsRunSettings::setStrIp(const QString &value)
{
    strIp = value;
}
