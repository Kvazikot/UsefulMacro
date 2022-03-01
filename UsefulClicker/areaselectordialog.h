/*
+ - - - + - + - -
+ - + - + copyright by Vladimir Baranov (Kvazikot)  <br>
+ - + - + email: vsbaranov83@gmail.com  <br>
+ - + - + github: https://github.com/Kvazikot/UsefulMacro/  <br>
```
                          )            (
                         /(   (\___/)  )\
                        ( #)  \ ('')| ( #
                         ||___c\  > '__||
                         ||**** ),_/ **'|
                   .__   |'* ___| |___*'|
                    \_\  |' (    ~   ,)'|
                     ((  |' /(.  '  .)\ |
                      \\_|_/ <_ _____> \______________
                       /   '-, \   / ,-'      ______  \
              b'ger   /      (//   \\)     __/     /   \
                                          './_____/
```
*/

#ifndef AREASELECTORDIALOG_H
#define AREASELECTORDIALOG_H

#include <QDialog>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QShowEvent>

namespace Ui {
class AreaSelectorDialog;
}

class AreaSelectorDialog : public QDialog
{
    Q_OBJECT

public:
    QPoint startWndCoords;
    QPoint prevMouseCoords;
    QPixmap screenshot;
    QRect  selectedRect;
    bool dragStarted;
    bool fullscreenMode;
    int  screenNum;

    explicit AreaSelectorDialog(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void selectTargetImage();
    void setScreen(int n);
    void fullScreen();
    void selectByWindow();
    QPixmap makeScreenshot();
    ~AreaSelectorDialog();

signals:
    void sigSetRect(QRect rect, QPointF p);
    void sigSetAreaRect(QRect rect, QPointF p);

private slots:
    void on_doneButton_clicked();
    void slotFullScreen();

private:
    Ui::AreaSelectorDialog *ui;
};

#endif // AREASELECTORDIALOG_H
