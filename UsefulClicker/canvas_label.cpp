#include <QPainter>
#include <QPainterPath>
#include "canvas_label.h"

Canvas_Label::Canvas_Label(QWidget *parent)
    : QLabel{parent}
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setText("first line\nsecond line");
}

void Canvas_Label::setMarkedImage()
{
    //return;


}


void Canvas_Label::paintEvent(QPaintEvent* event)
{
    /*
   QPainter painter(this);

   painter.fillRect(rect(), QColor(10,55,10,255));
   painter.drawText(rect().center(),"RESIZE THIS WINDOW TO SELECT SEARCH AREA!");
    qDebug() << " REPAINT ";
   painter.end();
   event->accept();
   */
}
