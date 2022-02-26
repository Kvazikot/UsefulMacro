#ifndef AREASELECTORDIALOG_H
#define AREASELECTORDIALOG_H

#include <QDialog>
#include <QPaintEvent>
#include <QMouseEvent>

namespace Ui {
class AreaSelectorDialog;
}

class AreaSelectorDialog : public QDialog
{
    Q_OBJECT

public:
    QPoint startWndCoords;
    QPoint prevMouseCoords;
    bool dragStarted;
    explicit AreaSelectorDialog(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    ~AreaSelectorDialog();

private slots:
    void on_doneButton_clicked();


private:
    Ui::AreaSelectorDialog *ui;
};

#endif // AREASELECTORDIALOG_H
