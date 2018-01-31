#ifndef CLSWK6500CALIBRATIONMETER_H
#define CLSWK6500CALIBRATIONMETER_H

#include "clsInstrumentCalibration.h"

class clsWK6500CalibrationMeter : public clsInstrumentCalibration
{
public:
    clsWK6500CalibrationMeter();
    void set10KHz();                  //设置10kHz为了校准
    void setChannel(QPoint value);       //通道测试
    void setUseLoad(bool value);      //使用Load数据
    void setConditionForCalibration(int); //设置条件为了校准；
    QList<double> getOriginZA();      //获得原始的没有进行过校准的Z A
    void setFreqencyForCal(double);   //设置频率，为了校准
    double getFreqency(int value );   //获取测试的频率
private:
    double frequency;

};

#endif // CLSWK6500CALIBRATIONMETER_H
