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

ScreenButtonsDetector::ScreenButtonsDetector(QWidget *parent, int screenNumber):
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
    this->screenNum = screenNumber;
    bg_image.fill(QColor(100,100,100,0));
    //ui->label->setPixmap(QPixmap::fromImage(bg_image));
    //ui->label->setScaledContents(false);
    //fullscreenMode = false;
    //DspModule
    dsp = new DspModule();

    startTimer(10);
}

bool ScreenButtonsDetector::setScreenNumber(int n)
{
    if( QGuiApplication::screens().size() < n)
    {
        screenNum = 0;
        setScreen(QGuiApplication::screens()[screenNum]);
        return false;
    }
    screenNum = n;
    setScreen(QGuiApplication::screens()[screenNum]);
    return true;
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

    dsp->kernel_size = std::clamp(p, 1, 40);
    rects.clear();
    dsp->detectButtons(screenNum, dsp->kernel_size, rects);
    //dsp->detectButtons(screenNum, dsp->kernel_size, rects, true);

}

void ScreenButtonsDetector::paintEvent( QPaintEvent* event)
{
    QPainter painter(this);
    if( screenNum > QGuiApplication::screens().size() ) return;
    QScreen* screen = QGuiApplication::screens()[screenNum];

    for( auto r: rects)
    {
        if( r.contains(mpos) )
        {
            selected_rect = r;
            painter.fillRect(r, Qt::red);
        }
        else
        {
            if( screenNum == 1)
                r.translate(-screen->geometry().width(), 0);
            QPointF p1 = QPointF(this->mapFromGlobal(r.topLeft()));
            QPointF p2 = QPointF(this->mapFromGlobal(r.bottomRight()));
            QRectF scaledRect = QRectF(p1,p2);
            painter.fillRect(scaledRect, Qt::green);
            //qDebug() << __FUNCTION__ << "r trqanslated" << r;

        }
    }

    QFont f;
    f.setBold(true);
    f.setPixelSize(24);
    painter.setFont(f);
    painter.setPen(Qt::red);
    event->accept();

    QString message;
    message = QString("kernel_size = %1 Select image to search. Use mouse wheel for fine tuning. logicalDotsPerInch = %2 ").arg(dsp->kernel_size).arg(screen->logicalDotsPerInch());
    if( (screen->logicalDotsPerInch()) != 96)
        message = "Please set screen scale to 100% in Desktop settings!";

    if( screenNum == 1)
        painter.drawText(rect().x()+100,600, message);
    else
        painter.drawText(rect().x()+100,600, message);


   // painter.drawText(geometry().left(),1000, s);
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
    //setWindowState(Qt::WindowFullScreen);

    //QTimer::singleShot(500, this, SLOT(slotFullScreen()));
    if( screenNum > QGuiApplication::screens().size() ) return;
    QScreen* screen = QGuiApplication::screens()[screenNum];
    QRect r = screen->geometry();
    //r.moveLeft(screen->geometry().width()-rect().left());
    qDebug() << __FUNCTION__ << "screen geometry" << screen->geometry();
    qDebug() << __FUNCTION__ << "ScreenButtonsDetector window  geometry" << geometry();
    setGeometry(r);
    setScreen(screen);
    setCursor(Qt::CrossCursor);
    dsp->detectButtons(screenNum, dsp->kernel_size, rects);
    event->accept();
    showFullScreen();
    //QTimer::singleShot(3000, this,  SLOT(setImage()));
}

ScreenButtonsDetector::~ScreenButtonsDetector()
{
    delete ui;
}
