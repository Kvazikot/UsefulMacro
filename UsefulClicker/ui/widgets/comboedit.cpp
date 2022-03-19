#include <QCoreApplication>

#include "ui/widgets/areabutton.h"
#include "ui/widgets/crossbutton.h"
#include "ui/widgets/keyboardbutton.h"
#include "ui/widgets/mousebutton.h"
#include "ui/widgets/comboedit.h"

static KeyboardButton* keyboard_but;
static CrossButton* cross_but;
static MouseButton* mouse_but;
static AreaButton* area_but;

//---------------------------------------------------------------------------------------------------------

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
    cross_but->setIcon(":/images/knights-templar-cross.png", true, true);
    connect(cross_but, SIGNAL(click(QString)), this, SLOT(slotSetSequence(QString)));
    connect(cross_but, SIGNAL(accept()),this, SLOT(updateSequence()));

    area_but = new AreaButton(this);
    area_but->state = true;
    area_but->setIcon(":/images/area_icon.png", true, true);
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

void ComboEdit::setMouseState(int button)
{
    switch(button)
    {
        case 0: mouse_but->setIcon(":/images/mouse_left_click.png");
        break;
        case 1: mouse_but->setIcon(":/images/mouse_right_click.png");
        break;
        case 2: mouse_but->setIcon(":/images/mouse_scroll.png");
        break;
    }

}
