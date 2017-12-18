#ifndef CLSWK6500RUNNINGMODE_H
#define CLSWK6500RUNNINGMODE_H

#include <QObject>
#include "clsInstrument.h"
#include "singleton.h"
#include "clsMeterLimit.h"
class clsWK6500RunningMode: public clsInstrument
{
    Q_OBJECT
public:
    explicit clsWK6500RunningMode(clsInstrument *parent=0 );


    void initConnection() ;            //初始化连接
    bool connectionStatus() ;          //查询连接状态
    void setCondition(QString value) ;       //设置测试条件
    QString getCondition() ;           //获取设置状态
    bool trig() ;                      //获取测试数据

    int getItemsCount() ;              //获取结果数目
    bool getItemStatus(int i) ;        //获取单独项目测试结果的状态
    bool getTotleStatus() ;            //获取所有测试项目的总体状态
    QString getItem(int i);           //获取测试项目
    QString getItemSuffix(int i);       //格式化数据的后缀

    double getItemValue(int i) ;       //获取每个项目的测试值 如： 1.0000E+3
    double getItemValueWithSuffix(int i) ; //获取每个项目的测试值具有格式 如： 1.000k
    QString getInstrumentType() ;      //获取仪器的类型
    void turnOffOutput()  ;            //关闭所有的输出
protected slots:
    QString changeItemToGpib(QString value);
private slots:
    void updateGpibCommand();


private:
    QStringList normCommands;
    QString biasCommand;
private:

    bool isConnected;
    QString item1, item2;
    bool isItem2Enable;
    double frequency, level;
    QString levelUnit;
    QString range;
    QString equcct;
    QString speed;
    double bias;
    QString biasSwitch;
    QString biasType;
    QString relaySwitch;
    double item1HiLimit, item1LowLimit,item2HiLimit,item2LowLimit;
    QString suffix1, suffix2;

    QList<double> results;

    QString strConditon;
    QList<clsMeterLimit* > limits;
    int channel;

};
typedef Singleton<clsWK6500RunningMode> sngWK6500Run;
#endif // CLSWK6500RUNNINGMODE_H
