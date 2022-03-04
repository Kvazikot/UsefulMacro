#include <QScreen>
#include <QPushButton>
#include <QPainter>
#include <QTimer>
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

    QPushButton* done_button = new QPushButton(this);
    done_button->setGeometry(0,0,100,100);
    QSizePolicy pol;
    pol.setHorizontalPolicy(QSizePolicy::Minimum);
    done_button->setSizePolicy(pol);
    done_button->setText("done!");
    done_button->show();
    connect(done_button, SIGNAL(clicked()), this, SLOT(on_doneButton_clicked()));    

    //DspModule
    dsp = new DspModule();

    startTimer(10);


}

void ScreenButtonsDetector::mouseMoveEvent(QMouseEvent* event)
{
    mpos = event->globalPosition().toPoint();
    repaint();
    event->accept();
}

void ScreenButtonsDetector::paintEvent( QPaintEvent* event)
{
    QPainter painter(this);
    for( auto r: rects)
    {
        if( r.contains(mpos) )
            painter.fillRect(r, Qt::red);
        else
            painter.fillRect(r, Qt::green);
    }
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
    QImage out_image(100,100,QImage::Format_ARGB32);
    dsp->detectButtons(0, out_image, rects);
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
