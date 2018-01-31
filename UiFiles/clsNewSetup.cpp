#include "clsNewSetup.h"
#include "clsWK6500Meter.h"
#include "clsHightVoltage.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include "publicUtility.h"
#include <QDebug>

clsNewSetup::clsNewSetup(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);

}

int clsNewSetup::getChannelStart() const
{
    return this->channelStart;
}

int clsNewSetup::getChannelStop() const
{
    return this->channelStop;
}

QPoint clsNewSetup::getChannel() const
{
   return QPoint(channelStart,this->channelStop);
}


void clsNewSetup::setChannel(int channelStart, int channelStop)
{
    this->cmbTerminal1->setCurrentIndex(channelStart-1);
    this->cmbTerminal2->setCurrentIndex(channelStop-1);
}

void clsNewSetup::setMeter(QString meter)
{
   this->show();
   if(meter == "WK6500")
       on_btnLCR_clicked();
   else
       on_btnHV_clicked();
}

QString clsNewSetup::getCondtion() const
{
    return condition;
}

QString clsNewSetup::getMeter() const
{
    return meter;
}


void clsNewSetup::on_btnLCR_clicked()
{
    this->channelStart = cmbTerminal1->currentIndex()+1;
    this->channelStop = cmbTerminal2->currentIndex()+1;
    clsWK6500Meter *dlg=new clsWK6500Meter(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        this->meter="WK6500";
        QString tmpCondition=dlg->getCondition();
        QVariantMap conditionMap;
        QJsonDocument jsondocument;

        conditionMap.insert("channelStart", channelStart);
        conditionMap.insert("channelStop", channelStop);
        conditionMap.insert("meter", meter);
        conditionMap.insert("conditions", tmpCondition);

        jsondocument=QJsonDocument::fromVariant(conditionMap);
        if(!(jsondocument.isNull()))
        {
            condition=jsondocument.toJson();
        }
        this->accept();
    }
}

void clsNewSetup::on_btnHV_clicked()
{
    this->channelStart = cmbTerminal1->currentIndex()+1;
    this->channelStop = cmbTerminal2->currentIndex()+1;
    clsHightVoltage *dlg=new clsHightVoltage(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        this->meter="HV";
        QString tmpCondition=dlg->getCondition();
        QVariantMap conditionMap;
        conditionMap.insert("channelStart",channelStart);
        conditionMap.insert("channelStop",channelStop);
        conditionMap.insert("meter",meter);
        conditionMap.insert("conditions", tmpCondition);
        QJsonDocument jsondocument=QJsonDocument::fromVariant(conditionMap);
        if(!(jsondocument.isNull()))
        {
            condition=jsondocument.toJson();
        }

        this->accept();
    }
}

void clsNewSetup::on_btnCancel_clicked()
{
    this->reject();
}

void clsNewSetup::on_cmbTerminal1_currentIndexChanged(int index)
{
    this->channelStart = index +1;
}

void clsNewSetup::on_cmbTerminal2_currentIndexChanged(int index)
{
   this->channelStop = index +1;
}
