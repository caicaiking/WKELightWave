#ifndef CLSINSTRUMENTCALIBRATION_H
#define CLSINSTRUMENTCALIBRATION_H
#include <QList>


class clsInstrumentCalibration
{
public:
    clsInstrumentCalibration();

    virtual void calibration()=0;
    virtual void set10KHz()=0;                  //设置10kHz为了校准
    virtual void setChannel(int value)=0;       //通道测试
    virtual void setUseLoad(bool value)=0;      //使用Load数据
    virtual void setConditionForCalibration(int)=0; //设置条件为了校准；
    virtual QList<double> getOriginZA()=0;      //获得原始的没有进行过校准的Z A
    virtual void setFreqencyForCal(double)=0;   //设置频率，为了校准
    virtual double getFreqency(int value )=0;   //获取测试的频率
};

#endif // CLSINSTRUMENTCALIBRATION_H
