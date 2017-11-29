#include "clsWK6500Items.h"

clsWK6500Items::clsWK6500Items(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);

}

int clsWK6500Items::getIndex() const
{
    return this->index;
}

//void clsWK6500Items::setBtnVisable()
//{
//    this->btnOFF->setVisible(false);
//}

void clsWK6500Items::on_btnC_clicked()
{
    func="C";
    index=0;
    this->accept();
}

void clsWK6500Items::on_btnD_clicked()
{
    func="D";
    index=1;
    this->accept();
}

void clsWK6500Items::on_btnL_clicked()
{
    func="L";
    index=2;
    this->accept();
}

void clsWK6500Items::on_btnQ_clicked()
{
    func="Q";
    index=3;
    this->accept();
}

void clsWK6500Items::on_btnR_clicked()
{
    func="R";
    index=4;
    this->accept();
}

void clsWK6500Items::on_btnX_clicked()
{
    func="X";
    index=5;
    this->accept();
}

void clsWK6500Items::on_btnG_clicked()
{
    func="G";
    index=6;
    this->accept();
}

void clsWK6500Items::on_btnB_clicked()
{
    func="B";
    index=7;
    this->accept();
}

void clsWK6500Items::on_btnZ_clicked()
{
    func="Z";
    index=8;
    this->accept();
}

void clsWK6500Items::on_btnA_clicked()
{
    func="A";
    index=9;
    this->accept();
}

void clsWK6500Items::on_btnY_clicked()
{
    func="Y";
    index=10;
    this->accept();
}

void clsWK6500Items::on_btnOFF_clicked()
{
    func="OFF";
    index=11;
    this->accept();
}
