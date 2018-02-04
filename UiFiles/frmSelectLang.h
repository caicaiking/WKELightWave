#ifndef FRMSELECTLANG_H
#define FRMSELECTLANG_H

#include "ui_frmSelectLang.h"

class frmSelectLang : public QDialog, private Ui::frmSelectLang
{
    Q_OBJECT

public:
    explicit frmSelectLang(QWidget *parent = 0);
    static int getLanguage(QWidget *parent = nullptr);
    int getChoice()
    {
        return choice;
    }


private slots:
    void on_btnOk_clicked();
private:
    int choice;
};

#endif // FRMSELECTLANG_H
