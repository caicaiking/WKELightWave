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
#include "clsTestConditon.h"
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
    this->btnMultiFreq->setVisible(false);
}

void clsCalibration::setMeter(clsInstrumentCalibration *meter)
{
    this->meter = meter;
    meter->setFreqencyForCal(0);
    meter->setConditionForCalibration(0);
    freq = meter->getFreqency(0);
}

void clsCalibration::setSteps(const QList<clsTestConditons *> steps)
{
    this->steps = steps;
    this->channels.clear();
    for(int i=0; i< steps.length(); i++)
    {
        clsTestConditons * tmpStep = steps.at(i);

        if(tmpStep->meter == "WK6500")
        {
            QPoint channel = tmpStep->channel;

            Parameters tmpPar = getParametersFromConditon(tmpStep->condition);
            tmpPar.channel = channel;
            channels.append(tmpPar);
        }
    }
}

QString clsCalibration::ps(QPoint p)
{
    return QString("%1-%2").arg(p.x()).arg(p.y());
}

bool clsCalibration::getSwitchStatusFromCondition(const QString condition)
{

    bool switchStatus=true;
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
        switchStatus=conditionMap["relaySwitch"].toString()==tr("开");

    }

    return switchStatus;
}

clsCalibration::Parameters clsCalibration::getParametersFromConditon(const QString condition)
{
    Parameters par;
    par.isUsable = false;
    QJsonParseError error;
    QJsonDocument jsondocument=QJsonDocument::fromJson(condition.toUtf8(),&error);
    if(error.error!=QJsonParseError::NoError)
        return par;
    if(jsondocument.isNull() || jsondocument.isEmpty())
        return par;

    QVariantMap tmpMap = jsondocument.toVariant().toMap();


    QString tmpConditon = tmpMap["conditions"].toString();
    if(tmpConditon.isEmpty())
        return par;

    jsondocument = QJsonDocument::fromJson(tmpConditon.toUtf8(), &error);
    if(error.error!=QJsonParseError::NoError)
        return par;
    if(jsondocument.isNull() || jsondocument.isEmpty())
        return par;

    if(jsondocument.isObject())
    {
        QVariantMap conditionMap=jsondocument.toVariant().toMap();
        par.freqnecy=conditionMap["frequency"].toDouble();
        par.switchStatus = conditionMap["relaySwitch"].toString()==tr("关");
        par.isUsable = true;
    }

    return par;
}




/*!
 * \brief 查询数据库中的记录
 * \param freq 频率
 * \param channal 通道
 * \param type 类型
 */
QList<double> clsCalibration::getCalDataFromDb(
        double freq, QPoint channal,QString type)
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
        double freq, QPoint channal,
        double z,double a, QString type)
{
    clsCalDb::getInst()->insertRecord(freq,channal,z,a,type);
}



void clsCalibration::on_btnDone_clicked()
{
    saveSettings();
    this->close();
}


void clsCalibration::on_btnOpenTrim_clicked()
{


    meter->setConditionForCalibration(0);
    clsSampleTest * sample = new clsSampleTest(meter,this);

    for(int c=0; c< channels.length(); c++)
    {

        Parameters tmpPar = channels.at(c);
        if(tmpPar.isUsable)
        {

            QPoint currentChannel = tmpPar.channel;
            clsConnectSWBox::Ins()->setChannel(currentChannel,"WK6500");
            clsConnectSWBox::Ins()->setRelay(tmpPar.switchStatus);

            sample->setOption(0);
            if(sample->exec() !=QDialog::Accepted)
                return;

            int res=showCalMessage(tr("开路校准"),currentChannel);
            if(res==QDialog::Rejected)
                return;

            showCalMessage(tr("开路校准"),tmpPar.freqnecy,currentChannel);
            meter->setFreqencyForCal((double)tmpPar.freqnecy);

            QList<double> resValue = meter->getOriginZA();

            doubleType dt;
            dt.setData(resValue.at(0));
            ocZ = dt.Data();

            dt.setData(resValue.at(1));
            ocA = dt.Data();

            clsCalDb::getInst()->insertRecord(tmpPar.freqnecy,currentChannel,
                                              ocZ,ocA,"O");

            // 10kHz 为了高频校准
            meter->set10KHz();
            resValue = meter->getOriginZA();

            clsCalDb::getInst()->insertRecord(10000.0,currentChannel,
                                              resValue.at(0),resValue.at(1),"OC_10k");
        }
    }
    setCalLabelInfo(lblOpenTrim,tr("开路校准"));
}

void clsCalibration::on_btnShortTrim_clicked()
{

    meter->setConditionForCalibration(0);

    clsSampleTest * sample = new clsSampleTest(meter,this);
    for(int c=0; c< channels.length(); c++)
    {

        Parameters par = channels.at(c);
        if(par.isUsable)
        {
            QPoint currentChannel = channels.at(c).channel;

            clsConnectSWBox::Ins()->setChannel(currentChannel,"WK6500");
            clsConnectSWBox::Ins()->setRelay(par.switchStatus);

            sample->setOption(1);
            if(sample->exec() !=QDialog::Accepted)
                return;

            int res=showCalMessage(tr("短路校准"),currentChannel);
            if(res==QDialog::Rejected)
                return;
            showCalMessage(tr("短路校准"),par.freqnecy,currentChannel);

            meter->setFreqencyForCal((double)par.freqnecy);

            QList<double> resValue = meter->getOriginZA();

            doubleType dt;
            dt.setData(resValue.at(0));
            scZ = dt.Data();

            dt.setData(resValue.at(1));
            scA = dt.Data();

            clsCalDb::getInst()->insertRecord(par.freqnecy,currentChannel,
                                              scZ,scA,"S");


            // 10kHz 为了高频校准
            meter->set10KHz();
            resValue = meter->getOriginZA();

            clsCalDb::getInst()->insertRecord(10000.0,currentChannel,
                                              resValue.at(0),resValue.at(1),"SC_10k");
        }
    }
    setCalLabelInfo(lblShortTrim,tr("短路校准"));
}


int clsCalibration::showCalMessage(QString calType, double calFreq, QPoint channel)
{
    this->lblCalbrationType->setText(calType);
    doubleType dt;
    dt.setData(calFreq,"");
    this->lblCalFrequency->setText(dt.formateToString()+"Hz");
    lblCalChannel->setText(QString("%1-%2").arg(channel.x()).arg(channel.y()));
    qApp->processEvents();
    return 0;
}

int clsCalibration::showCalMessage(QString calType, QPoint channel)
{
    MessageDialog *ms = new MessageDialog(this);

    ms->layout()->setSizeConstraint(QLayout::SetFixedSize);
    QString strMessage = tr("<p>现在第<strong><span style=\"font-size:16px;color:#E53333;\">%1-%2</span></strong>通道</p>").arg(channel.x()).arg(channel.y());
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

    settings.readSetting(strNode +"GoldenTrim",tmp);
    this->lblGoldenSample->setText(tmp);

}

void clsCalibration::saveSettings()
{
    clsSettings settings;
    QString strNode ="MulitChannel/";
    settings.writeSetting(strNode +"OpenTrim", lblOpenTrim->text());
    settings.writeSetting(strNode +"ShortTrim",lblShortTrim->text());
    settings.writeSetting(strNode +"GoldenTrim",lblGoldenSample->text());
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

void clsCalibration::on_btnClearCalData_clicked()
{
    clsCalDb::getInst()->removeAllData();
    lblOpenTrim->setText(tr("没有校准数据"));
    lblShortTrim->setText(tr("没有校准数据"));
    lblGoldenSample->setText(tr("没有校准数据"));
}

void clsCalibration::on_btnGoldenCalibrate_clicked()
{
    MessageDialog *dlg = new MessageDialog(this);
    dlg->setMessage(tr("确定是否已经做完了开路和短路校准"),tr("负载校准"));

    if(dlg->exec()!=QDialog::Accepted)
        return;

    for(int x =0; x<channels.length(); x++)
    {
        Parameters tmpPar = channels.at(x);
        if(tmpPar.isUsable)
        {
            clsStandardValueInput * dlg = new clsStandardValueInput(this);
            doubleType dt;
            dt.setData(tmpPar.freqnecy);
            dlg->setWindowTitle(tr("通道%2, 频率%1的标准负载值").arg(dt.formateToString()+"Hz").arg(ps(tmpPar.channel)));
            dlg->setFrequency(tmpPar.freqnecy);

            QList<double> resValue=meter->getOriginZA();
            stdZ = resValue.at(0);
            stdA = resValue.at(1);
            dlg->setZ(stdZ);
            dlg->setA(stdA);
            if(dlg->exec()!=QDialog::Accepted)
                return;

            clsCalDb::getInst()->insertRecord(tmpPar.freqnecy,tmpPar.channel,
                                              dlg->getZ(),dlg->getA(),"Ls");

        }
    }

    dlg->setMessage(tr("请放置好标准负载!"),tr("负载校准"));

    if(dlg->exec()!=QDialog::Accepted)
        return;

    for(int c=0; c< channels.length(); c++)
    {
        Parameters tmpPar = channels.at(c);

        meter->setFreqencyForCal((double)tmpPar.freqnecy);
        if(tmpPar.isUsable)
        {
            QPoint currentChannel = tmpPar.channel;
            clsConnectSWBox::Ins()->setChannel(currentChannel,"WK6500");
            clsConnectSWBox::Ins()->setRelay(tmpPar.switchStatus);

            showCalMessage(tr("负载校准"),tmpPar.freqnecy,currentChannel);

            meter->setFreqencyForCal((double)tmpPar.freqnecy);
            QList<double> resValue = meter->getOriginZA();
            loadZ=resValue.at(0);
            loadA=resValue.at(1);
            clsCalDb::getInst()->insertRecord(tmpPar.freqnecy,currentChannel,
                                              loadZ,loadA,"Lm");


        }
    }
    setCalLabelInfo(this->lblGoldenSample,tr("负载校准"));
}
