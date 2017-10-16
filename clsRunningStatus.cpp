#include "clsRunningStatus.h"

clsRunningStatus::clsRunningStatus(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
}

void clsRunningStatus::setChannel(const int channel)
{
    this->channel=channel;
}

void clsRunningStatus::setItem1(const QString item)
{
    this->item1=item;
}

void clsRunningStatus::setItem2(const QString item)
{
    this->item2=item;
}

void clsRunningStatus::setStatus1(const bool status)
{
    this->status1=status;
}

void clsRunningStatus::setStatus2(const bool status)
{
    this->status2=status;
}

void clsRunningStatus::updateLabels()
{
    QStringList colorList;
    colorList<<"#D891EF"<<"#FFBF00"<<"#00FFFF"<<"#FDEE00"<<"#D0FF14"<<"#D19FE8"
            <<"#FA6E79"<<"#FE6F5E"<<"#ACE5EE"<<"#66FF00"<<"#FF007F"<<"#84DE02"<<"#1F75FE"
           <<"#08E8DE"<<"#FFAA1D"<<"#FF55A3"<<"#FF033E"<<"#FF2052"<<"#E0218A"<<"#ACE5EE";
    labelChannel->setStyleSheet(QString("background-color:%1").arg(colorList.at(channel-1)));
    labelChannel->setFont(QFont("楷体",20));
    labelChannel->setText(tr("通道")+QString::number(channel));
}

void clsRunningStatus::updateStatusLabels()
{
    groupBox->setFont(QFont("楷体",15));
    if(status1)
    {
        labelStatus1->setStyleSheet(QString("background-color:#66FF00"));
        labelItem1->setStyleSheet(QString("background-color:#66FF00"));
        labelRes1->setStyleSheet(QString("background-color:#66FF00"));
        labelStatus1->setText(tr("PASS"));
    }
    else
    {
        labelStatus1->setStyleSheet(QString("background-color:red"));
        labelItem1->setStyleSheet(QString("background-color:red"));
        labelRes1->setStyleSheet(QString("background-color:red"));
        labelStatus1->setText(tr("FAIL"));
    }
    if(status2)
    {
        labelStatus2->setStyleSheet(QString("background-color:#66FF00"));
        labelItem2->setStyleSheet(QString("background-color:#66FF00"));
        labelRes2->setStyleSheet(QString("background-color:#66FF00"));
        labelStatus2->setText(tr("PASS"));
    }
    else
    {
        labelStatus2->setStyleSheet(QString("background-color:red"));
        labelItem2->setStyleSheet(QString("background-color:red"));
        labelRes2->setStyleSheet(QString("background-color:red"));
        labelStatus2->setText(tr("FAIL"));
    }
}
