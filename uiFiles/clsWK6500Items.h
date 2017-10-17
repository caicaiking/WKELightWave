#ifndef CLSWK6500ITEMS_H
#define CLSWK6500ITEMS_H

#include "ui_clsWK6500Items.h"


class clsWK6500Items : public QDialog, private Ui::clsWK6500Items
{
    Q_OBJECT

public:
    explicit clsWK6500Items(QWidget *parent = 0);
    QString getFunc()
    {
        return func;
    }
    int getIndex() const;
    //void setBtnOFFVisable();

private slots:
    void on_btnC_clicked();
    void on_btnD_clicked();
    void on_btnL_clicked();
    void on_btnQ_clicked();
    void on_btnR_clicked();
    void on_btnX_clicked();
    void on_btnG_clicked();
    void on_btnB_clicked();
    void on_btnZ_clicked();
    void on_btnA_clicked();
    void on_btnY_clicked();
    void on_btnOFF_clicked();

private:
    QString func;
    int index;
};

#endif // CLSWK6500ITEMS_H
