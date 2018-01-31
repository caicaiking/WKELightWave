#include "clsSingleTrig.h"
#include "clsDataProcess.h"
#include "clsCalibrationDbOp.h"

clsSingleTrig::clsSingleTrig()
{
}
QPoint clsSingleTrig::getChannel() const
{
    return channel;
}

void clsSingleTrig::setChannel(QPoint value)
{
    channel = value;
}
double clsSingleTrig::getFrequency() const
{
    return frequency;
}

void clsSingleTrig::setFrequency(double value)
{
    frequency = value;
}
double clsSingleTrig::getZm() const
{
    return Zm;
}

void clsSingleTrig::setZm(double value)
{
    Zm = value;
}
double clsSingleTrig::getAm() const
{
    return Am;
}

void clsSingleTrig::setAm(double value)
{
    Am = value;
}
bool clsSingleTrig::getBlUseLoad() const
{
    return blUseLoad;
}

void clsSingleTrig::setBlUseLoad(bool value)
{
    blUseLoad = value;
}

void clsSingleTrig::doLoadCalibration()
{
    Zm = Zm +(Zm==0? 1.0E-9:0.0);
    Am = Am +(Am==0? 1.0E-9:0.0);

    QList<double> openData = clsCalDb::getInst()->getCalData(frequency,channel,"O");
    QList<double> shortData = clsCalDb::getInst()->getCalData(frequency,channel,"S");
    QList<double> loadData = clsCalDb::getInst()->getCalData(frequency,channel,"Lm");
    QList<double> stdData = clsCalDb::getInst()->getCalData(frequency,channel,"Ls");

    clsDataProcess d(Zm,Am,frequency);
    if((openData.length() ==2) && (shortData.length() ==2))
    {
        d.applyOpenData(openData.at(0),openData.at(1));
        d.applyShortData(shortData.at(0),shortData.at(1));

        if((loadData.length()==2) && (stdData.length()==2) && blUseLoad)
        {
            d.applyLoadData(loadData.at(0),loadData.at(1));
            d.applyStdData(stdData.at(0),stdData.at(1));
            d.useLoadData(true);
            d.doCalibration();
        }
        else
        {
            d.useLoadData(false);
            d.doCalibration();
        }
    }

    Zm = d.getItem("Z",QObject::tr("串联"));

    Am = d.getItem("A",QObject::tr("串联"));
    if(Am > 180)
        Am =Am - 360.0;
    else if(Am < -180.0)
        Am += 360.0;


}

void clsSingleTrig::doRCCalibration()
{
    Zm = Zm +(Zm==0? 1.0E-9:0.0); //防止Zm =0
    Am = Am +(Am==0? 1.0E-9:0.0); //防止AM =0

    QList<double> openData = clsCalDb::getInst()->getCalData(frequency,channel,"O"); //开路
    QList<double> shortData = clsCalDb::getInst()->getCalData(frequency,channel,"S"); //短路
    QList<double> openData_10K = clsCalDb::getInst()->getCalData(10E3,channel,"OC_10k"); //短路
    QList<double> shortData_10K = clsCalDb::getInst()->getCalData(10E3,channel,"SC_10k"); //短路

    QList<double> z100Rref = clsCalDb::getInst()->getCalData(10000.0,channel,"HF_100RRef"); //10KHz 100R 参考值
    QList<double> z100CR = clsCalDb::getInst()->getCalData(frequency,channel,"HF_C100R");   //100R量测值
    QList<double> z100Pref = clsCalDb::getInst()->getCalData(10000.0,channel,"HF_100PRef"); //10KHz 100P参考值
    QList<double> z100CP = clsCalDb::getInst()->getCalData(frequency,channel,"HF_C100P");  //100P测试频率量测值



    if((openData.length() !=2) ||(shortData.length() !=2))
        return;

    if(z100Rref.length() !=2 || z100Pref.length() !=2) //只对数据进行开路短路校准
    {

        clsDataProcess zop(Zm,Am,frequency);

        zop.applyOpenData(openData.at(0),openData.at(1));
        zop.applyShortData(shortData.at(0),shortData.at(1));
        zop.useLoadData(false);
        zop.doCalibration();

        Zm=zop.getItem("Z",QObject::tr("串联")) ;
        Am=zop.getItem("A",QObject::tr("串联"));
        return ;

    }
    else
    {
        //先对100R 100P 10kHz的数据进行开路校准

        auto applyOpenShort =[](
                QList<double> op, QList<double> st, QList<double> meas, double frequeny)
        {
            clsDataProcess tmp(meas.first(),meas.last(), frequeny);
            tmp.applyOpenData(op.first(),op.last());
            tmp.applyShortData(st.first(),st.last());
            tmp.useLoadData(false);
            tmp.doCalibration();
            double z = tmp.getItem("Z", QObject::tr("串联"));
            double a = tmp.getItem("A", QObject::tr("串联"));

            return QList<double>()<<z<<a;
        };

        QList<double> meas;
        meas<< Zm<<Am;

        QList<double> _100R = applyOpenShort(openData,shortData,z100CR, frequency);
        QList<double> _100P = applyOpenShort(openData,shortData,z100CP, frequency);
        QList<double> __Dut = applyOpenShort(openData,shortData, meas, frequency);
        QList<double> _100PRef = applyOpenShort(openData_10K,shortData_10K,z100Pref,10E3);

        //角度适配
        double angleRange = qAbs(_100P.last() - _100R.last());
        double diffA = __Dut.last() - _100P.last();
        Am = diffA/angleRange *90 -90;

        //幅值适配
        if(Zm > _100R.first()) //> 100 Ohm
        {
            double magRange = abs(_100P.first() - _100R.first());
            double realMagRange = abs(_100PRef.first() *10E3 / frequency - 100.0);
            Zm = 100.0+ (__Dut.first()- _100R.first()) / magRange * realMagRange;
        }
        else 				   // <=100 Ohm
        {
            double magRange = abs(_100R.first());
            double realMagRange = 100.0-0.0;

            Zm = 0.0+ __Dut.first() /magRange * realMagRange;
        }

    }

    clsDataProcess end(Zm,Am,frequency);
    Zm=end.getItem("Z",QObject::tr("串联"));
    Am=end.getItem("A",QObject::tr("串联"));

}

double clsSingleTrig::getItem(QString item, QString equcct)
{
    clsDataProcess d(Zm,Am,frequency);

    return d.getItem(item,equcct);
}





