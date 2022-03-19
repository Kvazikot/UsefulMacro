#include <QMouseEvent>
#include "mousebutton.h"

//---------------------------------------------------------------------------------

MouseButton::MouseButton(QWidget *parent)
    : KeyboardButton(parent)
{
    /*
    icon_enabled = QImage(":/images/mouse_default.png");
    icon_enabled = icon_enabled.scaled(50,height());
    icon_disabled = icon_enabled;
    */
    //icon_disabled.invertPixels();
    setContextMenuPolicy(Qt::PreventContextMenu);

    repaint();
}

void MouseButton::mousePressEvent(QMouseEvent *ev)
{
    button = ev->button();
    QString sequence;
    if( ev->button() == Qt::MouseButton::LeftButton )
    {
        icon_enabled = QImage(":/images/mouse_left_click.png");
        sequence = "Left button";
    }
    if( ev->button() == Qt::MouseButton::RightButton )
    {
        icon_enabled = QImage(":/images/mouse_right_click.png");
        sequence = "Right button";
    }
    //QTimer::singleShot(500,this,SIGNAL(accept()));

    icon_enabled = icon_enabled.scaled(50,height());
    setPixmap(QPixmap::fromImage(icon_enabled));
    emit click(sequence);

}

void MouseButton::wheelEvent(QWheelEvent *event)
{
    event->accept();
    icon_enabled = QImage(":/images/mouse_scroll.png");
    setPixmap(QPixmap::fromImage(icon_enabled));
}