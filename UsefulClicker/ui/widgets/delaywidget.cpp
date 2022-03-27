#include <QPainter>
#include <QGridLayout>
#include <QDir>
#include <QGuiApplication>
#include <QLabel>
#include "delaywidget.h"
#include "ui/widgets/svgwidget.h"

static SvgWidget* widget;
static QLabel* label;

DelayWidget::DelayWidget(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::Widget );
    setAttribute(Qt::WA_MouseTracking, true);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_WState_WindowOpacitySet);
    setAttribute(Qt::WA_PaintOnScreen);
    setCursor(Qt::CrossCursor);
    frame = 0;
    //setWindowOpacity(0.3);
//    setTra

    QString filename = QDir::currentPath() + "/ui/widgets/delay_widget.svg";
    widget = new SvgWidget(this);
    if( widget->SvgLoad(filename) )
    {
        widget->LoadDocument(filename);
        QGridLayout* layout = new QGridLayout();
        layout->addWidget(widget);
        setLayout(layout);
        widget->show();

    }
    startTimer(10);
}

void DelayWidget::showEvent(QShowEvent* event)
{
    showFullScreen();
    QScreen* screen = QGuiApplication::screens()[0];
    QRect r(0,0,500,500);
    r.moveTopLeft(screen->geometry().center() - QPoint(250,250));
    screenshot = screen->grabWindow(0,0,0,screen->geometry().width(), screen->geometry().height());
    screenshot.save("pixm.png");
    setGeometry(r);
}

#define rnd(a,b) ((((float)rand() /RAND_MAX) - 0.5f) * a + b)

void DelayWidget::timerEvent(QTimerEvent* event)
{
    QRectF elipse = widget->getEllipse("path1042-1-5");
    //qDebug() << "read elipse " << elipse;
    double r = rnd(10,100);
    QPointF c = elipse.center();
    elipse.setCoords(c.x()-r,c.y()-r,c.x()+r,c.y()+r);
    widget->setEllipse("path1042-1-5", elipse);


    QRectF elipse2 = widget->getEllipse("path1042");
    //qDebug() << "read elipse " << elipse;
    r = rnd(100,200);
    c = elipse2.center();
    elipse2.setCoords(c.x()-r,c.y()-r,c.x()+r,c.y()+r);
    widget->setEllipse("path1042", elipse2);

    QRadialGradient g = widget->getRadialGradient("radialGradient1451");
    double r1 = rnd(300,500);
    g.setRadius(r1);
    //g.setFocalRadius(r1);
    widget->setRadialGradient("radialGradient1451", g);


    widget->LoadRenderDOM();

    qDebug() << "frame " << frame;
    qDebug() << "r " << r;
    qDebug() << "r1 " << r1;
    //qDebug() << "write elipse " << elipse;
    repaint();
    frame++;
}
void DelayWidget::mouseMoveEvent(QMouseEvent* event)
{
}
void DelayWidget::mousePressEvent(QMouseEvent* event)
{
}
void DelayWidget::paintEvent( QPaintEvent* event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.fillRect(rect(),Qt::red);
    QScreen* screen = QGuiApplication::screens()[0];
    QRect r(0,0,500,500);
    r.moveTopLeft(screen->geometry().center() - QPoint(250,250));
    painter.drawPixmap(rect(), screenshot, r);
    event->accept();


    /*
    QPainter painter;
    QRect rect(0,0,bigTimerRadius,bigTimerRadius);
    rect.moveCenter(this->rect().center());
    painter.setPen(Qt::black);

    painter.drawEllipse(rect);
    */

}
void DelayWidget::wheelEvent(QWheelEvent* event)
{
}

