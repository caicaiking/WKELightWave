#include "clsFtdiCnntWindow.h"
#include "clsFtdiConnection.h"
#include "clsSettings.h"

clsFtdiCnntWindow::clsFtdiCnntWindow(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
}

bool clsFtdiCnntWindow::setupConnection()
{
    clsSettings settings;
    QString strPath = "SerialPort/";

    QString strTmp;

    settings.readSetting(strPath + "WKEC", strTmp);

    sngFtdiCnnt::Ins()->setAddress(strTmp);
    sngFtdiCnnt::Ins()->setConnectionType("");
    bool blRet = sngFtdiCnnt::Ins()->setupConnection();

    return blRet;
}


void clsFtdiCnntWindow::on_btnTest_clicked()
{
    sngFtdiCnnt::Ins()->setAddress("");
    sngFtdiCnnt::Ins()->setConnectionType("");
    sngFtdiCnnt::Ins()->setupConnection();
    bool blRet = sngFtdiCnnt::Ins()->setupConnection();
    btnTest->setEnabled(!blRet);

    if(blRet)
        this->accept();
    else
        lblInfo->setText(tr("没有发现可用的FTDI连接线!请确认硬件连接."));
}
