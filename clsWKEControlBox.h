#ifndef CLSWKECONTROLBOX_H
#define CLSWKECONTROLBOX_H

#include "ui_clsWKEControlBox.h"

class clsWKEControlBox : public QDialog, private Ui::clsWKEControlBox
{
    Q_OBJECT

public:
    explicit clsWKEControlBox(QWidget *parent = 0);

    QVariantMap parseCondition(QString condition);
    QStringList getLCRCondition() const;

private slots:
    void labelLCR1Clicked();
    void labelLCR2Clicked();
    void labelLCR3Clicked();
    void labelLCR4Clicked();
    //void labelHV1Clicked();
    void labelHV2Clicked();
    void labelHV3Clicked();
    void labelHV4Clicked();
private slots:
    void on_btnOK_clicked();
    void on_btnCancel_clicked();

    void on_rbtnLCR1_clicked();
    void on_rbtnHV1_clicked();

private:
    QStringList lcrCondition;

};

#endif // CLSWKECONTROLBOX_H
