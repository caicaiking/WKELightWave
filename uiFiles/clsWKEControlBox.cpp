#include "clsWKEControlBox.h"
#include "clsWK6500Meter.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include "clsHightVoltage.h"

clsWKEControlBox::clsWKEControlBox(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    connect(labelLCR2,SIGNAL(labelClicked()),this,SLOT(labelLCR2Clicked()));
    connect(labelLCR3,SIGNAL(labelClicked()),this,SLOT(labelLCR3Clicked()));
    connect(labelLCR4,SIGNAL(labelClicked()),this,SLOT(labelLCR4Clicked()));
    connect(labelHV2,SIGNAL(labelClicked()),this,SLOT(labelHV2Clicked()));
    connect(labelHV3,SIGNAL(labelClicked()),this,SLOT(labelHV3Clicked()));
    connect(labelHV4,SIGNAL(labelClicked()),this,SLOT(labelHV4Clicked()));

    lcrCondition<<" "<<" "<<" "<<" ";
}

QVariantMap clsWKEControlBox::parseCondition(QString condition)
{
    QJsonParseError error;
    QJsonDocument jsonDocument=QJsonDocument::fromJson(condition.toUtf8(),&error);
    if(error.error==QJsonParseError::NoError)
    {
        if(!(jsonDocument.isNull() || jsonDocument.isEmpty()))
        {
            if(jsonDocument.isObject())
            {
                QVariantMap conditionMap=jsonDocument.toVariant().toMap();
                return conditionMap;
            }
        }
    }
}

QStringList clsWKEControlBox::getLCRCondition() const
{
    return lcrCondition;
}

void clsWKEControlBox::labelLCR1Clicked()
{

}

void clsWKEControlBox::labelLCR2Clicked()
{
       clsWK6500Meter *dlg=new clsWK6500Meter;
       if(dlg->exec()==QDialog::Accepted)
       {
           QString condition=dlg->getCondtion();
           lcrCondition.replace(1,condition);
           QVariantMap conditionMap=parseCondition(condition);
           QString item21=conditionMap["item1"].toString();
           QString item22=conditionMap["item2"].toString();
           double freqency2=conditionMap["frequency"].toDouble();
           double level2=conditionMap["level"].toDouble();
           QString levelUnit2=conditionMap["levelUnit"].toString();
           QString range2=conditionMap["range"].toString();
           QString speed2=conditionMap["speed"].toString();
           QString equcct2=conditionMap["equcct"].toString();
           double bias2=conditionMap["bias"].toDouble();
           QString biasType2=conditionMap["biasType"].toString();
           QString biasSwitch2=conditionMap["biasSwitch"].toString();

           QString tx=QString("%1,%2,%3,%4,%5,%6,%7,%8,%9").arg(item21).arg(item22)
                   .arg(QString::number(freqency2)+"Hz").arg(QString::number(level2)+levelUnit2)
                   .arg(range2).arg(speed2).arg(equcct2).arg(QString::number(bias2)+biasType2)
                   .arg(biasSwitch2);
            labelLCR2->setText(tx);
       }
}

void clsWKEControlBox::labelLCR3Clicked()
{
    clsWK6500Meter *dlg=new clsWK6500Meter;
    if(dlg->exec()==QDialog::Accepted)
    {
        QString condition=dlg->getCondtion();
        lcrCondition.replace(2,condition);
        QVariantMap conditionMap=parseCondition(condition);
        QString item31=conditionMap["item1"].toString();
        QString item32=conditionMap["item2"].toString();
        double freqency3=conditionMap["frequency"].toDouble();
        double level3=conditionMap["level"].toDouble();
        QString levelUnit3=conditionMap["levelUnit"].toString();
        QString range3=conditionMap["range"].toString();
        QString speed3=conditionMap["speed"].toString();
        QString equcct3=conditionMap["equcct"].toString();
        double bias3=conditionMap["bias"].toDouble();
        QString biasType3=conditionMap["biasType"].toString();
        QString biasSwitch3=conditionMap["biasSwitch"].toString();

        QString tx=QString("%1,%2,%3,%4,%5,%6,%7,%8,%9").arg(item31).arg(item32)
                .arg(QString::number(freqency3)+"Hz").arg(QString::number(level3)+levelUnit3)
                .arg(range3).arg(speed3).arg(equcct3).arg(QString::number(bias3)+biasType3)
                .arg(biasSwitch3);
        labelLCR3->setText(tx);
    }
}

void clsWKEControlBox::labelLCR4Clicked()
{
    clsWK6500Meter *dlg=new clsWK6500Meter;
    if(dlg->exec()==QDialog::Accepted)
    {
        QString condition=dlg->getCondtion();
        lcrCondition.replace(3,condition);
        QVariantMap conditionMap=parseCondition(condition);
        QString item41=conditionMap["item1"].toString();
        QString item42=conditionMap["item2"].toString();
        double freqency4=conditionMap["frequency"].toDouble();
        double level4=conditionMap["level"].toDouble();
        QString levelUnit4=conditionMap["levelUnit"].toString();
        QString range4=conditionMap["range"].toString();
        QString speed4=conditionMap["speed"].toString();
        QString equcct4=conditionMap["equcct"].toString();
        double bias4=conditionMap["bias"].toDouble();
        QString biasType4=conditionMap["biasType"].toString();
        QString biasSwitch4=conditionMap["biasSwitch"].toString();

        QString tx=QString("%1,%2,%3,%4,%5,%6,%7,%8,%9").arg(item41).arg(item42)
                .arg(QString::number(freqency4)+"Hz").arg(QString::number(level4)+levelUnit4)
                .arg(range4).arg(speed4).arg(equcct4).arg(QString::number(bias4)+biasType4)
                .arg(biasSwitch4);
        labelLCR4->setText(tx);
    }
}

void clsWKEControlBox::on_rbtnHV1_clicked()
{
    clsHightVoltage *dlg=new clsHightVoltage(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        QString volSwitch1=dlg->getVoltageSwitch();
        double voltage1=dlg->getVoltage();
        rbtnHV1->setText(QString::number(voltage1)+"V,"+volSwitch1);
    }
}

void clsWKEControlBox::labelHV2Clicked()
{
    clsHightVoltage *dlg=new clsHightVoltage(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        QString volSwitch2=dlg->getVoltageSwitch();
        double voltage2=dlg->getVoltage();
        labelHV2->setText(QString::number(voltage2)+"V,"+volSwitch2);
    }
}

void clsWKEControlBox::labelHV3Clicked()
{
    clsHightVoltage *dlg=new clsHightVoltage(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        QString volSwitch3=dlg->getVoltageSwitch();
        double voltage3=dlg->getVoltage();
        labelHV3->setText(QString::number(voltage3)+"V,"+volSwitch3);
    }
}

void clsWKEControlBox::labelHV4Clicked()
{
    clsHightVoltage *dlg=new clsHightVoltage(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        QString volSwitch4=dlg->getVoltageSwitch();
        double voltage4=dlg->getVoltage();
        labelHV4->setText(QString::number(voltage4)+"V,"+volSwitch4);
    }
}

void clsWKEControlBox::on_btnOK_clicked()
{
    this->accept();
}

void clsWKEControlBox::on_btnCancel_clicked()
{
    this->reject();
}

void clsWKEControlBox::on_rbtnLCR1_clicked()
{
    clsWK6500Meter *dlg=new clsWK6500Meter;
    if(dlg->exec()==QDialog::Accepted)
    {
        QString condition=dlg->getCondtion();
        lcrCondition.replace(0,condition);
        QVariantMap conditionMap=parseCondition(condition);
        QString item11=conditionMap["item1"].toString();
        QString item12=conditionMap["item2"].toString();
        double freqency1=conditionMap["frequency"].toDouble();
        double level1=conditionMap["level"].toDouble();
        QString levelUnit1=conditionMap["levelUnit"].toString();
        QString range1=conditionMap["range"].toString();
        QString speed1=conditionMap["speed"].toString();
        QString equcct1=conditionMap["equcct"].toString();
        double bias1=conditionMap["bias"].toDouble();
        QString biasType1=conditionMap["biasType"].toString();
        QString biasSwitch1=conditionMap["biasSwitch"].toString();

        QString tx=QString("%1,%2,%3,%4,%5,%6,%7,%8,%9").arg(item11).arg(item12)
                .arg(QString::number(freqency1)+"Hz").arg(QString::number(level1)+levelUnit1)
                .arg(range1).arg(speed1).arg(equcct1).arg(QString::number(bias1)+biasType1)
                .arg(biasSwitch1);
        rbtnLCR1->setText(tx);
    }
}
