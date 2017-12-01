#include "publicUtility.h"
#include <QStringList>
#include <QFile>
#include <QString>
#include <QSettings>
#include <QTime>
#include <QStringListIterator>
#include <QCoreApplication>
#include <QDebug>
#include <QMap>
#include <QTime>
using  std::vector;
publicUtility::publicUtility()
{
}

bool publicUtility::IsDouble(const QStringList r)
{

    QStringListIterator it(r);
    bool ok=false;

    while(it.hasNext())
    {

        QString str=it.next();
        // qDebug()<<str;
        str.toDouble(&ok);
        if(!ok)
            return false;
    }

    return true;
}

bool publicUtility::IsDouble(const QString r)
{
    bool ok;

    r.toDouble(&ok);
    return ok;
}

QString publicUtility::getVersion()
{
    QFile file(":/version.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "0.0.0";

    QString text = file.readLine();

    file.close();
    return text;

}


//value is like Z R Rdc etc.
QString publicUtility::getSuffix(const QString &value)
{

    if (value=="Z" || value=="R" || value=="X" || value=="RDC" || value =="Rdc")
        return QString("Ω");

    if(value=="A" || value==QString("θ"))
        return QString("°");


    if(value=="G" || value=="B" || value=="Y")
        return "S";

    if(value=="E'r" || value=="E\"r" || value=="U'r" || value=="U\"r")
        return "U";

    if(value =="De" || value == "Du")
        return "D";

    if(value=="L")
        return "H";
    if(value=="C")
        return "F";
    if(value=="Q" || value=="D")
        return value;
    if(value.toUpper()=="FREQUENCY" || value.toUpper()==QObject::tr("频率").toUpper())
        return "Hz";
    if(value.toUpper() =="SRF")
        return "Hz";
    if(value.toUpper()=="BIAS" || value.toUpper()==QObject::tr("偏置电压").toUpper() || value.toUpper()==QObject::tr("外置偏压").toUpper() || value.toUpper()==QObject::tr("电压信号"))
        return "V";
    if(value.toUpper()=="TIME" || value.toUpper()==QObject::tr("时间").toUpper())
        return "s";
    if(value.toUpper()=="CURRENT" || value.toUpper()=="CUR")
        return "A";
    if(value.toUpper()=="BIASI" || value.toUpper()==QObject::tr("偏置电流").toUpper())
        return "A";
    if(value.toUpper()=="LEVELA" || value.toUpper()==QObject::tr("电流信号").toUpper())
        return "A";
    if(value.toUpper() == QObject::tr("次数").toUpper())
        return "T";
    if(value.toUpper()=="LEVELV")
        return "V";

    return value;
}

QString publicUtility::getName(const QString &value)
{
    if(value=="Z")
        return QObject::tr("阻抗");
    else if(value=="R")
        return QObject::tr("交流电阻");
    else if(value=="X")
        return QObject::tr("电抗");
    else if(value=="RDC")
        return QObject::tr("直流电阻");
    else if(value=="A" || value==QString("θ"))
        return QObject::tr("相位");
    else if(value=="G")
        return QObject::tr("电导");
    else if(value=="B")
        return QObject::tr("电纳");
    else if(value=="Y")
        return QObject::tr("导纳");
    else if(value=="L")
        return QObject::tr("电感");
    else if(value=="C")
        return QObject::tr("电容");
    else if(value=="Q")
        return QObject::tr("品质因素");
    else if(value=="D")
        return QObject::tr("损耗");

    else if(value=="E'r")
        return QObject::tr("介电实部");
    else if(value=="E\"r")
        return QObject::tr("介电虚部");
    else if(value=="De")
        return QObject::tr("损耗");
    else if(value=="U'r")
        return QObject::tr("磁导率实部");
    else if(value=="U\"r")
        return QObject::tr("磁导率虚部");
    else if(value=="Du")
        return QObject::tr("损耗");

    else
        return "";
}

void publicUtility::sleepMs(int svalue)
{
    QTime dieTime = QTime::currentTime().addMSecs(svalue);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

QList<double> publicUtility::resultPro(const QString &resultString)
{
    QStringList list= resultString.split(",");

    QList<double> myReturn;

    for(int i=0; i<list.count();i++)
    {
        myReturn<< list.at(i).toDouble();

//        if(myReturn.at(i)==0.0)
//            myReturn.insert(i,999999999);
    }
    return myReturn;

}

QString publicUtility::converToQString(QList<QString> tmp, QChar sp)
{
    QStringList tmpStr;
    for(int i=0; i<tmp.length();i++)
    {
        tmpStr<< tmp.at(i);
    }

    return tmpStr.join(sp);
}

QString publicUtility::converToQString(QList<double> tmp)
{
    QStringList tmpStr;
    for(int i=0; i< tmp.length();i++)
    {
        tmpStr<< QString::number(tmp[i]);
    }
    return tmpStr.join(",");
}

QList<double> publicUtility::converToDoubleList(QString tmp)
{
    QStringList tmpStr = tmp.split(",");
    QList<double> list;

    if(tmp.isEmpty())
        return list;

    for(int i=0; i< tmpStr.length();i++)
    {
        list.append(tmpStr[i].toDouble());
    }

    return list;
}

double publicUtility::Max(const QList<double> &arry)
{
    if(arry.length()==0)
        return 0.0;

    double max=arry.at(0);


    QListIterator<double> it(arry);

    while(it.hasNext())
    {
        double value= it.next();

        if(value>max)
            max=value;
    }

    return max;
}

double publicUtility::Min(const QList<double> &arry)
{
    if(arry.length()==0)
        return 0.0;

    double min=arry.at(0);


    QListIterator<double> it(arry);

    while(it.hasNext())
    {
        double value= it.next();

        if(value<min)
            min=value;
    }

    return min;
}
double publicUtility::Abs(double x)
{
    if(x<=0)
        return -1.0*x;
    else
        return x;
}
