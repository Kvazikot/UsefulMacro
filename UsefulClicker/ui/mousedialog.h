#ifndef MOUSEDIALOG_H
#define MOUSEDIALOG_H

#include <QDialog>
#include "cv/dspmodule.h"

namespace Ui {
class MouseDialog;
}

class MouseDialog : public QDialog
{
    Q_OBJECT

public:
    Qt::MouseButton button;
    QPoint mpos;
    QRect selected_rect;
    QCursor cursor;
    QPixmap cursor_pixmap;
    HWND userWindow;
    std::vector<QRect> rects;
    int screenNum;
    QString sequence;
    DspModule* dsp;
    int frame;
    bool withDelayFlag;

    void showEvent(QShowEvent* event) override;
    void timerEvent(QTimerEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent( QPaintEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    explicit MouseDialog(QWidget *parent = nullptr);
    ~MouseDialog();

signals:
    void sigSetAttrs(QMap<QString, QString> attrs);

public slots:
    void afterclick();

private:
    Ui::MouseDialog *ui;
};

#endif // MOUSEDIALOG_H
