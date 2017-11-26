#include "clsHVCnntWindow.h"
#include "clsSettings.h"
#include "clsHVConnection.h"
clsHVCnntWindow::clsHVCnntWindow(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
}

bool clsHVCnntWindow::setupConnection()
{
    clsSettings settings;
    QString strPath = "HV/";

    QString tmpStr;
    settings.readSetting(strPath + "Address" , tmpStr);

//    tmpStr 还需要后续处理
    sngHVCnnt::Ins()->setAddress(tmpStr);
    sngHVCnnt::Ins()->setConnectionType("");
    bool ret = sngHVCnnt::Ins()->setupConnection();
    return ret;
}

void clsHVCnntWindow::readSettings()
{
    clsSettings settings;
    QString strPath = "HV/";

    QString tmpStr;
    settings.readSetting(strPath + "Address" , tmpStr);

    txtAddress->setText(tmpStr);
}

void clsHVCnntWindow::writeSettings()
{
    clsSettings settings;
    QString strPath = "HV/";

    settings.writeSetting(strPath + "Address" , txtAddress->text());

}

void clsHVCnntWindow::on_btnTest_clicked()
{
    sngHVCnnt::Ins()->setAddress(txtAddress->text());
    sngHVCnnt::Ins()->setConnectionType("");

    bool retValue = sngHVCnnt::Ins()->setupConnection();

    btnTest->setEnabled(!retValue);

    if(retValue)
        this->accept();

}
