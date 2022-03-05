#include <QScreen>
#include <QPushButton>
#include <QPainter>
#include <QTimer>
#include <algorithm>
#include <opencv2/imgproc.hpp>
#include "dspmodule.h"
#include "screenbuttonsdetector.h"
#include "ui_screenbuttonsdetector.h"

using namespace cv;
static DspModule* dsp;

ScreenButtonsDetector::ScreenButtonsDetector(QWidget *parent) :
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
    kernel_size = 4;
    startTimer(10);


}

void ScreenButtonsDetector::mousePressEvent(QMouseEvent* event)
{
    event->accept();

    //process selected rectangle

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
    int p = kernel_size;
    if( event->angleDelta().y() > 0)
       p-=1;
    else
        p+=1;

    kernel_size = std::clamp(p, 2, 40);
    rects.clear();
    dsp->detectButtons(0, kernel_size, rects);

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


    QString s = QString("x = %1 Select image to search. Use mouse wheel for fine tuning. ").arg(kernel_size);
    painter.drawText(0,1000, s);
}

void ScreenButtonsDetector::timerEvent(QTimerEvent* event)
{
    //ui->label->setGeometry(geometry());
    //ui->label->setPixmap(QPixmap("out.png"));
    //ui->label->repaint();
    repaint();
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
    dsp->detectButtons(0, kernel_size, rects);
    showFullScreen();
    //QTimer::singleShot(3000, this,  SLOT(setImage()));

}

void ScreenButtonsDetector::DetectButtons(int screenNum)
{
}

ScreenButtonsDetector::~ScreenButtonsDetector()
{
    delete ui;
}
