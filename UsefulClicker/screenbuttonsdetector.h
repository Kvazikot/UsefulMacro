#ifndef SCREENBUTTONSDETECTOR_H
#define SCREENBUTTONSDETECTOR_H

#include <vector>
#include <QDialog>
#include <QShowEvent>
#include <QTimerEvent>
#include <QMouseEvent>
#include <QPaintEvent>

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
    void DetectButtons(int screenNum);
    void showEvent(QShowEvent* event);
    void timerEvent(QTimerEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void paintEvent( QPaintEvent* event);
    ~ScreenButtonsDetector();

public slots:
    void on_doneButton_clicked();
    void setImage();

private:
    Ui::ScreenButtonsDetector *ui;
};

#endif // SCREENBUTTONSDETECTOR_H
