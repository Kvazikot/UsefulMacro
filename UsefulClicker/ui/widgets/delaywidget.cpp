#include <QPainter>

#include "delaywidget.h"

DelayWidget::DelayWidget(QWidget *parent)
    : QWidget{parent}
{
}

void DelayWidget::showEvent(QShowEvent* event)
{
}
void DelayWidget::timerEvent(QTimerEvent* event)
{
}
void DelayWidget::mouseMoveEvent(QMouseEvent* event)
{
}
void DelayWidget::mousePressEvent(QMouseEvent* event)
{
}
void DelayWidget::paintEvent( QPaintEvent* event)
{
    QPainter painter;
    QRect rect(0,0,bigTimerRadius,bigTimerRadius);
    rect.moveCenter(this->rect().center());
    painter.setPen(Qt::black);

    painter.drawEllipse(rect);

}
void DelayWidget::wheelEvent(QWheelEvent* event)
{
}

