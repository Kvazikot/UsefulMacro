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
    QPointF mpos, mlocalPos, c;

    int bigTimerRadius = 150;
    int frame=0;
    int repeats=0;
    explicit DelayWidget(QWidget *parent = nullptr);
    void showEvent(QShowEvent* event);
    void timerEvent(QTimerEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;


signals:

};

#endif // DELAYWIDGET_H
