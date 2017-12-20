#include "clsWKUpdateWindow.h"
#include <QSimpleUpdater.h>
#include "publicUtility.h"
static const QString DEFS_URL = "https://raw.githubusercontent.com/Leroy888/DelphiTestSystem/abama/Installer/updates.json";

clsWKUpdateWindow::clsWKUpdateWindow(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle(qApp->applicationName());
    lblVersion->setText("\nV" + publicUtility::getVersion());

    mUpdater = QSimpleUpdater::getInstance();
    connect(mUpdater,SIGNAL(checkingFinished(QString)),this,SLOT(updateChangeLog(QString)));

}


void clsWKUpdateWindow::checkForUpdates()
{
    QString version = publicUtility::getVersion();
    bool customAppCast = false;
    bool downloaderEnable = true;
    bool notifyOnFinish = false;
    bool notifyOnUpdate = true;

    mUpdater->setModuleVersion(DEFS_URL, version);
    mUpdater->setNotifyOnFinish(DEFS_URL, notifyOnFinish);
    mUpdater->setNotifyOnUpdate(DEFS_URL, notifyOnUpdate);
    mUpdater->setUseCustomAppcast(DEFS_URL,customAppCast);
    mUpdater->setDownloaderEnabled(DEFS_URL, downloaderEnable);

    mUpdater->checkForUpdates(DEFS_URL);
}

void clsWKUpdateWindow::updateChangeLog(const QString &url)
{
    if(url == DEFS_URL)
    {
        this->changelogText->setText(mUpdater->getChangelog(url));
        grpChangeLog->setVisible(true);
    }
}


void clsWKUpdateWindow::on_btnClose_clicked()
{
    this->close();
}

void clsWKUpdateWindow::on_btnCheckUpdate_clicked()
{
    this->checkForUpdates();
}

void clsWKUpdateWindow::on_btnAboutQt_clicked()
{
    qApp->aboutQt();
}
