#include "clsRunningSettings.h"
#include "clsRunSettings.h"
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
