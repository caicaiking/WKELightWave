#ifndef CLSLCRCNNTWINDOW_H
#define CLSLCRCNNTWINDOW_H

#include "ui_clsLcrCnntWindow.h"
///
/// \brief  这个是为了建立LCR表和电脑的连接，
///         在开始之前调用 setupConnection()，如果返回了false
///         再次初始化此类显示，让用户去设定仪器的IP地址，重新
///         建立连接。
///
class clsLcrCnntWindow : public QDialog, private Ui::clsLcrCnntWindow
{
    Q_OBJECT

public:
    explicit clsLcrCnntWindow(QWidget *parent = 0);
    static bool setupConnection();
private slots:
    void readSettings();
    void saveSettings();
    void on_btnTest_clicked();
};

#endif // CLSLCRCNNTWINDOW_H
