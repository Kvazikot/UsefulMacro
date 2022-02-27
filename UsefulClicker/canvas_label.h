#ifndef CANVAS_LABEL_H
#define CANVAS_LABEL_H

#include <QLabel>
#include <QPaintEvent>

class Canvas_Label : public QLabel
{
    Q_OBJECT
public:
    explicit Canvas_Label(QWidget *parent = nullptr);
    void setMarkedImage();
    void paintEvent(QPaintEvent* event);

signals:

};

#endif // CANVAS_LABEL_H
