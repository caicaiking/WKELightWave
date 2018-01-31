#ifndef CLSCALIBRATIONDBOP_H
#define CLSCALIBRATIONDBOP_H

#include <QObject>
#include <QSqlDatabase>

class clsCalDb : public QObject
{
    Q_OBJECT
public:

    static clsCalDb * getInst();

    QString getStrDataBaseName() const;
    void setStrDataBaseName(const QString &value);
    bool openDataBase();
    bool initTable();
    bool insertRecord(double freq, QPoint channal, double z, double a, QString type);
    bool removeAllData();
    QString getTableName();
    bool deleteRecord(double freq, QPoint channel, QString type);

    QList<double> getCalData(double freq, QPoint channal, QString type);
signals:

public slots:

private:
    explicit clsCalDb(QObject *parent = 0);
    static clsCalDb * _instance;

    QString strDataBaseName;
    bool isDataBaseIsOpen;
    bool hasTable;
    QString ps(QPoint p);
};

#endif // CLSCALIBRATIONDBOP_H
