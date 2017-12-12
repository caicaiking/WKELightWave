#ifndef CLSSELECTFTDICHIP_H
#define CLSSELECTFTDICHIP_H

#include "ui_clsSelectFtdiChip.h"

class clsSelectFtdiChip : public QDialog, private Ui::clsSelectFtdiChip
{
    Q_OBJECT

public:
    explicit clsSelectFtdiChip(QWidget *parent = 0);
    void setItems(QStringList items);

    static int selectIndex(const QStringList& items, bool *res, QWidget* parent =0);
    int getSelect();
private slots:
    void on_btnCancel_clicked();
    void on_btnOk_clicked();
};

#endif // CLSSELECTFTDICHIP_H
