#include "clsLabel.h"

clsLabel::clsLabel(QWidget *parent) : QLabel(parent)
{

}

void clsLabel::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
        emit labelClicked();
}
