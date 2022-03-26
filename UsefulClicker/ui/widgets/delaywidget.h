#ifndef DELAYWIDGET_H
#define DELAYWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QShowEvent>
#include <QWheelEvent>



class DelayWidget : public QWidget
{
    Q_OBJECT
public:
    QPixmap screenshot;
    int bigTimerRadius = 150;
    explicit DelayWidget(QWidget *parent = nullptr);
    void showEvent(QShowEvent* event);
    void timerEvent(QTimerEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent* event);


signals:

};

#endif // DELAYWIDGET_H
