#ifndef GLOBLE_H
#define GLOBLE_H

#define OR 99.999E99

#include <QString>
#include "doubleType.h"
#include <QObject>
#include <QList>

enum Status {
    BUSY=0,PASS=1,FAIL=2,IDEL=3
};

/*!

*/


struct graphSetup
{
    double xmin;
    double xmax;
    bool logX;

    double yLeftMin;
    double yLeftMax;
    bool logYleft;

    double yRightMin;
    double yRightMax;

    double biasVRate; //偏置电压速率
    QString title;
    QList<double> points;

    bool equal(graphSetup m)
    {
        if(xmin!=m.xmin)
            return false;
        if(xmax!=m.xmax)
            return false;
        if(logX!=m.logX)
            return false;

        if(points!=m.points)
            return false;

        return true;
    }

};

#endif // GLOBLE_H
