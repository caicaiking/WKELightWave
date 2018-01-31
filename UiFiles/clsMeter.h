#ifndef CLSMETER_H
#define CLSMETER_H

#include <QDialog>
#include <QObject>
class clsMeter : public QDialog
{
    Q_OBJECT
public:
    explicit clsMeter(QDialog *parent=0);

    virtual void setCondition(const QString condition)=0;   //设置测试条件
    virtual void setChannel(const QPoint channel)=0;           //设置通道
    virtual void setChannelSettings()=0;                    //切换成设置模式
    virtual void setChannelRunnings()=0;                    //切换成运行模式
    virtual void setCloseEnabled(const bool bl)=0;          //使能关闭按钮
    virtual void updateLabels()=0;                          //更新标签
    virtual void updateRes(const QString res)=0;            //更新结果
    virtual void setStep(const int i) =0;                   //设置步骤
    virtual int getStep() const=0;                          //获取步骤
signals:
    void deleteChannelSettings(int index);                  //删除步骤，通常是指自己本身
    void editStep(int step);
};

#endif // CLSMETER_H
