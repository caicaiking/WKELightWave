#include "clsWK6500Meter.h"
#include "doubleType.h"
#include "clsRangeDialog.h"
#include "clsSpeedDialog.h"
#include "clsWK6500Items.h"
#include "NumberInput.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include "frmSetLimit.h"
#include "publicUtility.h"
#include "clsSettings.h"
#include "clsMeterUnit.h"
#include "dlgLevelInputBox.h"

clsWK6500Meter::clsWK6500Meter(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle(tr("设置测试条件"));
    connect(labelLimit1,SIGNAL(labelClicked()),this,SLOT(onLabellimit1Clicked()));
    connect(labelLimit2,SIGNAL(labelClicked()),this,SLOT(onLabellimit2Clicked()));
    QString latestSettings = readSettings();

    if(latestSettings.isEmpty()) //赋值给默认值
    {
        item1="L";
        item2="Q";
        isItem2Enable = true;
        frequency=1000;
        this->level=1;
        range=tr("自动");
        speed=tr("快速");
        equcct="串联";
        bias=0;
        biasA =0;
        biasV=0;
        biasType="V";
        biasSwitch="关";
        levelUnit="V";
        suffix1="H";
        suffix2="Q";
        item1HiLimit=0.00;
        item1LowLimit=0.000;
        item2HiLimit=0.0;
        item2LowLimit=0.0;
        relaySwitch="开";
    }
    else
    {
        setCondition(latestSettings);
    }
    updateButtons();
}


void clsWK6500Meter::updateButtons()
{
    btnItem1->setText(item1);
    btnItem2->setText(item2);

    if(suffix1 != tr("自动"))
        btnItem1Unit->setText(suffix1 + publicUtility::getSuffix(item1));
    else
        btnItem1Unit->setText(suffix1);

    if(suffix2 != tr("自动"))
        btnItem2Unit->setText(suffix2 + publicUtility::getSuffix(item2));
    else
        btnItem2Unit->setText(suffix2);


    grpItem2->setChecked(isItem2Enable);
    doubleType dt;
    dt.setData(frequency,"");
    btnFreq->setText(dt.formateToString(6)+"Hz");
    dt.setData(level,"");
    btnLevel->setText(dt.formateToString(6)+levelUnit);

    QString strUnit;
    if(biasType=="A")
    {
        strUnit="A";
        btnBiasType->setText(tr("电流"));
        bias = biasA;
    }
    else
    {
        strUnit="V";
        btnBiasType->setText(tr("电压"));
        bias = biasV;
    }

    dt.setData(bias,"");
    btnBias->setText(dt.formateToString(6)+strUnit);
    btnBiasSwitch->setText(biasSwitch);
    btnRange->setText(range);
    btnSpeed->setText(speed);
    btnEqucct->setText(equcct);
    mlItem1.setAbsHi(item1HiLimit);
    mlItem1.setAbsLo(item1LowLimit);
    mlItem2.setAbsHi(item2HiLimit);
    mlItem2.setAbsLo(item2LowLimit);
    labelLimit1->setText(mlItem1.showLimits(publicUtility::getSuffix(item1)));
    labelLimit2->setText(mlItem2.showLimits(publicUtility::getSuffix(item2)));
}

void clsWK6500Meter::onLabellimit1Clicked()
{
    frmSetLimit *frm=new frmSetLimit(this);
    frm->setItem(this->item1);
    frm->setLimits(mlItem1);
    if(frm->exec()==QDialog::Accepted)
    {
        mlItem1= frm->getMeterLimit();
        labelLimit1->setText(mlItem1.showLimits(publicUtility::getSuffix(item1)));
        item1HiLimit=mlItem1.getAbsLimitHigh();
        item1LowLimit=mlItem1.getAbsLimitLow();
    }
}

void clsWK6500Meter::onLabellimit2Clicked()
{
    frmSetLimit *frm=new frmSetLimit(this);
    frm->setItem(this->item2);
    frm->setLimits(mlItem2);
    if(frm->exec()==QDialog::Accepted)
    {
        mlItem2= frm->getMeterLimit();
        labelLimit2->setText(mlItem2.showLimits(publicUtility::getSuffix(item2)));
        item2HiLimit=mlItem2.getAbsLimitHigh();
        item2LowLimit=mlItem2.getAbsLimitLow();
    }
}

QString clsWK6500Meter::getCondition() const
{
    QVariantMap condition;

    condition.insert("item1",this->item1);
    condition.insert("item2",this->item2);
    condition.insert("isItem2Enable",this->isItem2Enable);
    condition.insert("frequency",this->frequency);
    condition.insert("level",this->level);
    condition.insert("levelUnit",levelUnit);
    condition.insert("range",this->range);
    condition.insert("speed",this->speed);
    condition.insert("equcct",this->equcct);
    condition.insert("bias",this->bias);
    condition.insert("biasA",this->biasA);
    condition.insert("biasV",this->biasV);
    condition.insert("biasSwitch",this->biasSwitch);
    condition.insert("biasType",this->biasType);
    condition.insert("relaySwitch",this->relaySwitch);
    condition.insert("item1HiLimit",this->item1HiLimit);
    condition.insert("item1LowLimit",this->item1LowLimit);
    condition.insert("item2HiLimit",this->item2HiLimit);
    condition.insert("item2LowLimit",this->item2LowLimit);
    condition.insert("suffix1",this->suffix1);
    condition.insert("suffix2",this->suffix2);

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
                this->isItem2Enable = conditionMap["isItem2Enable"].toBool();
                this->frequency=conditionMap["frequency"].toDouble();
                this->level=conditionMap["level"].toDouble();
                this->levelUnit=conditionMap["levelUnit"].toString();
                this->range=conditionMap["range"].toString();
                this->speed=conditionMap["speed"].toString();
                this->equcct=conditionMap["equcct"].toString();
                this->bias=conditionMap["bias"].toDouble();
                this->biasA=conditionMap["biasA"].toDouble();
                this->biasV=conditionMap["biasV"].toDouble();
                this->biasSwitch=conditionMap["biasSwitch"].toString();
                this->biasType=conditionMap["biasType"].toString();
                this->relaySwitch=conditionMap["relaySwitch"].toString();
                this->item1HiLimit=conditionMap["item1HiLimit"].toDouble();
                this->item1LowLimit=conditionMap["item1LowLimit"].toDouble();
                this->item2HiLimit=conditionMap["item2HiLimit"].toDouble();
                this->item2LowLimit=conditionMap["item2LowLimit"].toDouble();
                this->suffix1=conditionMap["suffix1"].toString();
                this->suffix2=conditionMap["suffix2"].toString();
            }
        }
    }
    updateButtons();
}

void clsWK6500Meter::on_btnFreq_clicked()
{
    NumberInput *dlg=new NumberInput(this);
    dlg->setWindowTitle(tr("设置频率"));
    if(dlg->exec()==QDialog::Accepted)
    {
        doubleType dt;
        frequency=dlg->getNumber();

        frequency = limitCheck(frequency,120E6,20);
        updateButtons();

    }
}

void clsWK6500Meter::on_btnOK_clicked()
{
    //updateCommand();
    isItem2Enable = grpItem2->isChecked();

    saveSettings();
    this->accept();
}

void clsWK6500Meter::on_btnLevel_clicked()
{
    dlgLevelInputBox *dlg=new dlgLevelInputBox(this);
    dlg->setWindowTitle(tr("设置电平"));
    if(dlg->exec()==QDialog::Accepted)
    {
        doubleType dt;
        level=dlg->getNumber();
        levelUnit=dlg->getUnit();

        if(levelUnit == "A")
            level = limitCheck(level, 20E-3, 200E-6);
        else
            level = limitCheck(level, 1, 10E-3);


        updateButtons();
    }
}

void clsWK6500Meter::on_btnEqucct_clicked()
{
    if(btnEqucct->text()==tr("串联"))
    {
        equcct=tr("并联");
        btnEqucct->setText(tr("并联"));
    }
    else if(btnEqucct->text()==tr("并联"))
    {
        equcct=tr("串联");
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
    if(btnBiasType->text()==tr("电流"))
    {
        biasType="V";
        btnBiasType->setText(tr("电压"));
    }
    else if(btnBiasType->text()==tr("电压"))
    {
        biasType="A";
        btnBiasType->setText(tr("电流"));
    }
    updateButtons();
}

void clsWK6500Meter::on_btnBiasSwitch_clicked()
{
    if(btnBiasSwitch->text()=="开")
    {
        biasSwitch="关";
        btnBiasSwitch->setText(tr("关"));
    }
    else if(btnBiasSwitch->text()=="关")
    {
        biasSwitch="开";
        btnBiasSwitch->setText(tr("开"));
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
        relaySwitch="关";
        btnRelay->setText(tr("关"));
    }
    else if(btnRelay->text()==tr("关"))
    {
        relaySwitch="开";
        btnRelay->setText(tr("开"));
    }
}

void clsWK6500Meter::on_btnBias_clicked()
{
    NumberInput *dlg=new NumberInput(this);
    dlg->setWindowTitle(tr("输入数值"));
    if(dlg->exec()==QDialog::Accepted)
    {
        bias=dlg->getNumber();
        if(biasType == "V")
        {
            bias = limitCheck(bias,40,-40);
            biasV = bias;
        }
        else
        {
            bias = limitCheck(bias,100E-3, 0);
            biasA = bias;
        }

        updateButtons();
    }
}

QString clsWK6500Meter::readSettings()
{
    clsSettings settings;
    QString strTmp;
    QString strNode = "WK6500/";
    settings.readSetting(strNode + "latestSettings", strTmp);
    return strTmp;
}

void clsWK6500Meter::saveSettings()
{
    clsSettings settings;

    QString strNode = "WK6500/";
    settings.writeSetting(strNode + "latestSettings", this->getCondition());
}

void clsWK6500Meter::on_btnItem2Unit_clicked()
{
    clsMeterUnit *dlg = new clsMeterUnit(this);

    dlg->setWindowTitle(tr("选择后缀"));
    dlg->setItem(item2);
    dlg->setAutoEnable(true);

    if(dlg->exec()==QDialog::Accepted)
    {
        suffix2 = dlg->getSuffix();
    }

    updateButtons();

}

void clsWK6500Meter::on_btnItem1Unit_clicked()
{
    clsMeterUnit *dlg = new clsMeterUnit(this);

    dlg->setWindowTitle(tr("选择后缀"));
    dlg->setItem(item1);
    dlg->setAutoEnable(true);

    if(dlg->exec()==QDialog::Accepted)
    {
        suffix1 = dlg->getSuffix();
    }

    updateButtons();
}

void clsWK6500Meter::on_btnItem1_clicked()
{
    clsWK6500Items *dlg = new clsWK6500Items(this);
    dlg->setWindowTitle(tr("设置Item1"));
    if(dlg->exec()==QDialog::Accepted)
    {
        item1 = dlg->getFunc();
    }
    updateButtons();
}

void clsWK6500Meter::on_btnItem2_clicked()
{
    clsWK6500Items *dlg = new clsWK6500Items(this);
    dlg->setWindowTitle(tr("设置Item2"));
    if(dlg->exec()==QDialog::Accepted)
    {
        item2 = dlg->getFunc();
    }
    updateButtons();
}

void clsWK6500Meter::on_grpItem2_clicked(bool checked)
{
    this->isItem2Enable = checked;
    updateButtons();
}

double clsWK6500Meter::limitCheck(double value, const double max, const double min)
{
    if(value < min)
        value = min;
    if(value > max)
        value = max;
    return value;
}
