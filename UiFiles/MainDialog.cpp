#include "MainDialog.h"
#include "clsNewSetup.h"
#include "clsChannelSettings.h"
#include "clsRunningStatus.h"
#include <QGridLayout>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonParseError>
#include "publicUtility.h"
#include "clsMeterFactory.h"
#include <QDebug>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint
                         | Qt::WindowMaximizeButtonHint);
    this->showMaximized();
    connect(&runService,SIGNAL(showRes(QString)),this,SLOT(showChannelRes(QString)));
}

void MainDialog::updateChannelSettings(QVariantMap map)
{
    QList<QWidget*> widgetList;
    widgetList<<widget<<widget_2<<widget_3<<widget_4<<widget_5<<widget_6
             <<widget_7<<widget_8;
    for(int i=0;i<channelMap.count();i++)
    {
        deleteChannel(i+1);
    }
    conditionMap=map;
    for(int i=0;i<conditionMap.count();i++)
    {
       // clsChannelSettings *channelSettings=new clsChannelSettings;
        QString strCondition=conditionMap[QString::number(i)].toString();

        QVariantMap strMap=publicUtility::parseConditions(strCondition);
        QString str=strMap["meter"].toString();
        clsMeter *tmpMeter=clsMeterFactory::getMeter(str);
        connect(tmpMeter,SIGNAL(deleteChannelSettings(int)),this,SLOT(deleteChannel(int)));
        if(widgetList.at(i)->layout()!=NULL)
        {
            deleteChannel(i+1);
        }

        channelMap.insert(i,tmpMeter);


        //QString strCondition=publicUtility::pressConditions(variant);
        tmpMeter->setCondition(strCondition);
        tmpMeter->updateLabels();

        QGridLayout* mlayout=new QGridLayout;
        mlayout->setHorizontalSpacing(1);
        mlayout->setSpacing(1);

        mlayout->addWidget(tmpMeter);
        mlayout->setHorizontalSpacing(1);
        widgetList.at(i)->setLayout(mlayout);

    }
}

void MainDialog::on_btnNewSetup_clicked()
{
    clsNewSetup *dlg=new clsNewSetup(this);
    QList<QWidget*> widgetList;
    widgetList<<widget<<widget_2<<widget_3<<widget_4<<widget_5<<widget_6
             <<widget_7<<widget_8;

    if(dlg->exec()==QDialog::Accepted)
    {
        channel=dlg->getChannel();
        QString tmpMeter=dlg->getMeter();
        meter=clsMeterFactory::getMeter(tmpMeter);
        //clsChannelSettings *channelSettings=new clsChannelSettings;

        connect(meter,SIGNAL(deleteChannelSettings(int)),this,SLOT(deleteChannel(int)));
        if(widgetList.at(channel-1)->layout()!=NULL)
        {
            deleteChannel(channel);
        }
        channelMap.insert(channel-1,meter);
        meter->setChannel(channel);
        meter->setCondition(dlg->getCondtion());
        meter->updateLabels();

        conditionMap.insert(QString::number(channel-1),dlg->getCondtion());

        QGridLayout* mlayout=new QGridLayout;
        mlayout->setHorizontalSpacing(1);
        mlayout->setSpacing(1);

        mlayout->addWidget(meter);
        mlayout->setHorizontalSpacing(1);
        widgetList.at(channel-1)->setLayout(mlayout);
    }
}

void MainDialog::on_btnSettings_clicked()
{
    //stackedWidget->setCurrentIndex(0);
    QList<QWidget*> widgetList;
    widgetList<<widget<<widget_2<<widget_3<<widget_4<<widget_5<<widget_6
             <<widget_7<<widget_8;
    for(int i=0;i<widgetList.length();i++)
    {
        if(widgetList.at(i)->layout()!=NULL)
        {
            channelMap[i]->setChannelSettings();
            channelMap[i]->setCloseEnabled(true);
        }
    }
    btnNewSetup->setEnabled(true);
    btnOpenSetup->setEnabled(true);
    btnSaveSetup->setEnabled(true);

}

void MainDialog::on_btnRunning_clicked()
{
    //stackedWidget->setCurrentIndex(1);
    QList<QWidget*> widgetList;
    widgetList<<widget<<widget_2<<widget_3<<widget_4<<widget_5<<widget_6
             <<widget_7<<widget_8;
    for(int i=0;i<widgetList.length();i++)
    {
        if(widgetList.at(i)->layout()!=NULL)
        {
            channelMap[i]->setChannelRunnings();
            channelMap[i]->setCloseEnabled(false);
        }
    }
    btnNewSetup->setEnabled(false);
    btnOpenSetup->setEnabled(false);
    btnSaveSetup->setEnabled(false);
}

void MainDialog::deleteChannel(int index)
{
    qDebug()<<"delete channel"<<index;
    QList<QWidget*> widgetList;
    widgetList<<widget<<widget_2<<widget_3<<widget_4<<widget_5<<widget_6
             <<widget_7<<widget_8;

    if(widgetList.at(index-1)->layout()!=NULL)
    {
        disconnect(channelMap[index-1],SIGNAL(deleteChannelSettings(int)),this,SLOT(deleteChannel(int)));
        delete channelMap[index-1];//一定要先删除该控件  否则无法从界面中删除该控件
        widgetList.at(index-1)->layout()->removeWidget(channelMap[index-1]);
        delete widgetList.at(index-1)->layout();
        widgetList.at(index-1)->repaint();
        widgetList.at(index-1)->update();
    }
    else
        qDebug()<<"no layout";

}

void MainDialog::showChannelRes(QString res)
{
    QVariant resVariant;
    resVariant=publicUtility::parseConditions(res);

}

void MainDialog::on_btnSaveSetup_clicked()
{
    QString strPath=QFileDialog::getSaveFileName(this,tr("保存测试任务"), ".",
                                                 tr("WKE FactoryView 任务 (*.wket)"),0);
    QString strSetup;
    QJsonDocument jsonDocument=QJsonDocument::fromVariant(conditionMap);
    if(!(jsonDocument.isNull()))
    {
        strSetup=jsonDocument.toJson(QJsonDocument::Indented);
    }
    if(strPath.isEmpty())
        return;
    else
    {
        QFile file(strPath);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream outStream(&file);
        outStream<<strSetup;
        outStream.flush();
        file.close();
    }
}

void MainDialog::on_btnOpenSetup_clicked()
{
    QString strPath=QFileDialog::getOpenFileName(this,tr("保存测试任务"), ".",
                                                 tr("WKE FactoryView 任务 (*.wket)"),0);
    QString strSetup;
    if(strPath.isEmpty())
        return;
    QFile file(strPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream inStream(&file);
    strSetup=inStream.readAll();
    file.close();

    QVariantMap tmpConditionMap;

    QJsonParseError error;
    QJsonDocument jsonDocument=QJsonDocument::fromJson(strSetup.toUtf8(),&error);
    if(error.error==QJsonParseError::NoError)
    {
        if(!(jsonDocument.isNull() || jsonDocument.isEmpty()))
        {
            if(jsonDocument.isObject())
            {
                tmpConditionMap=jsonDocument.toVariant().toMap();
                for(int i=0;i<tmpConditionMap.count();i++)
                {
                    qDebug()<<tmpConditionMap[QString::number(i)].toString();
                }
            }
        }
    }
    updateChannelSettings(tmpConditionMap);
}
