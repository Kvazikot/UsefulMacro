#ifndef AREABUTTON_H
#define AREABUTTON_H

#include <QWidget>
#include <QMouseEvent>
#include "widgets/keyboardbutton.h"

class AreaButton : public KeyboardButton
{
    Q_OBJECT
public:
    explicit AreaButton(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *ev) override;
public slots:
    void areaSelected(QRect rect, QImage& rect_image);

signals:
    void click(QString button);
};


#endif // AREABUTTON_H
