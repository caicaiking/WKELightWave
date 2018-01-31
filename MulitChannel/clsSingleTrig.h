#ifndef CLSSINGLETRIG_H
#define CLSSINGLETRIG_H
#include <QString>
#include <QPoint>
#include "clsDataProcess.h"
class clsSingleTrig
{
public:
    clsSingleTrig();

    QPoint getChannel() const;
    void setChannel(QPoint value);

    double getFrequency() const;
    void setFrequency(double value);

    double getZm() const;
    void setZm(double value);

    double getAm() const;
    void setAm(double value);

    bool getBlUseLoad() const;
    void setBlUseLoad(bool value);

    void doLoadCalibration();
    void doRCCalibration();

    double getItem(QString item, QString equcct);

private:
    QPoint channel;
    double frequency;
    double Zm;
    double Am;
    bool blUseLoad;

    clsDataProcess *dp;

};

#endif // CLSSINGLETRIG_H
