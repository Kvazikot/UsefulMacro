#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include "coordselector.h"
#include "ui_coordselector.h"

static std::vector<QRectF> rects;
static std::vector<QVector2D> velocitys;
static std::vector<int> sprite_indexes;
static QImage sprite[3];

CoordSelector::CoordSelector(QWidget *parent) :
    QDialog(0),
    ui(new Ui::CoordSelector)
{
    setWindowFlags(Qt::Widget );
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_WState_WindowOpacitySet);
    setAttribute(Qt::WA_PaintOnScreen); // not needed in Qt 5.2 and up
    setCursor(Qt::CrossCursor);
    ui->setupUi(this);

    QImage bg_image(300,300,QImage::Format_ARGB32);
    bg_image.fill(QColor(100,100,100,0));

    sprite[0] = QImage(":/images/hitler_face.png");
    sprite[1] = QImage(":/images/putler.jpg");
    sprite[2] = QImage(":/images/stalin.jpg");
    //sprite[0] = QImage();
    //sprite[1] = QImage();
    //sprite[2] = QImage();

    for(int i=0; i < n_rects+11; i++)
    {
        rects.push_back(QRect(1,1,100,100));
        velocitys.push_back(QVector2D(1,1));
        sprite_indexes.push_back(0);
    }
    generate_rects();
    frame = 0;

    startTimer(10);

}

#define rnd ((float)rand()/RAND_MAX)

void CoordSelector::generate_rects()
{
    for(int i=0; i < n_rects; i++)
    {
        float x,y,w,h;
        x =  rnd * (float)rect().width();
        y =  rnd * (float)rect().height();
        w = 200. * rnd;
        h = w;
        QRectF r(x,y,w,h);
        rects[i] = r;
        float scale = rnd * 10;
        velocitys[i] = QVector2D(scale*rnd,scale*rnd);
        sprite_indexes[i] = qRound(rnd * 3);
    }

}

CoordSelector::~CoordSelector()
{
    delete ui;
}


void CoordSelector::mousePressEvent(QMouseEvent* event)
{

    //process selected rectangle
    QMap<QString, QString> attrs;
    attrs["x"] = QString::number(mpos.x());
    attrs["y"] = QString::number(mpos.y());
    emit sigSetAttrs(attrs);

    close();

    event->accept();
}

void CoordSelector::mouseMoveEvent(QMouseEvent* event)
{
    mpos = event->globalPosition().toPoint();
    qDebug() << mpos;
    repaint();
    event->accept();
}

void CoordSelector::wheelEvent(QWheelEvent* event)
{

}


void CoordSelector::animate()
{

}

void CoordSelector::paintEvent( QPaintEvent* event)
{
    QPainter painter(this);
    QRect r4(mpos.x(), mpos.y(),100,100);
    //qDebug() << __FUNCTION__ << r;
    r4.moveCenter(mpos);

    if( frame > n_rects )
        frame = 0;

    // draw rects
    //int i = frame;
    for(int i=0; i < n_rects; i++)
    {
        QRectF r = rects[i];
        float x = r.left() + velocitys[i].x() ;
        float y = r.top() + velocitys[i].y() ;
        rects[i] = QRectF(x,y,r.width(),r.height());
        painter.fillRect(rects[i], Qt::red);
        int j = sprite_indexes[i];
        painter.drawImage(rects[i], sprite[j]);
    }

    painter.fillRect(r4, Qt::red);

    QFont f;
    f.setBold(true);
    f.setPixelSize(24);
    painter.setFont(f);
    painter.setPen(Qt::red);


    QString s = QString("Left click to select coordinates.");
    painter.drawText(0,1000, s);
    event->accept();
    frame++;
}

void CoordSelector::timerEvent(QTimerEvent* event)
{
    repaint();
    event->accept();
}

void CoordSelector::on_doneButton_clicked()
{
    close();
}

void CoordSelector::showEvent(QShowEvent* event)
{
    showFullScreen();
    event->accept();
}

