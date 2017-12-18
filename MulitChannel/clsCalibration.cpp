#include "clsCalibration.h"
#include "doubleType.h"
#include "clsSampleTest.h"
#include "doubleType.h"
#include "clsDataProcess.h"
#include "clsCalibrationDbOp.h"
#include "NumberInput.h"
#include "clsStandardValueInput.h"
#include "clsSettings.h"
#include <QFileDialog>
#include "MessageDialog.h"
#include "clsFtdiOperation.h"
#include "clsWK6500RunningMode.h"
clsCalibration::clsCalibration(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    ocZ=OR;
    ocA=OR;
    scZ=OR;
    scA=OR;
    loadZ=OR;
    loadA=OR;
    stdA=OR;
    stdZ=OR;

    readSettings();
    //  this->layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void clsCalibration::setMeter(clsInstrumentCalibration *meter)
{
    this->meter = meter;
    meter->setConditionForCalibration(0);
    meter->setFreqencyForCal(0);
    freq = meter->getFreqency(0);
}

void clsCalibration::setSteps(const QList<clsTestConditons *> steps)
{
    this->steps = steps;
    this->channels.clear();
    calFreq.clear();
    for(int i=0; i< steps.length(); i++)
    {
        clsTestConditons * tmpStep = steps.at(i);

        if(tmpStep->meter == "WK6500")
        {
            if(!channels.contains(QString::number(tmpStep->channel)))
            {
                channels.append(QString::number(tmpStep->channel));
                calFreq[tmpStep->channel] =  QList<double>()<< getFreqFromConditon(tmpStep->condition);
            }
            else
            {
                double tmpFreq = getFreqFromConditon(tmpStep->condition);

                if(!calFreq[tmpStep->channel].contains(tmpFreq))
                    calFreq[tmpStep->channel].append(getFreqFromConditon(tmpStep->condition));
            }
        }
    }
}


double clsCalibration::getFreqFromConditon(const QString condition)
{
    double frequency=0;
    QJsonParseError error;
    QJsonDocument jsondocument=QJsonDocument::fromJson(condition.toUtf8(),&error);
    if(error.error!=QJsonParseError::NoError)
        return 0;
    if(jsondocument.isNull() || jsondocument.isEmpty())
        return 0;

    QVariantMap tmpMap = jsondocument.toVariant().toMap();


    QString tmpConditon = tmpMap["conditions"].toString();
    if(tmpConditon.isEmpty())
        return 0;

    jsondocument = QJsonDocument::fromJson(tmpConditon.toUtf8(), &error);
    if(error.error!=QJsonParseError::NoError)
        return 0;
    if(jsondocument.isNull() || jsondocument.isEmpty())
        return 0;

    if(jsondocument.isObject())
    {
        QVariantMap conditionMap=jsondocument.toVariant().toMap();
        frequency=conditionMap["frequency"].toDouble();

    }

    return frequency;
}




/*!
 * \brief 查询数据库中的记录
 * \param freq 频率
 * \param channal 通道
 * \param type 类型
 */
QList<double> clsCalibration::getCalDataFromDb(
        double freq, int channal,QString type)
{
    return clsCalDb::getInst()->getCalData(freq,channal,type);
}

/*!
 * \brief 将校准数据写入数据库
 * \param freq 频率
 * \param channal 通道
 * \param z 阻抗
 * \param a 相位
 * \param type 类型 O 开路 S 短路 Lm负载量测值 Ls负载标准值
 */
void clsCalibration::insertRecord(
        double freq, int channal,
        double z,double a, QString type)
{
    clsCalDb::getInst()->insertRecord(freq,channal,z,a,type);
}



void clsCalibration::on_btnDone_clicked()
{
    saveSettings();
    this->close();
}

void clsCalibration::on_btnCancel_clicked()
{
    saveSettings();
    this->close();
}


void clsCalibration::on_btnOpenTrim_clicked()
{

    QList<int> calChannels = this->getCalChannels();

    meter->setConditionForCalibration(0);
    clsSampleTest * sample = new clsSampleTest(meter,this);
    if(sample->exec() !=QDialog::Accepted)
        return;



    for(int c=0; c< calChannels.length(); c++)
    {
        int currentChannel = calChannels.at(c);
        clsConnectSWBox::Ins()->setChannel(currentChannel);
        clsConnectSWBox::Ins()->turnOffAllLight();
        clsConnectSWBox::Ins()->setOnlyOneOrangeLEDON(currentChannel);

        int res=showCalMessage(tr("开路校准"),currentChannel);
        if(res==QDialog::Rejected)
            return;
        QList<double> calFrequencys =  calFreq[calChannels.at(c)];
        for(int f=0; f<calFrequencys.length(); f++)
        {
            showCalMessage(tr("开路校准"),calFrequencys.at(f),currentChannel);
            meter->setFreqencyForCal((double)calFrequencys.at(f));

            QList<double> resValue = meter->getOriginZA();

            doubleType dt;
            dt.setData(resValue.at(0));
            ocZ = dt.Data();

            dt.setData(resValue.at(1));
            ocA = dt.Data();

            clsCalDb::getInst()->insertRecord(calFrequencys.at(f),currentChannel,
                                              ocZ,ocA,"O");

        }
        // 10kHz 为了高频校准
        meter->set10KHz();
        QList<double> resValue = meter->getOriginZA();

        clsCalDb::getInst()->insertRecord(10000.0,currentChannel,
                                          resValue.at(0),resValue.at(1),"OC_10k");

    }
    setCalLabelInfo(lblOpenTrim,tr("开路校准"));
}

void clsCalibration::on_btnShortTrim_clicked()
{
    QList<int> calChannels = this->getCalChannels();

    meter->setConditionForCalibration(0);

    clsSampleTest * sample = new clsSampleTest(meter,this);
    if(sample->exec() !=QDialog::Accepted)
        return;

    for(int c=0; c< calChannels.length(); c++)
    {
        int currentChannel = calChannels.at(c);
        clsConnectSWBox::Ins()->setChannel(currentChannel);
        clsConnectSWBox::Ins()->turnOffAllLight();
        clsConnectSWBox::Ins()->setOnlyOneOrangeLEDON(currentChannel);

        int res=showCalMessage(tr("短路校准"),currentChannel);
        if(res==QDialog::Rejected)
            return;
        QList<double> calFrequencys =  calFreq[calChannels.at(c)];
        for(int f=0; f<calFrequencys.length(); f++)
        {
            showCalMessage(tr("短路校准"),calFrequencys.at(f),currentChannel);

            meter->setFreqencyForCal((double)calFrequencys.at(f));

            QList<double> resValue = meter->getOriginZA();

            doubleType dt;
            dt.setData(resValue.at(0));
            scZ = dt.Data();

            dt.setData(resValue.at(1));
            scA = dt.Data();

            clsCalDb::getInst()->insertRecord(calFrequencys.at(f),currentChannel,
                                              scZ,scA,"S");

        }

        // 10kHz 为了高频校准
        meter->set10KHz();
        QList<double> resValue = meter->getOriginZA();

        clsCalDb::getInst()->insertRecord(10000.0,currentChannel,
                                          resValue.at(0),resValue.at(1),"SC_10k");
    }
    setCalLabelInfo(lblShortTrim,tr("短路校准"));
}

QList<double> clsCalibration::getCalFrequencys()
{


    if(freqList.empty())
    {
        QList<double> tmp;
        tmp.append(meter->getFreqency(0));
        if(false)
            tmp.append(meter->getFreqency(1));
        return tmp;
    }
    else
    {
        if(!freqList.contains(meter->getFreqency(0)))
            freqList.append(meter->getFreqency(0));
        if(!freqList.contains(meter->getFreqency(1)))
            freqList.append(meter->getFreqency(1));
        qSort(freqList);
        return freqList;
    }

}
QList<int> clsCalibration::getCalChannels()
{
    QList<int> tmp;
    for(int i=0; i< channels.length(); i++)
    {
        if(!channels.at(i).isEmpty())
            tmp.append(channels.at(i).toInt());
    }

    return tmp;
}

int clsCalibration::showCalMessage(QString calType, double calFreq, int channel)
{
    this->lblCalbrationType->setText(calType);
    doubleType dt;
    dt.setData(calFreq,"");
    this->lblCalFrequency->setText(dt.formateToString()+"Hz");
    lblCalChannel->setText(QString::number(channel));
    qApp->processEvents();
    return 0;
}

int clsCalibration::showCalMessage(QString calType, int channel)
{
    MessageDialog *ms = new MessageDialog(this);

    ms->layout()->setSizeConstraint(QLayout::SetFixedSize);
    QString strMessage = tr("<p>现在第<strong><span style=\"font-size:16px;color:#E53333;\">%1</span></strong>通道</p>").arg(channel);
    ms->setMessage(strMessage,calType);
    return ms->exec();
}

void clsCalibration::setCalLabelInfo(QLabel *lbl, QString calType)
{
    lbl->setText(tr("%3时间为：%1 %2").arg(QDate::currentDate().toString("yyyy-M-dd"))
                 .arg(QTime::currentTime().toString("hh:mm:ss"))
                 .arg(calType));
    this->saveSettings();
}



void clsCalibration::readSettings()
{

    clsSettings settings;
    QString strNode ="MulitChannel/";
    QString tmp;
    settings.readSetting(strNode +"Cal-Channel",tmp);
    settings.readSetting(strNode +"OpenTrim", tmp);
    lblOpenTrim->setText(tmp);
    settings.readSetting(strNode + "ShortTrim",tmp);
    lblShortTrim->setText(tmp);

    settings.readSetting(strNode +"HFTrim",tmp);
    lblRCTrime->setText(tmp);

}

void clsCalibration::saveSettings()
{
    clsSettings settings;
    QString strNode ="MulitChannel/";
    settings.writeSetting(strNode +"OpenTrim", lblOpenTrim->text());
    settings.writeSetting(strNode +"ShortTrim",lblShortTrim->text());
    settings.writeSetting(strNode +"HFTrim",lblRCTrime->text());
}




void clsCalibration::on_btnRCLoadCalibration_clicked()
{
    MessageDialog *dlg = new MessageDialog(this);
    dlg->setMessage(tr("确定是否已经做完了开路和短路校准"),tr("阻容校准"));

    if(dlg->exec()!=QDialog::Accepted)
        return;

    dlg->setMessage(tr("放入负载100R"),tr("阻容校准"));
    dlg->exec();
    if(dlg->result()!=QDialog::Accepted)
        return;

     clsSampleTest * sample = new clsSampleTest(meter,this);
    if(sample->exec() !=QDialog::Accepted)
        return;

    QList<int> calChannels = this->getCalChannels();

    for(int c=0; c< calChannels.length(); c++)
    {
        int currentChannel = calChannels.at(c);
        clsConnectSWBox::Ins()->setChannel(currentChannel);
        clsConnectSWBox::Ins()->turnOffAllLight();
        clsConnectSWBox::Ins()->setOnlyOneOrangeLEDON(currentChannel);

        int res1= showCalMessage(tr("100R校准"),currentChannel);
        if(res1==QDialog::Rejected)
            return;
        meter->set10KHz();
        meter->setConditionForCalibration(0);
        QList<double> res = meter->getOriginZA();

        double Zm_100R_10K = res.at(0);
        double A_100R_10k = res.at(1);

        //获取开路和短路值
        //获取开路值
        QList<double> oc_10k = clsCalDb::getInst()->getCalData(10000.0,currentChannel,"OC_10k");
        //获取短路值
        QList<double> sc_10k = clsCalDb::getInst()->getCalData(10000.0,currentChannel,"SC_10k");

        clsDataProcess c100R(Zm_100R_10K,A_100R_10k,10000);
        if((oc_10k.length()==2)&&(sc_10k.length()==2))
        {
            c100R.applyOpenData(oc_10k.at(0),oc_10k.at(1));
            c100R.applyShortData(sc_10k.at(0),sc_10k.at(1));
            c100R.useLoadData(false);
            c100R.doCalibration();
        }

        double z100R = c100R.getItem("Z",tr("串联"));
        double a100R = c100R.getItem("A",tr("串联"));

        clsCalDb::getInst()->insertRecord(10000,currentChannel,z100R,a100R,"HF_100RRef");


        QList<double> calFrequencys =  calFreq[calChannels.at(c)];
        for(int f=0; f<calFrequencys.length(); f++)
        {
            showCalMessage(tr("100R校准"),calFrequencys.at(f),currentChannel);

            meter->setConditionForCalibration(f);
            meter->setFreqencyForCal((double)calFrequencys.at(f));
            QList<double> resValue = meter->getOriginZA();


            clsCalDb::getInst()->insertRecord(calFrequencys.at(f),currentChannel,
                                              resValue.at(0),resValue.at(1),"HF_C100R");

        }
    }
    //100pF校准
    dlg->setMessage(tr("放入负载100pF"),tr("阻容校准"));
    dlg->exec();
    if(dlg->result()!=QDialog::Accepted)
        return;

        meter->setConditionForCalibration(0);
    if(sample->exec() !=QDialog::Accepted) //Sample 检测
        return;

    for(int c=0; c< calChannels.length(); c++)
    {
        int currentChannel = calChannels.at(c);
        clsConnectSWBox::Ins()->setChannel(currentChannel);
        clsConnectSWBox::Ins()->turnOffAllLight();
        clsConnectSWBox::Ins()->setOnlyOneOrangeLEDON(currentChannel);

        showCalMessage(tr("100pF校准"),currentChannel);

        meter->set10KHz();
        meter->setConditionForCalibration(0);
        QList<double> res = meter->getOriginZA();

        double Zm_100P_10K = res.at(0);
        double A_100P_10k = res.at(1);

        //获取开路和短路值
        //获取开路值
        QList<double> oc_10k = clsCalDb::getInst()->getCalData(10000.0,currentChannel,"OC_10k");
        //获取短路值
        QList<double> sc_10k = clsCalDb::getInst()->getCalData(10000.0,currentChannel,"SC_10k");

        clsDataProcess c100P(Zm_100P_10K,A_100P_10k,10000);
        if((oc_10k.length()==2)&&(sc_10k.length()==2))
        {
            c100P.applyOpenData(oc_10k.at(0),oc_10k.at(1));
            c100P.applyShortData(sc_10k.at(0),sc_10k.at(1));
            c100P.useLoadData(false);
            c100P.doCalibration();
        }

        double z100P = c100P.getItem("Z",tr("串联"));
        double a100P = c100P.getItem("A",tr("串联"));

        clsCalDb::getInst()->insertRecord(10000,currentChannel,z100P,a100P,"HF_100PRef");

        QList<double> calFrequencys = getCalFrequencys();
        for(int f=0; f<calFrequencys.length(); f++)
        {
            showCalMessage(tr("100P校准"),calFrequencys.at(f),currentChannel);

            meter->setConditionForCalibration(f);
            meter->setFreqencyForCal((double)calFrequencys.at(f));
            QList<double> resValue = meter->getOriginZA();


            clsCalDb::getInst()->insertRecord(calFrequencys.at(f),currentChannel,
                                              resValue.at(0),resValue.at(1),"HF_C100P");

        }

    }
    setCalLabelInfo(lblRCTrime,tr("阻容校准"));

}

void clsCalibration::on_btnMultiFreq_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("打开频率点数据文件"),"./",tr("CSV 文件(*.csv)"));

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    freqList.clear();
    while (!file.atEnd()) {
        QString line = file.readLine();
        QStringList lineList = line.split(",");
        if(!lineList.isEmpty())
        {
            QString strFreq = lineList.at(0);
            bool ok;

            double freq = strFreq.toDouble(&ok);
            if(ok)
                freqList.append(freq);
        }
    }

    file.close();

    qDebug()<<freqList;
}
