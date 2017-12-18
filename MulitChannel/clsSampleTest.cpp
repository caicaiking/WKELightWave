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
}

void clsSampleTest::on_btnClose_clicked()
{
    this->reject();
    this->close();
}


void clsSampleTest::on_btnTrig_clicked()
{
    btnTrig->setEnabled(false);

    QList<double> res = meter->getOriginZA();
    if(res.length()>=2)
    {
        doubleType dt;
        dt.setData(res.at(0));
        lblTest1->setText(dt.formateToString()+ publicUtility::getSuffix("Z"));
        dt.setData(res.at(1));
        lblTest2->setText(dt.formateToString()+ publicUtility::getSuffix("A"));
    }

    btnTrig->setEnabled(true);
    btnTrig->setFocus();

}

void clsSampleTest::on_btnOk_clicked()
{
    this->accept();
}
