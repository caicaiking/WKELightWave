#include "clsWKCommandProcess.h"
#include <QDebug>
#include <QStringListIterator>
#include "clsRunService.h"

#include "publicUtility.h"
clsWKCommandProcess::clsWKCommandProcess(QObject *parent) : QObject(parent)
{
    //注册所有的函数，用其GPIB指令注册其Key
    queryFunction.insert("*IDN?",&clsWKCommandProcess::queryId);
    setFunction.insert("TRIG",&clsWKCommandProcess::trig);
    this->lastCmmdType =0;
}

void clsWKCommandProcess::setIsRemote(bool value) {
    emit lanRemote(value);
}

void clsWKCommandProcess::setGpibCommand(QString str)
{

    qDebug()<< str;
    if(str == " ")
        return ;
    //根指令1st， 根指令2end
    QString strMode1st, strMode2end;

    QStringList cmdList = str.split(";",QString::SkipEmptyParts); //将指令分开用;，并且省略了空白部分。

    QListIterator<QString> it(cmdList);
    lastCmmdType=0;
    while(it.hasNext())
    {
        QString tmpStr = it.next();

        if(!tmpStr.isEmpty())
        {
            if(tmpStr.contains("?")) //查询指令开始
            {
                lastCmmdType =2;
                QStringList modes= tmpStr.split(":",QString::SkipEmptyParts);
                if(modes.length()==1 && queryFunction.keys().contains(modes.at(0)))//通用的IEE488指令查询
                {

                    (this->*(queryFunction.value(modes.at(0))))();
                }
                else if( modes.length()==2 && queryFunction.keys().contains(modes.at(1)))//通用的仪器指令查询
                {

                    (this->*(queryFunction.value(modes.at(1))))();
                }
                else if(modes.length()==3 && queryFunction.keys().contains(modes.at(1)+":"+modes.at(2)))//有副根指令的参数查询
                {

                    (this->*(queryFunction.value(modes.at(1)+":"+modes.at(2))))();
                }
                else//GPIB处理出错
                {
                    writeToClient("Send Command error!");
                }

            }
            else //设置指令开始
            {
                lastCmmdType =1;
                QStringList pars = tmpStr.split(" ",QString::SkipEmptyParts);

                if(pars.length()==1) //没有参数的设置指令 :METER:TRIG
                {
                    QStringList modes = pars.at(0).split(":",QString::SkipEmptyParts);
                    if(modes.length()==1 && setFunction.keys().contains(modes.at(0))) //如 *TRG
                        (this->*(setFunction.value(modes.at(0))))("");
                    else if(modes.length()==2 && setFunction.keys().contains(modes.at(1))) //如 :METER:TRIG
                        (this->*(setFunction.value(modes.at(1))))("");
                    else
                    {
                        writeToClient("Send Command error!");
                    }

                }
                else if(pars.length()==2) //有参数的设置指令
                {
                    QString par = pars.at(1);
                    QString strMode = pars.at(0);
                    QStringList modes = strMode.split(":",QString::SkipEmptyParts);

                    if(modes.length()==3) //有副根指令的命令， 如： :METER:FUNC:1 C
                    {
                        strMode1st = modes.at(0);
                        strMode2end = modes.at(1);
                        QString strItem = modes.at(2);

                        if(setFunction.keys().contains(strMode2end+":"+strItem))
                        {
                            (this->*(setFunction.value(strMode2end+":"+strItem)))(par);
                        }
                    }
                    else if(modes.length() ==2) //一般的设置指令
                    {
                        strMode1st = modes.at(0);
                        strMode2end = modes.at(1);

                        if(setFunction.keys().contains(strMode2end))
                        {
                            (this->*(setFunction.value(strMode2end)))(par);
                        }
                    }
                    else if(modes.length()==1) //如 2 D这样的指令
                    {
                        if(setFunction.keys().contains(strMode2end+":"+modes.at(0)))
                        {
                            (this->*(setFunction.value(strMode2end+":"+modes.at(0))))(par);

                        }
                    }
                    else
                    {
                        writeToClient("Send Command error!");
                    }
                }
            }
        }
    }

    if(this->lastCmmdType == 1)
        writeToClient(" ");
}

void clsWKCommandProcess::queryId()
{
    QString version = publicUtility::getVersion();
    version = version.remove("\r");
    version = version.remove("\n");
    writeToClient("WAYNE KERR, LightWave, Lan Remote, " + version);
}

void clsWKCommandProcess::trig(const QString &/*empty*/ )
{
    this->lastCmmdType = 2;
    writeToClient(sngRunService::Ins()->lanTrig());
}


