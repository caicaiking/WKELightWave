#include "clsHightVoltage.h"
#include "NumberInput.h"
#include "publicUtility.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include "doubleType.h"
#include "frmSetLimit.h"


clsHightVoltage::clsHightVoltage(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->volSwitch=tr("关");
    this->voltage=100.0;
    this->hiLimit=0.00;
    lowLimit=0.00;
    relaySwitch="开";
    connect(labelLimit,SIGNAL(labelClicked()),this,SLOT(onLabelLimitClicked()));
    updateButtons();
}

QString clsHightVoltage::getVoltageSwitch() const
{
    return this->volSwitch;
}

double clsHightVoltage::getVoltage() const
{
    return this->voltage;
}

QString clsHightVoltage::getCondition() const
{
    QVariantMap conditionMap;
    conditionMap.insert("voltage",this->voltage);
    conditionMap.insert("volSwitch",this->volSwitch);
    conditionMap.insert("relaySwitch",this->relaySwitch);
    conditionMap.insert("hiLimit",this->hiLimit);
    conditionMap.insert("lowLimit",this->lowLimit);
    QJsonDocument jsonDocument=QJsonDocument::fromVariant(conditionMap);
    QString condition;
    if(!(jsonDocument.isNull()))
    {
        condition=jsonDocument.toJson();
    }
    return condition;
}

void clsHightVoltage::setCondition(const QString condition)
{
    QVariantMap conditionMap;
    conditionMap=publicUtility::parseConditions(condition);
    this->voltage=conditionMap["voltage"].toDouble();
    this->volSwitch=conditionMap["volSwitch"].toString();
    this->relaySwitch=conditionMap["relaySwitch"].toString();
    this->hiLimit=conditionMap["hiLimit"].toDouble();
    this->lowLimit=conditionMap["lowLimit"].toDouble();
}

void clsHightVoltage::updateButtons()
{
    btnRelay->setText(relaySwitch);
    btnSwitch->setText(volSwitch);
    doubleType dt;
    dt.setData(voltage,"");
    btnVoltage->setText(dt.formateToString(5)+"V");
    mLimit.setAbsHi(hiLimit);
    mLimit.setAbsLo(lowLimit);
    labelLimit->setText(mLimit.showLimits("Ω"));
}

void clsHightVoltage::updateCommand()
{

}

void clsHightVoltage::on_btnSwitch_clicked()
{
    if(btnSwitch->text()==tr("开"))
    {
        this->volSwitch=tr("关");
        btnSwitch->setText(tr("关"));
    }
    else if(btnSwitch->text()==tr("关"))
    {
        this->volSwitch=tr("开");
        btnSwitch->setText(tr("开"));
    }
}

void clsHightVoltage::on_btnVoltage_clicked()
{
    NumberInput *dlg=new NumberInput(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        doubleType dt;

        voltage=dlg->getNumber();
        dt.setData(voltage,"");
        btnVoltage->setText(dt.formateToString(6)+"V");
    }
}

void clsHightVoltage::on_btnOK_clicked()
{
    //updateCommand();
    this->accept();
}

void clsHightVoltage::on_btnCancel_clicked()
{
    this->reject();
}

void clsHightVoltage::on_btnRelay_clicked()
{
    if(btnRelay->text()==tr("开"))
    {
        relaySwitch="关";
        btnRelay->setText(tr("关"));
    }
    else
    {
        relaySwitch="开";
        btnRelay->setText(tr("开"));
    }
}

void clsHightVoltage::onLabelLimitClicked()
{
    frmSetLimit *dlg=new frmSetLimit(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        mLimit=dlg->getMeterLimit();
        labelLimit->setText(mLimit.showLimits("Ω"));
        hiLimit=mLimit.getAbsLimitHigh();
        lowLimit=mLimit.getAbsLimitLow();
    }
}
