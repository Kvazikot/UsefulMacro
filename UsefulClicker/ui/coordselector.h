#ifndef COORDSELECTOR_H
#define COORDSELECTOR_H

#include <QDialog>
#include <QMap>
#include <QElapsedTimer>
//#include <QSound>

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
    QRectF hit_rect;
    QCursor cursor;
    //QSound bullet_sound;
    QPixmap cursor_pixmap;
    QElapsedTimer timeSinceHit;
    QPoint hitPoint;
    int n_rects = 10;
    int score = 10;
    int frame;
    int n_hited;
    bool hit;

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
    void closeDelaySlot();
    void clickDelay();
signals:
    void sigSetAttrs(QMap<QString, QString> attrs);


private:
    Ui::CoordSelector *ui;
};

#endif // COORDSELECTOR_H
