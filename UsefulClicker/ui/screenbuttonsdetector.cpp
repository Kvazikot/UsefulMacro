#include <QScreen>
#include <QPushButton>
#include <QRandomGenerator>
#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include <QDir>
#include <algorithm>
#include <opencv2/imgproc.hpp>
#include "cv/dspmodule.h"
#include "ui/screenbuttonsdetector.h"
#include "ui/widgets/dimensionswidget.h"
#include "ui/ui_screenbuttonsdetector.h"

using namespace cv;
static DspModule* dsp;

ScreenButtonsDetector::ScreenButtonsDetector(QWidget *parent, int screenNumber):
    QDialog(parent), parent_dialog(parent),
    ui(new Ui::ScreenButtonsDetector)
{
    ui->setupUi(this);
    attrs["nodename"] = "clickimg";
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
    Hide();

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

void ScreenButtonsDetector::Hide()
{
    setWindowOpacity(0);
    ui->tipLabel->hide();
    parent_dialog->hide();
}

void ScreenButtonsDetector::Show()
{
    setWindowOpacity(0.400000);
    ui->tipLabel->show();
    //parent_dialog->show();
}

void ScreenButtonsDetector::mousePressEvent(QMouseEvent* event)
{
    event->accept();

    //process selected rectangle
    if( attrs["nodename"] == "clickimg" )
    {
        QString filename;
        dsp->saveImage(selected_rect, filename);
        filename = filename.replace("\"","");
        attrs["targetImg"] = filename;
        attrs["kernel_size"] = QString::number(dsp->kernel_size);
        emit sigSetAttrs(attrs);
        parent_dialog->show();
        close();
    }

    if( attrs["nodename"] == "clickrect" )
    {
        attrs["kernel_size"] = QString::number(dsp->kernel_size);
        rectangle_descriptor.writeToMap(attrs);
        train.Generate(4, selected_rect, rects);
        emit sigSetAttrs(attrs);
    }


}

void ScreenButtonsDetector::keyPressEvent(QKeyEvent* event)
{
    event->accept();
    if( event->key() == Qt::Key::Key_F2)
    {
        DimensionsWidget* dimensions = new DimensionsWidget(this);
        attrs["nodename"] = "clickrect";
        QRect r = rect();
        QPoint c = r.center();
        QRect dimensions_geometry = QRect(c.x()-r.width()/2,
                                          c.y()-r.height()/2,
                                          r.width()/2,
                                          r.height()/2);
        dimensions_geometry = rect();
        dimensions->setGeometry(dimensions_geometry);
        dimensions->showFullScreen();


    }

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

int calc_area(QRect r) {return r.width()*r.height(); }

void Train::computeRectangleMaps(std::vector<QRect>& in_rects, t_rectmap& out_xMap, t_rectmap& out_yMap)
{
    for(int n_rect = 0; n_rect < in_rects.size(); n_rect++ )
    {
        auto& r = in_rects[n_rect];
        for(int x=r.topLeft().x(); x!=r.topRight().x(); x++ )
             out_xMap[x].insert(n_rect);
        for(int y=r.topLeft().y(); y!=r.bottomLeft().y(); y++ )
           out_yMap[y].insert(n_rect);
    }
    for(auto it=out_xMap.begin(); it!=out_xMap.end(); it++)
    {
        int maxAreaIndex;
        int maxArea = std::numeric_limits<int>::min();
        for(auto n_rect = it->second.begin(); n_rect != it->second.end(); n_rect++)
        {
            int area = calc_area(in_rects[*n_rect]);
            if(  area > maxArea)
            {
                maxArea = area;
                maxAreaIndex = *n_rect;
            }
        }
        it->second.clear();
        it->second.insert(maxAreaIndex);

    }
}

QPoint randomPointInRect(QRect& r)
{
    QRandomGenerator rng(QDateTime::currentDateTime().toMSecsSinceEpoch());
    return QPoint(r.left() + rng.bounded(r.width()),
                  r.top() + rng.bounded(r.height()));
}

void Train::Generate(int n_Wagons, QRect startingRect, std::vector<QRect>& in_rects)
{
    computeRectangleMaps(in_rects, xMap, yMap);

    Wagons.clear();
    Wagons.resize(n_Wagons);

    Wagons[0] = Wagon(startingRect, randomPointInRect(startingRect));

    QRandomGenerator rng(QDateTime::currentDateTime().toMSecsSinceEpoch());
    for(int i=1; i < n_Wagons; i++)
    {
        auto& randomRect = in_rects[rng.bounded(in_rects.size()-1)];
        Wagons[i] = Wagon(randomRect, randomPointInRect(startingRect));
    }

}

void ScreenButtonsDetector::drawTrain(QPainter& painter, Train& train, QColor boarder_color, QColor fill_color)
{
    painter.save();
    auto prev_junction_point = QPoint();
    for(auto& w : train.Wagons)
    {
        painter.setPen(boarder_color);
        painter.drawRect(w.bounds);
        painter.setPen(Qt::red);
        painter.drawLine(w.junction_point, prev_junction_point);
        painter.fillRect(w.bounds, fill_color);
        prev_junction_point = w.junction_point;
    }
    painter.restore();
}


void ScreenButtonsDetector::paintEvent( QPaintEvent* event)
{
    QPainter painter(this);
    if( screenNum > QGuiApplication::screens().size() ) return;
    QScreen* screen = QGuiApplication::screens()[screenNum];

    int n = 0;
    for( auto r: rects)
    {
        if( r.contains(mpos) )
        {
            selected_rect = r;
            rectangle_descriptor.setRect(selected_rect);
            rectangle_descriptor.setNumber(n);
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
            QString similarity = QString::number(n);
            QFont f;
            f.setBold(true);
            f.setPixelSize(24);
            painter.setFont(f);
            painter.setPen(Qt::yellow);
            if( attrs["nodename"] == "clickrect" )
            {
                drawTrain(painter, train, Qt::black, Qt::yellow);
                painter.drawText(scaledRect.topLeft(), similarity);
            }
            //qDebug() << __FUNCTION__ << "r trqanslated" << r;

        }
        n++;
    }

    QFont f;
    f.setBold(true);
    f.setPixelSize(24);
    painter.setFont(f);
    painter.setPen(Qt::red);
    event->accept();

    QString message;
    message = QString("kernel_size = %1 Select image to search. Use mouse wheel for fine tuning. ");
    message = message.arg(QString::number(dsp->kernel_size));

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


void ScreenButtonsDetector::init()
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
    showFullScreen();
    Show();

}


void ScreenButtonsDetector::showEvent(QShowEvent* event)
{
    QTimer::singleShot(500, this,  SLOT(init()));
    event->accept();
}

ScreenButtonsDetector::~ScreenButtonsDetector()
{
    delete ui;
    delete dsp;
}
