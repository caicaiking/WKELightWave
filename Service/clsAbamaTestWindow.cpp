#include "clsAbamaTestWindow.h"
#include <QDebug>
#include "publicUtility.h"
#include "clsTestClass.h"
#include "clsFtdiOperation.h"
#include "clsUpdateFtdiDataThread.h"
clsAbamaTestWindow::clsAbamaTestWindow(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    trigThread = new clsRunningThread();
    trigThread->setCaptureBit(0);

    resetThread = new clsRunningThread();
    resetThread->setCaptureBit(1);

    connect(trigThread,SIGNAL(getSignal()),this,SLOT(setTrigLabel()));
    connect(resetThread,SIGNAL(getSignal()),this,SLOT(setResetLabel()));

    trigThread->start();
    resetThread->start();

    sngFtdiData::Ins()->start();

}

void clsAbamaTestWindow::closeEvent(QCloseEvent *event)
{
    trigThread->stop();
    resetThread->stop();
    sngFtdiData::Ins()->stop();

    qDebug()<< "window Closed";
}

void clsAbamaTestWindow::on_btnTrig0_clicked()
{
    sngTest::Ins()->setFtdiReadString("0");
}

void clsAbamaTestWindow::on_btnTrig1_clicked()
{
    sngTest::Ins()->setFtdiReadString("1");
}

void clsAbamaTestWindow::on_btnReset0_clicked()
{

    sngTest::Ins()->setFtdiReadString("00");
}

void clsAbamaTestWindow::on_btnReset1_clicked()
{

    sngTest::Ins()->setFtdiReadString("01");
}

void clsAbamaTestWindow::setLabelColor(QLabel *lbl)
{
    lbl->setStyleSheet("background-color:red;border-radius:20px;border:2px solid rgb(255, 82, 29);");
    publicUtility::sleepMs(100);

    int value = lbl->text().toInt();
    lbl->setText(QString::number(value+1));

    lbl->setStyleSheet("background-color:green;border-radius:20px;border:2px solid rgb(255, 82, 29);");
}

void clsAbamaTestWindow::setTrigLabel()
{
    setLabelColor(lblTrigCount);
}

void clsAbamaTestWindow::setResetLabel()
{
    setLabelColor(lblResetCount);
}


void clsAbamaTestWindow::on_btnSetBusy_toggled(bool checked)
{
    setBusyStatus(checked);
}

void clsAbamaTestWindow::on_btnSetLcr_toggled(bool checked)
{
    setLcrStatus(checked);
}

void clsAbamaTestWindow::on_btnSetHv_toggled(bool checked)
{
    setHVStatus(checked);
}

void clsAbamaTestWindow::setLcrStatus(bool status)
{
    if(!status)
        lblLcr->setStyleSheet("background-color:green;border-radius:20px;border:2px solid rgb(255, 82, 29);");
    else
        lblLcr->setStyleSheet("background-color:red;border-radius:20px;border:2px solid rgb(255, 82, 29);");
    btnSetLcr->setChecked(status);
}

void clsAbamaTestWindow::setHVStatus(bool status)
{
    if(!status)
        lblHv->setStyleSheet("background-color:green;border-radius:20px;border:2px solid rgb(255, 82, 29);");
    else
        lblHv->setStyleSheet("background-color:red;border-radius:20px;border:2px solid rgb(255, 82, 29);");
    btnSetHv->setChecked(status);
}

void clsAbamaTestWindow::setBusyStatus(bool status)
{
    if(!status)
        lblBusy->setStyleSheet("background-color:green;border-radius:20px;border:2px solid rgb(255, 82, 29);");
    else
        lblBusy->setStyleSheet("background-color:red;border-radius:20px;border:2px solid rgb(255, 82, 29);");
    btnSetBusy->setChecked(status);
}
