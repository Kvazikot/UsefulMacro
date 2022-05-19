#include <windows.h>

#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include "cv/dspmodule.h"
#include "mousedialog.h"
#include "interpreter/interpreter.h"
#include "ui_mousedialog.h"

MouseDialog::MouseDialog(QWidget *parent) :
    QDialog(parent), screenNum(0),
    ui(new Ui::MouseDialog)
{
    setWindowFlags(Qt::Widget );
    setAttribute(Qt::WA_AlwaysStackOnTop, true);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_WState_WindowOpacitySet);
    setAttribute(Qt::WA_PaintOnScreen); // not needed in Qt 5.2 and up
    setCursor(Qt::CrossCursor);
    userWindow = GetFocus();
    ui->setupUi(this);
    ui->delayWidget->hide();
    withDelayFlag = false;

    QImage bg_image(300,300,QImage::Format_ARGB32);
    bg_image.fill(QColor(100,100,100,0));

    dsp = new DspModule();

    startTimer(10);
}


void MouseDialog::keyPressEvent(QKeyEvent* event)
{
    event->accept();

    //show delay widget if F2
    if( event->key() == Qt::Key_F2)
    {
        withDelayFlag = true;
        ui->delayWidget->setHidden(!ui->delayWidget->isHidden());
        if( ui->delayWidget->isHidden() )
            ui->keySequenceLabel_2->setText( "Press F2 again to accept delay values");
        else
            ui->keySequenceLabel_2->setText( "Press F2 to set delays");
        return;
    }
    //if( event->key() == Qt::Key_Delete)  clear();


    Qt::KeyboardModifiers m = event->modifiers();
    sequence = "";
    if( m.testFlag(Qt::ControlModifier) )
        sequence="ctrl+";
    if( m.testFlag(Qt::ControlModifier) && m.testFlag(Qt::ShiftModifier))
    {
       sequence="ctrl+shift+";
    }
    sequence+=QKeySequence(event->key()).toString();
    //setStyleSheet("");
    QString html = QString("<html><head/><body><p><span style=\" font-size:24pt; font-weight:700; color:#00007f;\">%1</span></p></body></html>")
                   .arg(sequence);
    ui->keySequenceLabel->setText(html);
}

void MouseDialog::keyReleaseEvent(QKeyEvent *event)
{
    QMap<QString, QString> attrs;
    if( event->key() == Qt::Key_F2)
    {
        if( ui->delayWidget->isHidden() )
        {
            attrs["delay_fixed"] = QString::number(ui->delayWidget->delay_fixed);
            attrs["delay_random"] = QString::number(ui->delayWidget->delay_random);
            attrs["repeats"] = QString::number(ui->delayWidget->repeats);
            QString str = "Press F2 to set delays. <br/> delay_fixed = " + attrs["delay_fixed"] + "<br/>";
            str+= "delay_random = " + attrs["delay_random"] + "<br/>";
            str+= "repeats = " + attrs["repeats"];
            QString html = QString("<html><head/><body><p><span style=\" font-size:18pt; font-weight:700; color:#00007f;\">%1</span></p></body></html>")
                           .arg(str);
            ui->keySequenceLabel_2->setText(html);
        }
        else
        {
            QString str = "Press F2 to set delays.";
            QString html = QString("<html><head/><body><p><span style=\" font-size:18pt; font-weight:700; color:#00007f;\">%1</span></p></body></html>")
                           .arg(str);
            ui->keySequenceLabel_2->setText(html);
        }
        return;
    }

    attrs["event"] = "hotkey";
    attrs["hotkey"] = sequence;
    attrs["withDelayFlag"] = QString::number(withDelayFlag);
    emit sigSetAttrs(attrs);
    close();
}


void MouseDialog::mousePressEvent(QMouseEvent* event)
{
    //process selected rectangle
    QMap<QString, QString> attrs;
    attrs["event"] = "click";
    attrs["withDelayFlag"] = QString::number(withDelayFlag);
    mpos = event->pos();

    attrs["x"] = QString::number(mpos.x());
    attrs["y"] = QString::number(mpos.y());
    attrs["delay_fixed"] = QString::number(ui->delayWidget->delay_fixed);
    attrs["delay_random"] = QString::number(ui->delayWidget->delay_random);
    attrs["repeats"] = QString::number(ui->delayWidget->repeats);
    button = event->button();
    if( button == Qt::MouseButton::LeftButton )
        attrs["button"] = "left";
    if( button == Qt::MouseButton::RightButton )
        attrs["button"] = "right";
    if( button == Qt::MouseButton::MiddleButton )
        attrs["button"] = "middle";
    emit sigSetAttrs(attrs);
    //hide();
    //MouseClick(mpos, button);
   // SetFocus(userWindow);
    //QTimer::singleShot(100, this, SLOT(afterclick()));
    //QTimer::singleShot(1000, this, SLOT(show()));

    close();

    event->accept();
}

void MouseDialog::afterclick()
{
    userWindow = GetFocus();
    //MouseClick(mpos, button);
}

void MouseDialog::mouseMoveEvent(QMouseEvent* event)
{
    mpos = event->globalPosition().toPoint();
    repaint();
    event->accept();
}

void MouseDialog::wheelEvent(QWheelEvent* event)
{
    QMap<QString, QString> attrs;
    auto s = QString("%1").arg(event->angleDelta().y());
    attrs["event"] = "scroll";
    attrs["delta"] = s;
    attrs["delay_fixed"] = QString::number(ui->delayWidget->delay_fixed);
    attrs["delay_random"] = QString::number(ui->delayWidget->delay_random);
    attrs["repeats"] = QString::number(ui->delayWidget->repeats);
    attrs["withDelayFlag"] = QString::number(withDelayFlag);
    emit sigSetAttrs(attrs);
    close();
}


void MouseDialog::paintEvent( QPaintEvent* event)
{
    QPainter painter(this);


    frame++;
}

void MouseDialog::timerEvent(QTimerEvent* event)
{
    repaint();
    event->accept();
}


void MouseDialog::showEvent(QShowEvent* event)
{
    //dsp->detectButtons(screenNum, dsp->kernel_size, rects);
    showFullScreen();
    event->accept();
}


MouseDialog::~MouseDialog()
{
    delete ui;
}
