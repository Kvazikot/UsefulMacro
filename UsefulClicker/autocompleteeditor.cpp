#include <QImage>
#include <QPainter>
#include <QWheelEvent>
#include <QCoreApplication>
#include <QLabel>
#include <QHBoxLayout>
#include "autocompleteeditor.h"


MouseButton::MouseButton(QWidget *parent)
    : KeyboardButton(parent)
{
    /*
    icon_enabled = QImage(":/mouse_default.png");
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
        icon_enabled = QImage(":/mouse_left_click.png");
        sequence = "Left button";
    }
    if( ev->button() == Qt::MouseButton::RightButton )
    {
        icon_enabled = QImage(":/mouse_right_click.png");
        sequence = "Right button";
    }
    icon_enabled = icon_enabled.scaled(50,height());
    setPixmap(QPixmap::fromImage(icon_enabled));
    //emit click(sequence);
    setFocus();
}

void MouseButton::wheelEvent(QWheelEvent *event)
{
    event->accept();
    icon_enabled = QImage(":/mouse_scroll.png");
    setPixmap(QPixmap::fromImage(icon_enabled));
}

KeyboardButton::KeyboardButton(QWidget *parent)
    : QLabel(parent)
{
    mouseOverFlag = false;
    keyScanMode = false;
    setScaledContents(true);
    setGeometry(width()-10,0,50,20);
    startTimer(101);
}

void KeyboardButton::setIcon(QString filename)
{
    icon_enabled = QImage(filename);
    icon_enabled = icon_enabled.scaled(50,height());
    icon_disabled = icon_enabled;
    icon_disabled.invertPixels();
    setPixmap(QPixmap::fromImage(icon_disabled));
}

void KeyboardButton::mousePressEvent(QMouseEvent *ev)
{
    keyScanMode = !keyScanMode;
    mouseOverFlag = true;
    if( keyScanMode )
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
    qDebug() << "KeyboardButton pos ";
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
    qDebug() << "KeyboardButton::setDisable() ";
}



ComboEdit::ComboEdit(QWidget *parent) :
    QLineEdit(parent)
{
    keyboard_but = new KeyboardButton(0);
    keyboard_but->setIcon(":/keyboard_icon.png");
    setContextMenuPolicy(Qt::PreventContextMenu);
    connect(keyboard_but, SIGNAL(clicked()),this, SLOT(slotKeyboardClick()));
    connect(keyboard_but, SIGNAL(accept()),this, SLOT(slotAccepted()));

    mouse_but = new MouseButton(0);
    mouse_but->setIcon(":/mouse_default.png");
    connect(mouse_but, SIGNAL(click(QString)), this, SLOT(slotSetSequence(QString)));
    keyboard_but->setGeometry(width()-keyboard_but->width()-10,1,50,15);
    mouse_but->setGeometry(width()-keyboard_but->width()-mouse_but->width()-15,1,50,15);

    connect(QCoreApplication::instance(), SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(slotFocusChanged(QWidget*, QWidget*)));


    //label->show();
    QHBoxLayout hbox((QWidget*)this->parent());
    hbox.addWidget(this);
    hbox.addWidget(keyboard_but);
    hbox.addWidget(mouse_but);
    hbox.setStretch(0, 100);
}

void ComboEdit::slotFocusChanged(QWidget * old, QWidget * now)
{
   //if(keyboard_but->keyScanMode)
   {
        //QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
        //QCoreApplication::sendEvent(this, &keyEvent);
        editingFinished();
   }
}

void ComboEdit::slotAccepted()
{

    //QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
    //QCoreApplication::sendEvent(this, &keyEvent);
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
    if (keyboard_but->keyScanMode)
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
    qDebug("slot clicked slotKeyboardClick");
    setText("press hot key  ");
    setStyleSheet("color: rgb(188, 188, 188);");
}

void ComboEdit::slotSetSequence(QString sequence)
{
    qDebug("slot clicked slotSetSequence");
    setText(sequence);
    setStyleSheet("");
    emit sigSetSequence(sequence);
}


void ComboEdit::resizeEvent(QResizeEvent* event)
{
    keyboard_but->setGeometry(width()-keyboard_but->width()-10,1,50,15);
    mouse_but->setGeometry(width()-keyboard_but->width()-mouse_but->width()-15,1,50,15);
    event->accept();
}

void ComboEdit::mouseMoveEvent(QMouseEvent *ev)
{
    ev->accept();
    qDebug() << "pos " << ev->pos();
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

    setItemIcon(0, QIcon(":/keyboard_red.png"));
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

   // if( event->key() == Qt::Key_Backspace)  clear();
   // if( event->key() == Qt::Key_Delete)  clear();

    QString text = this->currentText();
    for (QString item : completion_list) {
        if(item.contains(text) && text.size() > 2)
            filtered_list.push_back(item);
    }
    if( filtered_list.size() > 0 )
    {
        //this->clear();
        insertItems(0, filtered_list);
        setItemIcon(0, QIcon(":/keyboard_red.png"));
        showPopup();
    }
    event->accept();
    QComboBox::keyPressEvent(event);
}

AutocompleteEditor::~AutocompleteEditor()
{
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
