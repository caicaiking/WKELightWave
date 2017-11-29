#ifndef CLSLABEL_H
#define CLSLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include <QObject>

class clsLabel : public QLabel
{
    Q_OBJECT
public:
    explicit clsLabel(QWidget *parent=0);

    void mousePressEvent(QMouseEvent *e);
protected:
    void mouseReleaseEvent(QMouseEvent *e);
signals:
    void labelClicked();

};

#endif // CLSLABEL_H
