#ifndef CLSWARNINGBOX_H
#define CLSWARNINGBOX_H

#include "ui_clsWarningBox.h"

class clsWarningBox : public QDialog, private Ui::clsWarningBox
{
    Q_OBJECT

public:
    explicit clsWarningBox(QWidget *parent = 0);

    static int warning(QWidget *parent , QString title, QString info);



    int getSelected() const;

private slots:
    void on_btnUpdate_clicked();

    void on_btnNewStep_clicked();

    void on_btnCancel_clicked();

private:
    int selected;
};

#endif // CLSWARNINGBOX_H
