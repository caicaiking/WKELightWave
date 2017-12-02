#include "clsDataStatistics.h"

clsDataStatistics::clsDataStatistics(QObject *parent):QObject(parent)
{
    totle =0;
    pass=0;
    fail=0;
    t1 = QTime::currentTime();
    trigMs = 10000E3;
}

void clsDataStatistics::addData(bool value)
{
    t2 = QTime::currentTime();
    trigMs = t1.msecsTo(t2);
    t1 = t2;

    totle +=1;
    if(value)
        pass +=1;
    else
        fail +=1;
    showInfo();
}


void clsDataStatistics::showInfo()
{
    if(trigMs !=0)
    {
        int times = int(60*1000*1.0/trigMs);
        emit showSpeed(QString::number(times)+ tr("次/分"));
    }

    emit showTotle(tr("总数：%1").arg(totle));
    emit showPass(tr("通过：%1").arg(pass));
    emit showFail(tr("失败：%1").arg(fail));
    if(totle !=0)
    {
        double passRate = pass *1.0/totle *100;
        QString tmpStr;
        tmpStr= QString::asprintf("%5.2lf",passRate);
        emit showPassRate(tr("良品率：%1%").arg(tmpStr));
    }


}
