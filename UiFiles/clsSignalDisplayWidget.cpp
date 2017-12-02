#include "clsSignalDisplayWidget.h"
#include "publicUtility.h"
#include "clsRunService.h"
#include "clsHVRunningMode.h"
#include "clsWK6500RunningMode.h"

clsSignalDisplayWidget::clsSignalDisplayWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    passPix = QString(":/dotGreen.png");
    failPix = QString(":/dotRed.png");

    connect(sngRunService::Ins(),&clsRunService::busyStatus,this,&clsSignalDisplayWidget::setBusy);
    connect(sngRunService::Ins(),&clsRunService::lcrPF,this,&clsSignalDisplayWidget::setLCR);
    connect(sngRunService::Ins(),&clsRunService::hvPF,this,&clsSignalDisplayWidget::setHV);
    connect(sngRunService::Ins(),&clsRunService::trigSignal,this,&clsSignalDisplayWidget::setTrig);
    connect(sngRunService::Ins(),&clsRunService::resetSignal,this,&clsSignalDisplayWidget::reset);
    connect(sngRunService::Ins(),&clsRunService::currentStep,this,&clsSignalDisplayWidget::setCurrentStep);
    connect(sngHVRun::Ins(),&clsHVRunningMode::voltageOutput,this,&clsSignalDisplayWidget::hvOutput);
    connect(sngWK6500Run::Ins(),&clsWK6500RunningMode::voltageOutput,this,&clsSignalDisplayWidget::lcrOutput);

    this->lcdNumber->setVisible(false);
    setLcdNumberStyle();

    totle = new clsDataStatistics(this);
    connect(totle,&clsDataStatistics::showSpeed, lblTrigSpeed,&QLabel::setText);

    lcrData = new clsDataStatistics(this);
    connect(lcrData,&clsDataStatistics::showTotle, lblLcrTotle,&QLabel::setText);
    connect(lcrData,&clsDataStatistics::showPass, lblLcrPass,&QLabel::setText);
    connect(lcrData,&clsDataStatistics::showFail, lblLcrFail,&QLabel::setText);
    connect(lcrData,&clsDataStatistics::showPassRate, lblLcrPassRate,&QLabel::setText);

    hvData = new clsDataStatistics(this);
    connect(hvData,&clsDataStatistics::showTotle, lblHVTotle,&QLabel::setText);
    connect(hvData,&clsDataStatistics::showPass, lblHVPass,&QLabel::setText);
    connect(hvData,&clsDataStatistics::showFail, lblHVFail,&QLabel::setText);
    connect(hvData,&clsDataStatistics::showPassRate, lblHVPassRate,&QLabel::setText);
}

void clsSignalDisplayWidget::setBusy(bool value)
{
    if(value == false)
        totle->addData(false);

    setLabelPixmap(this->lblBusySatusLed,!value);
}

void clsSignalDisplayWidget::setLCR(bool value)
{
    lcrData->addData(value);
    setLabelPixmap(this->lblLCRStatusLed,value);
}

void clsSignalDisplayWidget::setHV(bool value)
{
    hvData->addData(value);
    setLabelPixmap(this->lblHVStatusLed,value);
}

void clsSignalDisplayWidget::setTrig()
{
    setLabelPixmap(lblTrig,false);
    publicUtility::sleepMs(50);
    setLabelPixmap(lblTrig,true);
}

void clsSignalDisplayWidget::reset()
{
    setLabelPixmap(lblReset,false);
    publicUtility::sleepMs(25);
    setLabelPixmap(lblReset,true);
}

void clsSignalDisplayWidget::lcrOutput(bool value)
{
    setLabelPixmap(lblLcrOutput,value);
}

void clsSignalDisplayWidget::hvOutput(bool value)
{
    setLabelPixmap(lblHVOutputLed,!value);
}

void clsSignalDisplayWidget::setCurrentStep(int value)
{
    this->lcdNumber->display(value);
}

void clsSignalDisplayWidget::setLabelPixmap(QLabel *lbl, bool status)
{
    if(status)
        lbl->setPixmap(QPixmap(passPix));
    else
        lbl->setPixmap(QPixmap(failPix));

}

void clsSignalDisplayWidget::setLcdNumberStyle()
{
    this->lcdNumber->setDigitCount(2);
    this->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    QPalette lcdpat = this->lcdNumber->palette();
    lcdpat.setColor(QPalette::Normal, QPalette::WindowText,Qt::red);
    this->lcdNumber->setPalette(lcdpat);
    this->lcdNumber->setStyleSheet("background-color:yellow");
}
