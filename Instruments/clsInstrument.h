#ifndef CLSINSTRUMENT_H
#define CLSINSTRUMENT_H

#include <QObject>
///
/// \brief 主要是为了适配所有的仪器，用同一个父类。
///
class clsInstrument : public QObject
{
    Q_OBJECT
public:
    explicit clsInstrument(QObject *parent=0):QObject(parent){}
    virtual void initConnection()=0;            //初始化连接
    virtual bool connectionStatus()=0;          //查询连接状态
    virtual void setCondition(QString)=0;       //设置测试条件
    virtual QString getCondition()=0;           //获取设置状态
    virtual bool trig()=0;                      //获取测试数据

    virtual int getItemsCount()=0;              //获取结果数目
    virtual bool getItemStatus(int i)=0;        //获取单独项目测试结果的状态
    virtual bool getTotleStatus()=0;            //获取所有测试项目的总体状态
    virtual QString getItem(int i)=0;           //获取测试项目
    virtual QString getItemSuffix(int i)=0;       //格式化数据的后缀
    virtual double getItemValue(int i)=0;       //获取每个项目的测试值 如： 1.0000E+3
    virtual double getItemValueWithSuffix(int i)=0; //获取每个项目的测试值具有格式 如： 1.000k
    virtual QString getInstrumentType()=0;      //获取仪器的类型
    virtual void turnOffOutput() =0;            //关闭所有的输出
signals:
    void setConnectStatus(bool);                //显示连接状态
public slots:
};

#endif // CLSINSTRUMENT_H

