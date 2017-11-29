#include "clsLabel.h"

clsLabel::clsLabel(QWidget *parent) : QLabel(parent)
{

}

void clsLabel::mousePressEvent(QMouseEvent *e)
{
}

void clsLabel::mouseReleaseEvent(QMouseEvent *e)
{
     if(e->button()==Qt::LeftButton)
        emit labelClicked();

}
