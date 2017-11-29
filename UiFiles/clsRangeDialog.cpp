#include "clsRangeDialog.h"

clsRangeDialog::clsRangeDialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
}

QString clsRangeDialog::getRange() const
{
    return range;
}

void clsRangeDialog::on_btnAuto_clicked()
{
    this->range=tr("自动");
    this->accept();
}

void clsRangeDialog::on_btn1_clicked()
{
    this->range="1";
    this->accept();
}

void clsRangeDialog::on_btn2_clicked()
{
    this->range="2";
    this->accept();
}

void clsRangeDialog::on_btn3_clicked()
{
    this->range="3";
    this->accept();
}

void clsRangeDialog::on_btn4_clicked()
{
    this->range="4";
    this->accept();
}

void clsRangeDialog::on_btn5_clicked()
{
    this->range="5";
    this->accept();
}

void clsRangeDialog::on_btn6_clicked()
{
    this->range="6";
    this->accept();
}

void clsRangeDialog::on_btn7_clicked()
{
    this->range="7";
    this->accept();
}

//void clsRangeDialog::on_btnClose_clicked()
//{
//    this->close();
//}
