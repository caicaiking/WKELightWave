#ifndef CLSHVRUNNINGMODE_H
#define CLSHVRUNNINGMODE_H

#include <QObject>
#include "clsInstrument.h"
#include "clsHVConnection.h"
#include "clsMeterLimit.h"


class clsHVRunningMode :public clsInstrument
{
public:
    explicit clsHVRunningMode(clsInstrument *parent=0);
    void initConnection() ;            //初始化连接
    bool connectionStatus() ;          //查询连接状态
    void setCondition(QString value) ;       //设置测试条件
    QString getCondition() ;           //获取设置状态
    bool trig() ;                      //获取测试数据

    int getItemsCount() ;              //获取结果数目
    bool getItemStatus(int) ;        //获取单独项目测试结果的状态
    bool getTotleStatus() ;            //获取所有测试项目的总体状态
    QString getItem(int i);           //获取测试项目
    QString getItemSuffix(int i);       //格式化数据的后缀

    double getItemValue(int i) ;       //获取每个项目的测试值 如： 1.0000E+3
    double getItemValueWithSuffix(int i) ; //获取每个项目的测试值具有格式 如： 1.000k
    QString getInstrumentType() ;      //获取仪器的类型
    void turnOffOutput();            //关闭所有的输出
    void clearGpibCommands();
private slots:
    void updateGpibCommands();

private:
    QString strCondition;
    double voltage;
    QString item, suffix;
    QString relaySwitch;
    QList<clsMeterLimit *> limits;
    double hiLimit,lowLimit;
    double dblRampUp, dblDelay, dblRampDown;
    bool isConnected;
    QList<double> results;

    QStringList gpibCommands;

    bool resStatus;


};
typedef Singleton<clsHVRunningMode> sngHVRun;
#endif // CLSHVRUNNINGMODE_H
