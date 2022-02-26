#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimerEvent>

namespace Ui {
class MainWindow;
}

struct Summary
{
    double corelation;
    QSize  size1;
    QSize  size2;
    QPoint coordinates;
    Summary()
    {}
    Summary(double corelation, QSize  size1, QSize  size2, QPoint coordinates)
        :corelation(corelation), size1(size1), size2(size2), coordinates(coordinates)
    {
    }
    QString toString()
    {
        return QString("corelation = %1  coordinates: x = %2 y = %3 SearchIn.size=%4,%5 TargetIn.size=%6,%7").
                arg(corelation).arg(coordinates.x()).arg(coordinates.y()).
                arg(size1.width()).arg(size1.height()).
                arg(size2.width()).arg(size1.height());


    }

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QImage SearchIn, TargetIn, Out;
    Summary summary;
    explicit MainWindow(QWidget *parent = nullptr);
    void timerEvent(QTimerEvent* event);
    ~MainWindow();

public slots:
    void computeDCorrelation();
    void slotSetImage(QImage& img, int n_screen);
public:
    Ui::MainWindow *ui;    
};

#endif // MAINWINDOW_H
