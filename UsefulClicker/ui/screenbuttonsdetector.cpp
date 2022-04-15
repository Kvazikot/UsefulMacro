#include <QScreen>
#include <QPushButton>
#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include <QDir>
#include <algorithm>
#include <opencv2/imgproc.hpp>
#include "cv/dspmodule.h"
#include "ui/screenbuttonsdetector.h"
#include "ui/ui_screenbuttonsdetector.h"

using namespace cv;
static DspModule* dsp;

ScreenButtonsDetector::ScreenButtonsDetector(QWidget *parent):
    QDialog(parent),
    ui(new Ui::ScreenButtonsDetector)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Widget );
    setParent(0); // Create TopLevel-Widget
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_WState_WindowOpacitySet);
    setAttribute(Qt::WA_PaintOnScreen); // not needed in Qt 5.2 and up
    ui->setupUi(this);
    QImage bg_image(300,300,QImage::Format_ARGB32);
    bg_image.fill(QColor(100,100,100,0));
    //ui->label->setPixmap(QPixmap::fromImage(bg_image));
    //ui->label->setScaledContents(false);
    //screenNum = 0;
    //fullscreenMode = false;
    //DspModule
    dsp = new DspModule();

    startTimer(10);


}

void ScreenButtonsDetector::mousePressEvent(QMouseEvent* event)
{
    event->accept();

    //process selected rectangle
    QMap<QString, QString> attrs;
    QString v = QString("QRect(%1,%2,%3,%4)").arg(selected_rect.left())
            .arg(selected_rect.top())
            .arg(selected_rect.width())
            .arg(selected_rect.height());
    attrs["area"] = v;
    QString filename;
    dsp->saveImage(selected_rect, filename);
    attrs["filename"] = filename;
    attrs["nodename"] = "clickimg";
    //rect_image.save(str);



    emit sigSetAttrs(attrs);


    close();

}

void ScreenButtonsDetector::mouseMoveEvent(QMouseEvent* event)
{
    mpos = event->globalPosition().toPoint();
    repaint();
    event->accept();
}

void ScreenButtonsDetector::wheelEvent(QWheelEvent* event)
{
    int p = dsp->kernel_size;
    if( event->angleDelta().y() > 0)
       p-=1;
    else
        p+=1;

    dsp->kernel_size = std::clamp(p, 2, 40);
    rects.clear();
    dsp->detectButtons(0, dsp->kernel_size, rects);

}

void ScreenButtonsDetector::paintEvent( QPaintEvent* event)
{
    QPainter painter(this);
    for( auto r: rects)
    {
        if( r.contains(mpos) )
        {
            selected_rect = r;
            painter.fillRect(r, Qt::red);
        }
        else
            painter.fillRect(r, Qt::green);
    }

    QFont f;
    f.setBold(true);
    f.setPixelSize(24);
    painter.setFont(f);
    painter.setPen(Qt::red);
    event->accept();


    QString s = QString("kernel_size = %1 Select image to search. Use mouse wheel for fine tuning. ").arg(dsp->kernel_size);
    painter.drawText(0,1000, s);
}

void ScreenButtonsDetector::timerEvent(QTimerEvent* event)
{
    repaint();
    event->accept();
}

void ScreenButtonsDetector::on_doneButton_clicked()
{
    close();
}

void ScreenButtonsDetector::setImage()
{
    //ui->label->setPixmap(QPixmap("out.png"));
    //ui->label->repaint();
}

void ScreenButtonsDetector::showEvent(QShowEvent* event)
{
    dsp->detectButtons(0, dsp->kernel_size, rects);
    showFullScreen();
    event->accept();
    //QTimer::singleShot(3000, this,  SLOT(setImage()));
}

ScreenButtonsDetector::~ScreenButtonsDetector()
{
    delete ui;
}
