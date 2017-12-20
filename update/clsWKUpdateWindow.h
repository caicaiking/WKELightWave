#ifndef CLSWKUPDATEWINDOW_H
#define CLSWKUPDATEWINDOW_H

#include "ui_clsWKUpdateWindow.h"

class QSimpleUpdater;
class clsWKUpdateWindow : public QDialog, private Ui::clsWKUpdateWindow
{
    Q_OBJECT

public:
    explicit clsWKUpdateWindow(QWidget *parent = 0);

public slots:
    void checkForUpdates();
    void updateChangeLog(const QString & url);
private slots:
    void on_btnClose_clicked();

    void on_btnCheckUpdate_clicked();

    void on_btnAboutQt_clicked();

private:
    QSimpleUpdater *mUpdater;
};

#endif // CLSWKUPDATEWINDOW_H
