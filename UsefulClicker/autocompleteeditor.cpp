#include <QImage>
#include <QPainter>
#include <QWheelEvent>
#include <QCoreApplication>
#include <QLabel>
#include <QTimer>
#include <QHBoxLayout>
#include "autocompleteeditor.h"
#include "areaselectordialog.h"

//---------------------------------------------------------------------------------

AreaButton::AreaButton(QWidget *parent)
    : KeyboardButton(parent)
{
    setContextMenuPolicy(Qt::PreventContextMenu);
    setIcon(":/images/area_icon.png", true, true);
    repaint();
}

void AreaButton::areaSelected(QRect rect, QImage& rect_image)
{
    QPainter painter(&rect_image);
    painter.drawImage(geometry(), rect_image);
}

void AreaButton::mousePressEvent(QMouseEvent *ev)
{
    if ( ev->button() == Qt::MouseButton::LeftButton )
    {
        AreaSelectorDialog* dlg = new AreaSelectorDialog(0);
        //dlg->selectTargetImage();
        QRect curernt_geometry = dlg->geometry();
        curernt_geometry.setWidth(curernt_geometry.width()/2);
        curernt_geometry.setHeight(curernt_geometry.height()/2);
        dlg->setGeometry(curernt_geometry);
        dlg->show();
        dlg->prevMouseCoords = curernt_geometry.center();
        dlg->repaint();

        //void sigSetRect(QRect rect, QPointF p);
        //void sigSetAreaRect(QRect rect, QPointF p);
        connect(dlg, SIGNAL(sigSetImageRect(QRect rect, QPointF p)), this, SLOT(areaSelected(QRect rect, QPointF p)));
    }

    QString sequence;
    emit click(sequence);
}


//---------------------------------------------------------------------------------

CrossButton::CrossButton(QWidget *parent)
    : KeyboardButton(parent)
{
    setContextMenuPolicy(Qt::PreventContextMenu);
    repaint();
}

void CrossButton::mousePressEvent(QMouseEvent *ev)
{
    QString sequence;
    icon_enabled = icon_enabled.scaled(200, 200, Qt::AspectRatioMode::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(QPixmap::fromImage(icon_enabled));
    emit click(sequence);
}

//---------------------------------------------------------------------------------

MouseButton::MouseButton(QWidget *parent)
    : KeyboardButton(parent)
{
    /*
    icon_enabled = QImage(":/images/mouse_default.png");
    icon_enabled = icon_enabled.scaled(50,height());
    icon_disabled = icon_enabled;
    */
    //icon_disabled.invertPixels();
    setContextMenuPolicy(Qt::PreventContextMenu);

    repaint();
}

void MouseButton::mousePressEvent(QMouseEvent *ev)
{
    button = ev->button();
    QString sequence;
    if( ev->button() == Qt::MouseButton::LeftButton )
    {
        icon_enabled = QImage(":/images/mouse_left_click.png");
        sequence = "Left button";
    }
    if( ev->button() == Qt::MouseButton::RightButton )
    {
        icon_enabled = QImage(":/images/mouse_right_click.png");
        sequence = "Right button";
    }
    //QTimer::singleShot(500,this,SIGNAL(accept()));

    icon_enabled = icon_enabled.scaled(50,height());
    setPixmap(QPixmap::fromImage(icon_enabled));
    emit click(sequence);

}

void MouseButton::wheelEvent(QWheelEvent *event)
{
    event->accept();
    icon_enabled = QImage(":/images/mouse_scroll.png");
    setPixmap(QPixmap::fromImage(icon_enabled));
}


//---------------------------------------------------------------------------------

KeyboardButton::KeyboardButton(QWidget *parent)
    : QLabel(parent)
{
    mouseOverFlag = false;
    state = false;
    setScaledContents(true);
    setGeometry(width()-10,0,50,20);
    startTimer(101);
}

void KeyboardButton::setIcon(QString filename, bool invert_pixels, bool init_state)
{
    icon_enabled = QImage(filename);
    icon_enabled = icon_enabled.scaled(50,height());
    icon_disabled = icon_enabled;
    if(invert_pixels)
        icon_disabled.invertPixels();
    if(init_state)
        setPixmap(QPixmap::fromImage(icon_enabled));
    else
        setPixmap(QPixmap::fromImage(icon_disabled));
}

void KeyboardButton::mousePressEvent(QMouseEvent *ev)
{
    state = !state;
    mouseOverFlag = true;
    if( state )
        emit clicked();
    else
    {
        //emit accept();
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
        QCoreApplication::sendEvent(this, &keyEvent);

    }
    ev->accept();
}

void KeyboardButton::timerEvent(QTimerEvent* event)
{
    event->accept();
    if( mouseOverFlag )
        setPixmap(QPixmap::fromImage(icon_enabled));

}

void KeyboardButton::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
}

void KeyboardButton::mouseMoveEvent(QMouseEvent *ev)
{
}

void KeyboardButton::setDisable()
{
    setPixmap(QPixmap::fromImage(icon_disabled));
    mouseOverFlag = false;
}


//----------------------------------------------------------------------------------

ComboEdit::ComboEdit(QWidget *parent) :
    QLineEdit(parent)
{
    keyboard_but = new KeyboardButton(0);
    keyboard_but->setIcon(":/images/keyboard_icon.png", true, false);
    setContextMenuPolicy(Qt::PreventContextMenu);
    connect(keyboard_but, SIGNAL(clicked()),this, SLOT(slotKeyboardClick()));
    connect(keyboard_but, SIGNAL(accept()),this, SLOT(slotAccepted()));

    mouse_but = new MouseButton(0);
    mouse_but->setIcon(":/images/mouse_default.png", true, true);
    connect(mouse_but, SIGNAL(click(QString)), this, SLOT(slotSetSequence(QString)));
    connect(mouse_but, SIGNAL(accept()),this, SLOT(slotAccepted()));

    cross_but = new CrossButton(0);
    cross_but->state = true;
    cross_but->setIcon(":/images/templ_cross.png", true, true);
    connect(cross_but, SIGNAL(click(QString)), this, SLOT(slotSetSequence(QString)));
    connect(cross_but, SIGNAL(accept()),this, SLOT(updateSequence()));

    area_but = new AreaButton(0);
    area_but->state = true;
    area_but->setIcon(":/images/area_icon.png", true, true);
    connect(area_but, SIGNAL(click(QString)), this, SLOT(slotSetSequence(QString)));
    connect(area_but, SIGNAL(accept()),this, SLOT(updateSequence()));
    connect(QCoreApplication::instance(), SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(slotFocusChanged(QWidget*, QWidget*)));

    hbox = new QHBoxLayout((QWidget*)this->parent());
    hbox->addWidget(this);
    hbox->addWidget(area_but);
    hbox->addWidget(cross_but);
    hbox->addWidget(keyboard_but);
    hbox->addWidget(mouse_but);
    hbox->setStretch(0, 100);

    QWidget* w = (QWidget*)this->parent();
    w->setLayout(hbox);

}

void ComboEdit::slotCrossClick()
{
    clear();
    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
    QCoreApplication::sendEvent(this, &keyEvent);
    //cross_but->setDisabled(cross_but->state);
}

void ComboEdit::slotFocusChanged(QWidget * old, QWidget * now)
{
   //if(keyboard_but->keyScanMode)
   {
        //QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
        //QCoreApplication::sendEvent(this, &keyEvent);
        //editingFinished();
   }
}

void ComboEdit::slotAccepted()
{

    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
    QCoreApplication::sendEvent(this, &keyEvent);
}

void ComboEdit::wheelEvent(QWheelEvent *event)
{

    if( event->angleDelta().y() > 0 )
        sequence = "Scroll up";
    else
        sequence = "Scroll down";
    setText(sequence);
    setStyleSheet("");
    QLineEdit::wheelEvent(event);
}

void ComboEdit::mousePressEvent(QMouseEvent *ev)
{
    QLineEdit::mousePressEvent(ev);
}

void ComboEdit::keyPressEvent(QKeyEvent* event)
{
    event->accept();
    if( event->key() == Qt::Key_Backspace)  clear();
    if( event->key() == Qt::Key_Delete)  clear();

    if (keyboard_but->state)
    {
        Qt::KeyboardModifiers m = event->modifiers();
        if(keyboard_but->mouseOverFlag)
        {
            sequence = "";
            if( m.testFlag(Qt::ControlModifier) )
               sequence="ctrl+";
            if( m.testFlag(Qt::ControlModifier) && m.testFlag(Qt::ShiftModifier))
               sequence="ctrl+shift+";
            sequence+=QKeySequence(event->key()).toString();
            setText(sequence);
        }
    }
    setStyleSheet("");
    QLineEdit::keyPressEvent(event);
}


void ComboEdit::slotKeyboardClick()
{
    setText("press the hot key sequence  ");
    setStyleSheet("color: rgb(188, 188, 188);");
}

void ComboEdit::slotSetSequence(QString sequence)
{
    setText(sequence);
    setStyleSheet("");

    emit sigSetSequence(sequence);
}


void ComboEdit::resizeEvent(QResizeEvent* event)
{
    event->accept();
}

void ComboEdit::mouseMoveEvent(QMouseEvent *ev)
{
    ev->accept();
    keyboard_but->setDisable();
}


/*
void ComboEdit::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(0,0,rect().width(),100,Qt::red);
    QRect r = event->rect();
    r.setRect(0,0,10,10);
    QPaintEvent pevent(r);
    QLineEdit::paintEvent(&pevent);
    //label->repaint();

}
*/

AutocompleteEditor::AutocompleteEditor(QWidget *parent) :
    QComboBox(parent)
{
    setEditable(true);
    ComboEdit* edit = new ComboEdit(this);
    //edit->setEditable(true);
    setLineEdit(edit);
    connect(edit, SIGNAL(sigSetSequence(QString)), this, SLOT(updateSequence(QString)));
    setContextMenuPolicy(Qt::PreventContextMenu);

    setItemIcon(0, QIcon(":/images/keyboard_red.png"));
    completion_list = {"Right click",
                       "Left click",
                       "Esc",
                       "Hot key",
                       "Scroll up",
                       "Scroll down",
                       "Launch program",
                       "Image search",
                       "Type text",
                       "ctrl + A",
                       "ctrl + C",
                       "ctrl + V",
                      };

}

void AutocompleteEditor::updateSequence(QString sequence)
{
    setItemText(0, sequence);
}

void AutocompleteEditor::keyPressEvent(QKeyEvent* event)
{
    QVector<QString> filtered_list;

    if( event->key() == Qt::Key_Backspace)  clear();
    if( event->key() == Qt::Key_Delete)  clear();

    QString text = this->currentText();
    for (QString item : completion_list) {
        if(item.contains(text) && text.size() > 2)
            filtered_list.push_back(item);
    }
    if( filtered_list.size() > 0 )
    {
        //this->clear();
        insertItems(0, filtered_list);
        setItemIcon(0, QIcon(":/images/keyboard_red.png"));
        showPopup();
    }
    event->accept();
    QComboBox::keyPressEvent(event);
}

AutocompleteEditor::~AutocompleteEditor()
{
}

void AutocompleteEditor::setValue(QString value)
{
    ComboEdit* edit  = (ComboEdit*)lineEdit();
    setItemText(0, value);
    edit->setText(value);

    // set buttons state
    if( value.contains("Scroll") )
        edit ->mouse_but->setIcon(":/images/mouse_scroll.png");
    if( value.contains("Left") )
        edit ->mouse_but->setIcon(":/images/mouse_left_click.png");
    if( value.contains("Right") )
        edit ->mouse_but->setIcon(":/images/mouse_right_click.png");

}

/*
void AutocompleteEditor::paintEvent(QPaintEvent* event)
{
    QRect r = event->rect();
    r.setRect(0,0,10,10);
    QPaintEvent pevent(r);

    QComboBox::paintEvent(&pevent);
}
*/
