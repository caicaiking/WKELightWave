#include "MainDialog.h"
#include "clsNewSetup.h"
#include "clsChannelSettings.h"
#include "clsRunningStatus.h"
#include <QGridLayout>
#include <QDebug>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint
                         | Qt::WindowMaximizeButtonHint);
    this->showMaximized();
}

void MainDialog::on_btnNewSetup_clicked()
{
    clsNewSetup *dlg=new clsNewSetup(this);
    QList<QWidget*> widgetList;
    widgetList<<widget<<widget_2<<widget_3<<widget_4<<widget_5<<widget_6
                <<widget_7<<widget_8;
    QList<QWidget*> widgetRunList;
    widgetRunList<<widgetRun1<<widgetRun2<<widgetRun3<<widgetRun4
                   <<widgetRun5<<widgetRun6<<widgetRun7<<widgetRun8;

    if(dlg->exec()==QDialog::Accepted)
    {
        channel=dlg->getChannel();
        clsChannelSettings *channelSettings=new clsChannelSettings;
        clsRunningStatus *runningStatus=new clsRunningStatus;

        connect(channelSettings,SIGNAL(deleteChannelSettings(int)),this,SLOT(deleteChannel(int)));
        if(widgetList.at(channel-1)->layout()!=NULL)
        {
            deleteChannel(channel);
        }
        channelMap.insert(channel-1,channelSettings);
        channelSettings->setChannel(channel);
        channelSettings->setCondition(dlg->getCondtion());
        channelSettings->updateLabels();

        runningMap.insert(channel-1,runningStatus);
        runningStatus->setChannel(channel);
        runningStatus->setItem1("L");
        runningStatus->setItem2("Q");
        runningStatus->setStatus1(true);
        runningStatus->setStatus2(false);
        runningStatus->updateLabels();
        runningStatus->updateStatusLabels();

        QGridLayout* mlayout=new QGridLayout;
        mlayout->setHorizontalSpacing(1);
        mlayout->setSpacing(1);

        mlayout->addWidget(channelSettings);
        mlayout->setHorizontalSpacing(1);
        widgetList.at(channel-1)->setLayout(mlayout);

        QGridLayout* statusLayout=new QGridLayout;
        statusLayout->setHorizontalSpacing(1);
        statusLayout->setSpacing(1);

        statusLayout->addWidget(runningStatus);
        statusLayout->setHorizontalSpacing(1);
        widgetRunList.at(channel-1)->setLayout(statusLayout);
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
}

void MainDialog::deleteChannel(int index)
{
    qDebug()<<"delete channel"<<index;
    QList<QWidget*> widgetList;
    widgetList<<widget<<widget_2<<widget_3<<widget_4<<widget_5<<widget_6
                <<widget_7<<widget_8;
    QList<QWidget*> widgetRunList;
    widgetRunList<<widgetRun1<<widgetRun2<<widgetRun3<<widgetRun4
                   <<widgetRun5<<widgetRun6<<widgetRun7<<widgetRun8;
    //widgetList.at(index)->layout()->removeWidget();
    if(widgetList.at(index-1)->layout()!=NULL)
    {
        disconnect(channelMap[index-1],SIGNAL(deleteChannelSettings(int)),this,SLOT(deleteChannel(int)));
        delete channelMap[index-1];//一定要先删除该控件  否则无法从界面中删除该控件
        widgetList.at(index-1)->layout()->removeWidget(channelMap[index-1]);
        delete widgetList.at(index-1)->layout();
        widgetList.at(index-1)->repaint();
        widgetList.at(index-1)->update();

        delete runningMap[index-1];
        widgetRunList.at(index-1)->layout()->removeWidget(runningMap[index-1]);
        delete widgetRunList.at(index-1)->layout();
        widgetRunList.at(index-1)->repaint();
    }
    else
        qDebug()<<"no layout";

}
