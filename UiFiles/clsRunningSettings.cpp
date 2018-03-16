#include "clsRunningSettings.h"
#include "clsRunSettings.h"
#include "clsConnectToServer.h"
clsRunningSettings::clsRunningSettings(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);


    switch (sngRunSettings::Ins()->getRemoteControlType()) {
    case clsRunSettings::ManualTrig:
        rbManual->setChecked(true);
        break;
    case clsRunSettings::HandlerTrig:
        rbHardware->setChecked(true);
        break;
    case clsRunSettings::LanTrig:
        rbNetWork->setChecked(true);
        break;
    default:
        break;
    }
    chkJumpOut->setChecked(sngRunSettings::Ins()->getJumpOut());
    btnConnect->setEnabled(!sngConnectServer::Ins()->getIsInit());

    txtIp->setText(sngRunSettings::Ins()->getStrIp());
    txtPort->setText(sngRunSettings::Ins()->getPort());
}

void clsRunningSettings::on_btnOk_clicked()
{
   if(rbManual->isChecked())
       sngRunSettings::Ins()->setRemoteControlType(clsRunSettings::ManualTrig);
   else if(rbHardware->isChecked())
       sngRunSettings::Ins()->setRemoteControlType(clsRunSettings::HandlerTrig);
   else
       sngRunSettings::Ins()->setRemoteControlType(clsRunSettings::LanTrig);

   sngRunSettings::Ins()->setJumpOut(chkJumpOut->isChecked());

   sngRunSettings::Ins()->writeSettings();
   this->accept();
}

void clsRunningSettings::on_btnCancel_clicked()
{
    this->reject();
}

void clsRunningSettings::on_btnConnect_clicked()
{

    sngRunSettings::Ins()->setStrIp(txtIp->text());
    sngRunSettings::Ins()->setPort(txtPort->text());
    sngConnectServer::Ins()->setIpAddressAndPort(sngRunSettings::Ins()->getStrIp(),sngRunSettings::Ins()->getPort().toInt());
    sngConnectServer::Ins()->startConnect();

    btnConnect->setEnabled(!sngConnectServer::Ins()->getIsInit());
}
