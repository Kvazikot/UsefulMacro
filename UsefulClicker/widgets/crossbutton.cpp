#include "widgets/crossbutton.h"

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
    //icon_enabled = icon_enabled.scaled(200, 200, Qt::AspectRatioMode::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(QPixmap::fromImage(icon_enabled));
    emit click(sequence);
}
