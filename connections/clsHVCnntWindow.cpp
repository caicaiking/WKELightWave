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
    QString strPath = "SerialPort/";

    QString tmpStr;
    settings.readSetting(strPath + "HVTest" , tmpStr);

//    tmpStr 还需要后续处理
    sngHVCnnt::Ins()->setAddress(tmpStr);
    sngHVCnnt::Ins()->setConnectionType("");
    bool ret = sngHVCnnt::Ins()->setupConnection();
    return ret;
}


void clsHVCnntWindow::on_btnTest_clicked()
{
    sngHVCnnt::Ins()->setAddress("");
    sngHVCnnt::Ins()->setConnectionType("");

    bool retValue = sngHVCnnt::Ins()->setupConnection();

    btnTest->setEnabled(!retValue);

    if(!retValue)
        lblInfo->setText(tr("没有发现可用的FTDI连接线!请确认硬件连接."));
    else
        this->accept();

}
