#ifndef PUBLICUTILITY_H
#define PUBLICUTILITY_H
#include <QMap>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QVariantMap>

class QStringList;
class QString;

enum SaveResultType
{
    AllRes=0,PassRes=1,FailRes=2
};

struct MeterSettings
{
    double preDelay; //前延时
    double lastDelay; //后延时
    bool failPass; //失败通过
    bool failRetestOnce; //失败重新测试一次
    SaveResultType saveResType; //保存结果类型
    bool displayResultType; //显示结果类型
    int startNumber; //开始号码
    QString sp; //分割数据
};


class publicUtility
{
public:
    publicUtility();

    static bool IsDouble(const QStringList r);
    static bool IsDouble(const QString r);
    static QString getVersion();
    static QString getSuffix(const QString& value);
    static QString getName(const QString &value);
    static void sleepMs(int svalue);
    static double Max(const QList<double> &arry);
    static double Min(const QList<double> &arry);
    static double Abs(double x);
    static QList<double> resultPro(const QString &resultString);
    static QString converToQString(QList<QString> tmp,QChar sp=',');
    static QString converToQString(QList<double> tmp);
    static QList<double> converToDoubleList(QString tmp);
    static int getLanChoice();
    static void setLanChoice(int i);
};

#endif // PUBLICUTILITY_H
