#ifndef SCREENBUTTONSDETECTOR_H
#define SCREENBUTTONSDETECTOR_H

#include <vector>
#include <QDialog>
#include <QShowEvent>
#include <QTimerEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QWheelEvent>
#include "ui/dialogtype.h"

namespace Ui {
class ScreenButtonsDetector;
}

class ScreenButtonsDetector : public QDialog
{
    Q_OBJECT

public:
    explicit ScreenButtonsDetector(QWidget *parent = nullptr);
    std::vector<QRect> rects;
    QPoint mpos;
    QRect selected_rect;

    void showEvent(QShowEvent* event);
    void timerEvent(QTimerEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void paintEvent( QPaintEvent* event);
    void wheelEvent(QWheelEvent* event);
    ~ScreenButtonsDetector();

public slots:
    void on_doneButton_clicked();
    void setImage();
signals:
    void sigSetAttrs(QMap<QString, QString> attrs);

private:
    Ui::ScreenButtonsDetector *ui;
};

#endif // SCREENBUTTONSDETECTOR_H
