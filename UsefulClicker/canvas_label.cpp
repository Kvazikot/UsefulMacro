
/*
+ - - - + - + - -
+ - + - + copyright by Vladimir Baranov (Kvazikot)  <br>
+ - + - + email: vsbaranov83@gmail.com  <br>
+ - + - + github: https://github.com/Kvazikot/UsefulMacro/  <br>
```
                          )            (
                         /(   (\___/)  )\
                        ( #)  \ ('')| ( #
                         ||___c\  > '__||
                         ||**** ),_/ **'|
                   .__   |'* ___| |___*'|
                    \_\  |' (    ~   ,)'|
                     ((  |' /(.  '  .)\ |
                      \\_|_/ <_ _____> \______________
                       /   '-, \   / ,-'      ______  \
              b'ger   /      (//   \\)     __/     /   \
                                          './_____/
```
*/

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
