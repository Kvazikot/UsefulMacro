#ifndef CROSSBUTTON_H
#define CROSSBUTTON_H

#include <QWidget>
#include <QMouseEvent>
#include "widgets/keyboardbutton.h"

class CrossButton : public KeyboardButton
{
    Q_OBJECT
public:
    explicit CrossButton(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *ev) override;
signals:
    void click(QString button);
};


#endif // CROSSBUTTON_H
