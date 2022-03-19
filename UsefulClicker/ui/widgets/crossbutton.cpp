#include "ui/widgets/crossbutton.h"

//---------------------------------------------------------------------------------

CrossButton::CrossButton(QWidget *parent)
    : KeyboardButton(parent)
{
    setContextMenuPolicy(Qt::PreventContextMenu);
    repaint();
}

void CrossButton::mousePressEvent(QMouseEvent *ev)
{
    QString sequence;
    setPixmap(QPixmap::fromImage(icon_enabled));
    emit click(sequence);
    ev->accept();
}
