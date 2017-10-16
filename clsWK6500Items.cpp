#include "clsWK6500Items.h"

clsWK6500Items::clsWK6500Items(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

}

//void clsWK6500Items::setBtnVisable()
//{
//    this->btnOFF->setVisible(false);
//}

void clsWK6500Items::on_btnC_clicked()
{
    func="C";
    this->accept();
}

void clsWK6500Items::on_btnD_clicked()
{
    func="D";
    this->accept();
}

void clsWK6500Items::on_btnL_clicked()
{
    func="L";
    this->accept();
}

void clsWK6500Items::on_btnQ_clicked()
{
    func="Q";
    this->accept();
}

void clsWK6500Items::on_btnR_clicked()
{
    func="R";
    this->accept();
}

void clsWK6500Items::on_btnX_clicked()
{
    func="X";
    this->accept();
}

void clsWK6500Items::on_btnG_clicked()
{
    func="G";
    this->accept();
}

void clsWK6500Items::on_btnB_clicked()
{
    func="B";
    this->accept();
}

void clsWK6500Items::on_btnZ_clicked()
{
    func="Z";
    this->accept();
}

void clsWK6500Items::on_btnA_clicked()
{
    func="A";
    this->accept();
}

void clsWK6500Items::on_btnY_clicked()
{
    func="Y";
    this->accept();
}

void clsWK6500Items::on_btnOFF_clicked()
{
    func="OFF";
    this->accept();
}
