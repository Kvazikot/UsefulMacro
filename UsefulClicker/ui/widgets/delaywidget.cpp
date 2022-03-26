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
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_WState_WindowOpacitySet);
    setAttribute(Qt::WA_PaintOnScreen);
    setCursor(Qt::CrossCursor);
    //setWindowOpacity(0.3);
//    setTra


    widget = new SvgWidget(this);
    if( widget->SvgLoad(QDir::currentPath() + "/ui/widgets/delay_widget.svg") )
    {

        QGridLayout* layout = new QGridLayout();
        layout->addWidget(widget);
        setLayout(layout);
        widget->show();

    }
    startTimer(100);
}

void DelayWidget::showEvent(QShowEvent* event)
{
   // showFullScreen();
    QScreen* screen = QGuiApplication::screens()[0];
    QRect r(0,0,500,500);
    r.moveTopLeft(screen->geometry().center() - QPoint(250,250));
    screenshot = screen->grabWindow(0,0,0,screen->geometry().width(), screen->geometry().height());
    screenshot.save("pixm.png");
    setGeometry(r);
}
void DelayWidget::timerEvent(QTimerEvent* event)
{
    repaint();
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

