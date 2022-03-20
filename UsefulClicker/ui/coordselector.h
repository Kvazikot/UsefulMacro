#ifndef COORDSELECTOR_H
#define COORDSELECTOR_H

#include <QDialog>
#include <QMap>

namespace Ui {
class CoordSelector;
}

class CoordSelector : public QDialog
{
    Q_OBJECT

public:
    explicit CoordSelector(QWidget *parent = nullptr);
    ~CoordSelector();
    QPoint mpos;
    QRect selected_rect;
    QCursor cursor;

    QPixmap cursor_pixmap;
    int n_rects = 10;
    int frame;

    void animate();
    void generate_rects();
    void showEvent(QShowEvent* event) override;
    void timerEvent(QTimerEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent( QPaintEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
public slots:
    void on_doneButton_clicked();
signals:
    void sigSetAttrs(QMap<QString, QString> attrs);


private:
    Ui::CoordSelector *ui;
};

#endif // COORDSELECTOR_H
