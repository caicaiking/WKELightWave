#include "clsFtdiCnntWindow.h"
#include "clsFtdiConnection.h"
#include "clsSettings.h"

clsFtdiCnntWindow::clsFtdiCnntWindow(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    readSettings();
}

bool clsFtdiCnntWindow::setupConnection()
{
    clsSettings settings;
    QString strPath = "WKEC/";

    QString strTmp;

    settings.readSetting(strPath + "Address", strTmp);

    sngControlBox::Ins()->setAddress(strTmp);
    bool blRet = sngControlBox::Ins()->setupConnection();

    return blRet;
}

void clsFtdiCnntWindow::readSettings()
{
    clsSettings settings;
    QString strPath = "WKEC/";

    QString strTmp;

    settings.readSetting(strPath + "Address", strTmp);
    this->txtAddress->setText(strTmp);

}

void clsFtdiCnntWindow::writeSettings()
{
    clsSettings settings;
    QString strPath = "WKEC/";

    QString strTmp;

    settings.writeSetting(strPath + "Address", strTmp);

}

void clsFtdiCnntWindow::on_btnTest_clicked()
{
    sngControlBox::Ins()->setAddress(txtAddress->text());
    bool blRet = sngControlBox::Ins()->setupConnection();
    btnTest->setEnabled(!blRet);

    if(blRet)
    {
        writeSettings();
        this->accept();
    }
}
