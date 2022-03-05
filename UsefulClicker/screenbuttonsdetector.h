#ifndef SCREENBUTTONSDETECTOR_H
#define SCREENBUTTONSDETECTOR_H

#include <vector>
#include <QDialog>
#include <QShowEvent>
#include <QTimerEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QWheelEvent>

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
    int kernel_size;

    void DetectButtons(int screenNum);
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

private:
    Ui::ScreenButtonsDetector *ui;
};

#endif // SCREENBUTTONSDETECTOR_H
