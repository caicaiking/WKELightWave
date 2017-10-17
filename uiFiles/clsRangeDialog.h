#ifndef CLSRANGEDIALOG_H
#define CLSRANGEDIALOG_H

#include "ui_clsRangeDialog.h"

class clsRangeDialog : public QDialog, private Ui::clsRangeDialog
{
    Q_OBJECT

public:
    explicit clsRangeDialog(QWidget *parent = 0);
    QString getRange() const;

private slots:
    void on_btnAuto_clicked();

    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_btn4_clicked();

    void on_btn5_clicked();

    void on_btn6_clicked();

    void on_btn7_clicked();

   // void on_btnClose_clicked();

private:
    QString range;
};

#endif // CLSRANGEDIALOG_H
