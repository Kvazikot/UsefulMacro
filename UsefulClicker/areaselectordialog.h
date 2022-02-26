#ifndef AREASELECTORDIALOG_H
#define AREASELECTORDIALOG_H

#include <QDialog>
#include <QPaintEvent>
#include <QMouseEvent>
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
    void selectTargetImage();
    void setScreen(int n);
    void fullScreen();
    ~AreaSelectorDialog();

signals:
    void sigSetRect(QRect rect);

private slots:
    void on_doneButton_clicked();
    void slotFullScreen();

private:
    Ui::AreaSelectorDialog *ui;
};

#endif // AREASELECTORDIALOG_H
