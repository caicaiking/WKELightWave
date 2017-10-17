#include "clsWK6500Meter.h"
#include "doubleType.h"
#include "clsRangeDialog.h"
#include "clsSpeedDialog.h"
#include "clsWK6500Items.h"
#include "NumberInput.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include "frmSetLimit.h"



clsWK6500Meter::clsWK6500Meter(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->setWindowTitle(tr("设置测试条件"));
    item1="L";
    item2="Q";
    frequency=1000;
    this->level=1;
    range="AUTO";
    speed="FAST";
    equcct="串联";
    bias=0;
    biasType="V";
    biasSwitch="OFF";
    levelUnit="V";
    groupBoxBias->setEnabled(false);

    connect(labelLimit1,SIGNAL(labelClicked()),this,SLOT(onLabellimit1Clicked()));
    connect(labelLimit2,SIGNAL(labelClicked()),this,SLOT(onLabellimit2Clicked()));
}


void clsWK6500Meter::updateButtons()
{
    btnItem1->setText(item1);
    btnItem2->setText(item2);
    doubleType dt;
    dt.setData(frequency,"");
    btnFreq->setText(dt.formateToString(6)+"Hz");
    dt.setData(level,"");
    btnLevel->setText(dt.formateToString(6)+levelUnit);
    dt.setData(bias,"");
    QString strUnit;
    if(biasType=="CUR")
        strUnit="A";
    else if(biasType=="VOL")
        strUnit="V";
    btnBias->setText(dt.formateToString(6)+strUnit);
    btnBiasSwitch->setText(biasSwitch);
    btnBiasType->setText(biasType);
    btnRange->setText(range);
    btnSpeed->setText(speed);
    if(equcct=="SER")
        btnEqucct->setText(tr("串联"));
    else if(equcct=="PAR")
        btnEqucct->setText(tr("并联"));
}

void clsWK6500Meter::updateCommand()
{

    QString cmd=QString(":METER:FUNC:1 %1;2 %2").arg(item1).arg(item2);
//    clsSingleton::getInstance()->sendCommand(cmd,false);
//    clsSingleton::getInstance()->sendCommand(":METER:FREQ "+QString::number(frequency.at(0)),false);
//    clsSingleton::getInstance()->sendCommand(":METER:LEVEL "+QString::number(level.at(0))+unit.at(0),false);
//    clsSingleton::getInstance()->sendCommand(":METER:SPEED "+speed.at(0),false);
//    clsSingleton::getInstance()->sendCommand(":METER:RANGE "+range.at(0),false);
//    clsSingleton::getInstance()->sendCommand(":METER:EQU-CCT "+equcct.at(0),false);
}

void clsWK6500Meter::turnOffDisplay()
{
//    clsSingleton::getInstance()->sendCommand(QString(":METER:FAST-GPIB ON"),false);
}

void clsWK6500Meter::turnOnDisplay()
{
    //    clsSingleton::getInstance()->sendCommand(QString(":METER:FAST-GPIB OFF"),false);
}

QStringList clsWK6500Meter::setCmbSuffix(int i)
{
    QStringList suffixList;
    suffixList.clear();
    switch (i) {
    case 0:
        suffixList<<" F"<<"mF"<<"uF"<<"nF"<<"pF";
        break;
    case 1:
        suffixList<<" D";
        break;
    case 2:
        suffixList<<" H"<<"mH"<<"uH"<<"nH";
        break;
    case 3:
        suffixList<<" Q";
        break;
    case 4:
        suffixList<<"MΩ"<<"kΩ"<<" Ω"<<"mΩ";
        break;
    case 5:
        suffixList<<"MΩ"<<"kΩ"<<" Ω"<<"mΩ";
        break;
    case 6:
        suffixList<<" S"<<"mS"<<"uS"<<"nS";
        break;
    case 7:
        suffixList<<" S"<<"mS"<<"uS"<<"nS";
        break;
    case 8:
        suffixList<<"MΩ"<<"kΩ"<<" Ω"<<"mΩ";
        break;
    case 9:
        suffixList<<" °";
        break;
    case 10:
        suffixList<<" S"<<"mS"<<"uS"<<"nS";
        break;
    case 11:
        suffixList<<" ";
        break;
    default:
        break;
    }
    return suffixList;
}

void clsWK6500Meter::onLabellimit1Clicked()
{
    frmSetLimit *frm=new frmSetLimit(this);
    if(frm->exec()==QDialog::Accepted)
    {
        mlItem1= frm->getMeterLimit();
        //labelLimit1->setText(mlItem1.showLimits(UserfulFunctions::getSuffix(item1)));
        //labelLimit2->setText(mlItem2.showLimits(UserfulFunctions::getSuffix(item2)));

    }
}

void clsWK6500Meter::onLabellimit2Clicked()
{
    frmSetLimit *frm=new frmSetLimit(this);
    if(frm->exec()==QDialog::Accepted)
    {
        mlItem2= frm->getMeterLimit();
        //labelLimit1->setText(mlItem1.showLimits(UserfulFunctions::getSuffix(item1)));
        //labelLimit2->setText(mlItem2.showLimits(UserfulFunctions::getSuffix(item2)));
    }
}

QString clsWK6500Meter::trig() const
{
    QString strRes;
//    strRes=clsSingleton::getInstance()->sendCommand(":METER:TRIG",true);
    return strRes;
}

QString clsWK6500Meter::getCondtion() const
{
    QVariantMap condition;

    condition.insert("item1",this->item1);
    condition.insert("item2",this->item2);
    condition.insert("frequency",this->frequency);
    condition.insert("level",this->level);
    condition.insert("levelUnit",levelUnit);
    condition.insert("range",this->range);
    condition.insert("speed",this->speed);
    condition.insert("equcct",this->equcct);
    condition.insert("bias",this->bias);
    condition.insert("biasSwitch",this->biasSwitch);
    condition.insert("biasType",this->biasType);
    condition.insert("relaySwitch",this->relaySwitch);



    QJsonDocument jsonDocument=QJsonDocument::fromVariant(condition);
    if(!jsonDocument.isNull())
    {
        return jsonDocument.toJson();
    }
    else
        return "";
}

void clsWK6500Meter::setCondition(const QString condition)
{
    QJsonParseError error;
    QJsonDocument jsondocument=QJsonDocument::fromJson(condition.toUtf8(),&error);
    if(error.error==QJsonParseError::NoError)
    {
        if(!(jsondocument.isNull() || jsondocument.isEmpty()))
        {
            if(jsondocument.isObject())
            {
                QVariantMap conditionMap=jsondocument.toVariant().toMap();
                this->item1=conditionMap["item1"].toString();
                this->item2=conditionMap["item2"].toString();
                this->frequency=conditionMap["frequency"].toDouble();
                this->level=conditionMap["level"].toDouble();
                this->levelUnit=conditionMap["levelUnit"].toString();
                this->range=conditionMap["range"].toString();
                this->speed=conditionMap["speed"].toString();
                this->equcct=conditionMap["equcct"].toString();
                this->bias=conditionMap["bias"].toDouble();
                this->biasSwitch=conditionMap["biasSwitch"].toString();
                this->biasType=conditionMap["biasType"].toString();
                this->relaySwitch=conditionMap["relaySwitch"].toString();

            }
        }
    }
}

void clsWK6500Meter::on_btnItem1_clicked()
{
    clsWK6500Items *dlg=new clsWK6500Items(this);
    dlg->setWindowTitle(tr("设置项目"));
    if(dlg->exec()==QDialog::Accepted)
    {
        item1=dlg->getFunc();
        item1Index=dlg->getIndex();
        cmbItem1->addItems(setCmbSuffix(item1Index));
        btnItem1->setText(item1);
    }
}

void clsWK6500Meter::on_btnItem2_clicked()
{
    clsWK6500Items *dlg=new clsWK6500Items(this);
    dlg->setWindowTitle(tr("设置项目"));
    if(dlg->exec()==QDialog::Accepted)
    {
        item2=dlg->getFunc();
        item2Index=dlg->getIndex();
        cmbItem2->addItems(setCmbSuffix(item2Index));
        btnItem2->setText(item2);
    }
}

void clsWK6500Meter::on_btnFreq_clicked()
{
    NumberInput *dlg=new NumberInput(this);
    dlg->setWindowTitle(tr("设置频率"));
    if(dlg->exec()==QDialog::Accepted)
    {
        doubleType dt;
        frequency=dlg->getNumber();

        dt.setData(frequency,"");
        QString str=dt.formateToString(6);
        btnFreq->setText(str+"Hz");
    }
}

void clsWK6500Meter::on_btnOK_clicked()
{
    //updateCommand();
    this->accept();
}

void clsWK6500Meter::on_btnLevel_clicked()
{
    NumberInput *dlg=new NumberInput(this);
    dlg->setWindowTitle(tr("设置电平"));
    if(dlg->exec()==QDialog::Accepted)
    {
        doubleType dt;
        level=dlg->getNumber();
        levelUnit=dlg->getUnit();

        dt.setData(level,"");
        QString str=dt.formateToString(6);
        btnLevel->setText(str+levelUnit);
    }
}

void clsWK6500Meter::on_btnEqucct_clicked()
{
    if(btnEqucct->text()==tr("串联"))
    {
        equcct="PAR";
        btnEqucct->setText(tr("并联"));
    }
    else if(btnEqucct->text()==tr("并联"))
    {
        equcct="SER";
        btnEqucct->setText(tr("串联"));
    }
}

void clsWK6500Meter::on_btnRange_clicked()
{
    clsRangeDialog *dlg=new clsRangeDialog;
    dlg->setWindowTitle(tr("设置档位"));
    if(dlg->exec()==QDialog::Accepted)
    {
        range=dlg->getRange();
        btnRange->setText(range);
    }
}

void clsWK6500Meter::on_btnSpeed_clicked()
{
    clsSpeedDialog *dlg=new clsSpeedDialog;
    dlg->setWindowTitle(tr("设置速度"));
    if(dlg->exec()==QDialog::Accepted)
    {
        speed=dlg->getSpeed();
        btnSpeed->setText(speed);
    }
}

void clsWK6500Meter::on_btnBiasType_clicked()
{
    if(btnBiasType->text()=="电流")
    {
        biasType="VOL";
        btnBiasType->setText(tr("电压"));
    }
    else if(btnBiasType->text()=="电压")
    {
        biasType="CUR";
        btnBiasType->setText(tr("电流"));
    }
}

void clsWK6500Meter::on_btnBiasSwitch_clicked()
{
    if(btnBiasSwitch->text()=="ON")
    {
        biasSwitch="OFF";
        btnBiasSwitch->setText(tr("OFF"));
    }
    else if(btnBiasSwitch->text()=="OFF")
    {
        biasSwitch="ON";
        btnBiasSwitch->setText(tr("ON"));
    }
}

void clsWK6500Meter::on_btnCancel_clicked()
{
    this->reject();
}

void clsWK6500Meter::on_btnRelay_clicked()
{
    if(btnRelay->text()==tr("开"))
    {
        relaySwitch="OFF";
        btnRelay->setText(tr("关"));
    }
    else if(btnRelay->text()==tr("关"))
    {
        relaySwitch="ON";
        btnRelay->setText(tr("开"));
    }
}
