#ifndef MOUSEBUTTON_H
#define MOUSEBUTTON_H

#include <QWidget>
#include "widgets/keyboardbutton.h"


class MouseButton : public KeyboardButton
{
    Q_OBJECT
public:
    Qt::MouseButton button;
    explicit MouseButton(QWidget *parent = nullptr);
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *ev) override;
signals:
    void click(QString button);
};


#endif // MOUSEBUTTON_H
