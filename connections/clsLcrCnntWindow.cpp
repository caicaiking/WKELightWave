#include "clsLcrCnntWindow.h"
#include "clsLcrConnection.h"
#include "clsSettings.h"
#include <QDebug>
clsLcrCnntWindow::clsLcrCnntWindow(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    readSettings();
}

bool clsLcrCnntWindow::setupConnection()
{
    clsSettings settings;
    QString strPath = "LCR/";

    QString strIp;
    settings.readSetting(strPath +"IP", strIp);

    if(strIp.isEmpty())
        strIp=("127.0.0.1");

    strIp += ",6500";
    sngLCRCnnt::Ins()->setConnectionType("LAN");
    sngLCRCnnt::Ins()->setAddress(strIp);

    bool isInit = sngLCRCnnt::Ins()->setupConnection();
    if(!isInit)
        return false;

    QString strRet = sngLCRCnnt::Ins()->sendCommand("*IDN?", true);
    qDebug()<< strRet;
    if(strRet.contains("WAYNE KERR"))
        return true;
    else
        return false;
}

void clsLcrCnntWindow::readSettings()
{
    clsSettings settings;
    QString strPath = "LCR/";

    QString strTmp;
    settings.readSetting(strPath +"IP", strTmp);

    if( strTmp.isEmpty())
        this->txtIP->setText("127.0.0.1");
    else
        this->txtIP->setText(strTmp);
}

void clsLcrCnntWindow::saveSettings()
{
    clsSettings settings;
    QString strPath = "LCR/";

    settings.writeSetting(strPath + "IP", txtIP->text());
}

void clsLcrCnntWindow::on_btnTest_clicked()
{
    sngLCRCnnt::Ins()->setConnectionType("LAN");
    sngLCRCnnt::Ins()->setAddress(txtIP->text()+ ",6500");

    bool isInit = sngLCRCnnt::Ins()->setupConnection();

    btnTest->setEnabled(!isInit);

    if(!isInit)
        return;

    QString strRet = sngLCRCnnt::Ins()->sendCommand("*IDN?", true);
    if(strRet.contains("WAYNE KERR"))
    {
        saveSettings();
        this->accept();
    }
    else
    {
        this->reject();
    }
}
