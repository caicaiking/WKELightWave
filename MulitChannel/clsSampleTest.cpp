#include "clsSampleTest.h"
#include "doubleType.h"
#include "publicUtility.h"
clsSampleTest::clsSampleTest(clsInstrumentCalibration *value, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    meter = value;

    lblItem1->setText("Z");
    lblItem2->setText("A");
    lblTest1->setText("");
    lblTest2->setText("");
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_btnTrig_clicked()));

}

void clsSampleTest::setOption(int opt)
{
    this->opt = opt;
    btnTrig->setEnabled(true);
    timer->start();
}

void clsSampleTest::on_btnClose_clicked()
{
    timer->stop();
    this->reject();
    this->close();
}


void clsSampleTest::on_btnTrig_clicked()
{

    if(!btnTrig->isEnabled())
        return ;

    btnTrig->setEnabled(false);
    QList<double> res = meter->getOriginZA();
    if(res.length()>=2)
    {
        doubleType dt;
        dt.setData(res.at(0));
        lblTest1->setText(dt.formateToString()+ publicUtility::getSuffix("Z"));
        dt.setData(res.at(1));
        lblTest2->setText(dt.formateToString()+ publicUtility::getSuffix("A"));

        switch (opt) {
        case 0:
            if(res.at(0) >= 10E3)
            {
                timer->stop();
                this->accept();
            }
            break;
        case 1:
            if(res.at(0) <= 50)
            {
                timer->stop();
                this->accept();
            }
            break;
        case 2:
            if(res.at(0)<= 110 && res.at(0)>=90)
            {
                timer->stop();
                this->accept();
            }
            break;
        case 3:
            if(res.at(1)>= -130 && res.at(1)<=-80)
            {
                timer->stop();
                this->accept();
            }
            break;
        default:
            break;
        }
    }

    btnTrig->setEnabled(true);
    btnTrig->setFocus();

}

void clsSampleTest::on_btnOk_clicked()
{
    timer->stop();
    this->accept();
}
