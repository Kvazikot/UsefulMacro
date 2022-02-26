#include <QPainter>
#include <QPushButton>
#include "areaselectordialog.h"
#include "ui_areaselectordialog.h"

AreaSelectorDialog::AreaSelectorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AreaSelectorDialog)
{
    setWindowFlags(Qt::Widget);
    setParent(0); // Create TopLevel-Widget
    setAttribute(Qt::WA_NoSystemBackground, true);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_WState_WindowOpacitySet);
    setAttribute(Qt::WA_PaintOnScreen); // not needed in Qt 5.2 and up
    ui->setupUi(this);
    QImage bg_image(300,300,QImage::Format_ARGB32);
    bg_image.fill(QColor(100,100,100,100));
    ui->label->setPixmap(QPixmap::fromImage(bg_image));

    QPushButton* done_button = new QPushButton(this);
    done_button->setGeometry(0,0,100,100);
    done_button->setText("done!");
    done_button->show();
    connect(done_button, SIGNAL(clicked()), this, SLOT(on_doneButton_clicked()));

}

void AreaSelectorDialog::mouseReleaseEvent(QMouseEvent *event)
{
    dragStarted = false;
}

void AreaSelectorDialog::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton )
    {
        dragStarted = true;
        prevMouseCoords = event->globalPosition().toPoint();
        startWndCoords = QPoint(geometry().x(), geometry().y());

    }
}

void AreaSelectorDialog::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    if(  dragStarted )
    {
        QPoint delta = prevMouseCoords - event->pos();
        move( event->globalPosition().toPoint()  - QPoint(rect().width()/2,rect().height()/2));
    }
    prevMouseCoords = event->pos();
}

AreaSelectorDialog::~AreaSelectorDialog()
{
    delete ui;
}

void AreaSelectorDialog::paintEvent(QPaintEvent* event)
{

}

void AreaSelectorDialog::on_doneButton_clicked()
{
   close();
}

