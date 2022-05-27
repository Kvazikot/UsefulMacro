#ifndef SCREENBUTTONSDETECTOR_H
#define SCREENBUTTONSDETECTOR_H

#include <vector>
#include <QDialog>
#include <QShowEvent>
#include <QTimerEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QWheelEvent>
#include "ui/dialogtype.h"
#include "cv/rectangle_descriptor.h"

namespace Ui {
class ScreenButtonsDetector;
}


class ScreenButtonsDetector : public QDialog
{
    Q_OBJECT

public:
    explicit ScreenButtonsDetector(QWidget *parent = nullptr, int screenNumber=0);
    QWidget* parent_dialog;
    QMap<QString, QString> attrs;
    std::vector<QRect> rects;
    QPoint mpos;
    QRect selected_rect;
    int screenNum;
    RectangleDescriptor rectangle_descriptor;
    void Hide();
    void Show();
    void keyPressEvent(QKeyEvent* event);
    bool setScreenNumber(int n);
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
    void init();

signals:
    void sigSetAttrs(QMap<QString, QString> attrs);

private:
    Ui::ScreenButtonsDetector *ui;
};

#endif // SCREENBUTTONSDETECTOR_H
