#include <QPainter>
#include <QPushButton>
#include <QScreen>
#include <QTimer>
#include "windows.h"
#include "areaselectordialog.h"
#include "ui_areaselectordialog.h"
#include <opencv2/opencv.hpp>

using namespace cv;

AreaSelectorDialog::AreaSelectorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AreaSelectorDialog)
{
    setWindowFlags(Qt::Widget );
    setParent(0); // Create TopLevel-Widget
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_WState_WindowOpacitySet);
    setAttribute(Qt::WA_PaintOnScreen); // not needed in Qt 5.2 and up
    ui->setupUi(this);
    QImage bg_image(300,300,QImage::Format_ARGB32);
    bg_image.fill(QColor(100,100,100,200));
    ui->label->setPixmap(QPixmap::fromImage(bg_image));
    screenNum = 0;

    QPushButton* done_button = new QPushButton(this);
    done_button->setGeometry(0,0,100,100);
    QSizePolicy pol;
    pol.setHorizontalPolicy(QSizePolicy::Minimum);
    done_button->setSizePolicy(pol);
    done_button->setText("done!");
    done_button->show();
    connect(done_button, SIGNAL(clicked()), this, SLOT(on_doneButton_clicked()));

}

void AreaSelectorDialog::setScreen(int n)
{
    screenNum = n;
}

void AreaSelectorDialog::slotFullScreen()
{

    QScreen* screen = QGuiApplication::screens()[screenNum];
    setGeometry(screen->geometry());
    ui->label->setGeometry(screen->geometry());
    setCursor(Qt::CrossCursor);

}

void AreaSelectorDialog::fullScreen()
{
    fullscreenMode = true;
    show();
    ui->label->setVisible(false);
    QTimer::singleShot(500, this, SLOT(slotFullScreen()));
}


QPixmap AreaSelectorDialog::makeScreenshot()
{
    //makeScreenshot();
    QScreen* screen = QGuiApplication::screens()[screenNum];
    screenshot = screen->grabWindow(0,0,0,screen->geometry().width(), screen->geometry().height());
    return screenshot;
    //screenshot.save("screenshot.png");

}

void AreaSelectorDialog::selectTargetImage()
{
    //QDesktopWidget* desktop = QApplication::desktop();
    int screenNum = 0;
    QScreen* screen = QGuiApplication::screens()[screenNum];
    setGeometry(screen->geometry());

}

void AreaSelectorDialog::showEvent(QShowEvent* event)
{
    SetWindowPos
    (
        (HWND)winId(),
        HWND_TOPMOST,
        geometry().top(),
        geometry().left(),
        geometry().width(),
        geometry().height(),
        SWP_SHOWWINDOW
    );
    event->accept();
}

void AreaSelectorDialog::mouseReleaseEvent(QMouseEvent *event)
{
    dragStarted = false;
    event->accept();
    QPoint p = startWndCoords - prevMouseCoords;

    //selectedRect.setTopLeft(startWndCoords);
    //selectedRect.setBottomRight(prevMouseCoords);
    selectedRect = QRect();
    // 1 case
     if( (startWndCoords.x() - prevMouseCoords.x()) < 0 )
         if( (prevMouseCoords.y() - startWndCoords.y()) > 0 )
         {
             selectedRect.setTopLeft(startWndCoords);
             selectedRect.setBottomRight(prevMouseCoords);
         }

     // 2 case
     if( (startWndCoords.x() - prevMouseCoords.x()) < 0 )
         if( (prevMouseCoords.y() - startWndCoords.y()) < 0 )
         {
             selectedRect.setBottomLeft(startWndCoords);
             selectedRect.setTopRight(prevMouseCoords);
         }

     // 3 case
     if( (startWndCoords.x() - prevMouseCoords.x()) > 0 )
         if( (startWndCoords.y() - prevMouseCoords.y()) < 0 )
         {
             selectedRect.setTopRight(startWndCoords);
             selectedRect.setBottomLeft(prevMouseCoords);
         }

     // 4 case
     if( (startWndCoords.x() - prevMouseCoords.x()) < 0 )
         if( (startWndCoords.y() - prevMouseCoords.y()) > 0 )
         {
             selectedRect.setBottomLeft(startWndCoords);
             selectedRect.setTopRight(prevMouseCoords);
         }


    emit sigSetRect(selectedRect);
    if(fullscreenMode) close();
}

void AreaSelectorDialog::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton )
    {
        dragStarted = true;
        prevMouseCoords = event->globalPosition().toPoint();
        startWndCoords = prevMouseCoords;
    }
}

void AreaSelectorDialog::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    if(  dragStarted )
    {
        //QPoint delta = prevMouseCoords - event->pos();
        if(!fullscreenMode)
          move( event->globalPosition().toPoint()  - QPoint(rect().width() / 2,rect().height() / 2));
    }
    prevMouseCoords = event->pos();
    repaint();
}

AreaSelectorDialog::~AreaSelectorDialog()
{
    delete ui;
}

void AreaSelectorDialog::paintEvent(QPaintEvent* event)
{
   QPainter painter(this);

   selectedRect.setTopLeft(startWndCoords);
   selectedRect.setBottomRight(prevMouseCoords);
   painter.fillRect(selectedRect, QColor(100,255,100,255));

   painter.end();
   event->accept();
}

void AreaSelectorDialog::on_doneButton_clicked()
{
   close();
}

