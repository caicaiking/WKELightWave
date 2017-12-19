#include "clsHVChannelSettings.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include "publicUtility.h"
#include "doubleType.h"
#include "doubleType.h"
#include "publicUtility.h"
#include "clsRunService.h"
clsHVChannelSettings::clsHVChannelSettings(clsMeter *parent) :
    clsMeter(parent)
{
    setupUi(this);

    isEditMode = true;
    connect(labelClose,SIGNAL(labelClicked()),this,SLOT(onCloseLabelClicked()));
    connect(labelChannel,SIGNAL(labelClicked()),this,SLOT(onChannelLabelClicked()));
    connect(sngRunService::Ins(),&clsRunService::currentStep,this,&clsHVChannelSettings::showTrigStar);
    this->lblTrigStar->setText(" ");
    isEditMode = true;
}

void clsHVChannelSettings::setCondition(const QString condition)
{
    this->condition=condition;
    QJsonParseError error;
    QJsonDocument jsonDocument=QJsonDocument::fromJson(this->condition.toUtf8(),&error);
    if(error.error==QJsonParseError::NoError)
    {
        if(!(jsonDocument.isEmpty() || jsonDocument.isEmpty()))
        {
            if(jsonDocument.isObject())
            {
                QVariantMap conditionMap=jsonDocument.toVariant().toMap();
                this->item = conditionMap["item"].toString();
                this->suffix = conditionMap["suffix"].toString();
                this->hiLimit = conditionMap["hiLimit"].toDouble();
                this->lowLimit = conditionMap["lowLimit"].toDouble();
                this->voltage = conditionMap["voltage"].toDouble();
                this->relaySwitch = conditionMap["relaySwitch"].toString();
                this->dblRampUp = conditionMap["dblRampUp"].toDouble();
                this->dblDelay = conditionMap["dblDelay"].toDouble();
                this->dblRampDown = conditionMap["dblRampDown"].toDouble();
            }
        }
    }
}

void clsHVChannelSettings::setChannel(const int channel)
{
    this->channel=channel;
}

void clsHVChannelSettings::updateLabels()
{
    QStringList colorList;
    colorList<<"#D891EF"<<"#FFBF00"<<"#00FFFF"<<"#FDEE00"<<"#D0FF14"<<"#D19FE8"
            <<"#FA6E79"<<"#FE6F5E"<<"#ACE5EE"<<"#66FF00"<<"#FF007F"<<"#84DE02"<<"#1F75FE"
           <<"#08E8DE"<<"#FFAA1D"<<"#FF55A3"<<"#FF033E"<<"#FF2052"<<"#E0218A"<<"#ACE5EE";

    int colorIndex =(channel-1) % colorList.length();
    this->setStyleSheet(QString("QDialog{background-color:%1;border:2px solid %2;border-radius: 9px;}")
                        .arg(colorList.at(colorIndex)).arg(colorList.at(colorIndex)));

    //labelChannel->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelChannel->setText(QString::number(channel));

    lblTrigStar->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelChannel1->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelItem->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelItem->setFont(QFont("楷体",17));
    labelItem11->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelItem11->setText(this->item);
    labelItem11->setFont(QFont("楷体",18));

    labelLimit1->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelLimit1->setFont(QFont("楷体",13));
    labelLimit11->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelLimit11->setFont(QFont("楷体",13));


    labelRelay->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelRelay->setFont(QFont("楷体",13));
    labelRelayRes->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelRelayRes->setFont(QFont("楷体",13));

    labelVoltage->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelVoltage->setFont(QFont("楷体",13));
    labelVoltageRes->setStyleSheet(QString("background-color:%1").arg(colorList.at(colorIndex)));
    labelResItem1->setText(this->item);

    doubleType dt;
    QString strHiLimit;
    QString strLowLimit;
    if(this->suffix == tr("自动"))
    {
        dt.setData(hiLimit);
        strHiLimit = dt.formateToString(6) + publicUtility::getSuffix(item);
        dt.setData(lowLimit);
        strLowLimit= dt.formateToString(6) + publicUtility::getSuffix(item);
        this->labelLimit11->setText(strLowLimit + "--" + strHiLimit);
    }
    else
    {
        dt.setData(hiLimit);
        strHiLimit = dt.formateWithUnit(this->suffix,6) +this->suffix+ publicUtility::getSuffix(item);
        dt.setData(lowLimit);
        strLowLimit= dt.formateWithUnit(this->suffix,6) + this->suffix+ publicUtility::getSuffix(item);
        this->labelLimit11->setText(strLowLimit + "--" + strHiLimit);

    }

    QString strRampUp, strDelay, strRampDown;
    dt.setData(dblRampUp);
    strRampUp = dt.formateToString(5) + "s";
    dt.setData(dblDelay);
    strDelay = dt.formateToString(5) + "s";
    dt.setData(dblRampDown);
    strRampDown = dt.formateToString(5) + "s";

    dt.setData(this->voltage);

    this->labelVoltageRes->setText(dt.formateToString(6) + "V" + '\n' + strRampUp + " " + strDelay + " " + strRampDown);

    labelRelayRes->setText(relaySwitch);

}

void clsHVChannelSettings::setChannelSettings()
{
    setLablChannelToolTip();
    stackedWidget->setCurrentIndex(0);
    isEditMode = true;
    labelClose->setVisible(true);
}

void clsHVChannelSettings::setChannelRunnings()
{
    setLablChannelToolTip();
    stackedWidget->setCurrentIndex(1);
    isEditMode = false;
    labelClose->setVisible(false);
}

void clsHVChannelSettings::setCloseEnabled(const bool bl)
{
    if(bl)
        labelClose->setEnabled(true);
    else
        labelClose->setEnabled(false);
}

void clsHVChannelSettings::updateRes(const QString res)
{
    QVariantMap resMap;
    QVariantList resList;
    doubleType dt;

    QString item;
    bool resStatus;
    double result;
    QString resUnit;

    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(res.toUtf8(), &error);

    if(error.error != QJsonParseError::NoError)
        return;

    if(jsonDocument.isEmpty() || jsonDocument.isNull())
        return;

    resMap = jsonDocument.toVariant().toMap();

    if(resMap["channel"].toInt() != this->channel)
        return ;

    resList = resMap["data"].toList();
    if(resList.length()>=1)
    {
        QVariantMap tmpMap = resList.at(0).toMap();
        item = tmpMap["item"].toString();
        resStatus = tmpMap["status"].toBool();
        result = tmpMap["result"].toDouble();
        resUnit = tmpMap["suffix"].toString();

        dt.setData(result);
        if(resUnit != tr("自动"))
            labelRes1->setText(dt.formateWithUnit(resUnit,7)+ resUnit + publicUtility::getSuffix(item));
        else
            labelRes1->setText(dt.formateToString(7)+ publicUtility::getSuffix(item));

        if(resStatus)
            labelResStatus1->setPixmap(QPixmap(":/dotGreen.png"));
        else
            labelResStatus1->setPixmap(QPixmap(":/dotRed.png"));
    }

    this->lblTrigStar->setText(" ");
}

void clsHVChannelSettings::setStep(int i)
{
    labelChannel1->setText("s"+QString::number(i+1)+"\n"+"HVMeter");
    intStep =i;
}

int clsHVChannelSettings::getStep() const
{
    return intStep;
}

void clsHVChannelSettings::onCloseLabelClicked()
{
    emit deleteChannelSettings(intStep);
}

void clsHVChannelSettings::onChannelLabelClicked()
{
    if(isEditMode)
    {
        emit editStep(this->intStep);
    }
    else
    {
        int tabs = stackedWidget->count();

        int nextPageIndex = stackedWidget->currentIndex()+1;
        stackedWidget->setCurrentIndex(nextPageIndex % tabs);
    }
}

void clsHVChannelSettings::setLablChannelToolTip()
{
   if(isEditMode)
       this->labelChannel->setToolTip(tr("点我修改参数"));
   else
       this->labelChannel->setToolTip(tr("点击我切换显示"));
}

void clsHVChannelSettings::showTrigStar(int i)
{
    if(i == intStep)
        lblTrigStar->setText("*");
    else
        lblTrigStar->setText(" ");
}
