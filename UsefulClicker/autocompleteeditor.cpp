#include <QImage>
#include <QPainter>
#include <QLabel>
#include <QHBoxLayout>
#include "autocompleteeditor.h"


KeyboardButton::KeyboardButton(QWidget *parent)
    : QLabel(parent)
{
    keyboard_red = QImage(":/keyboard_icon.png");
    keyboard_red = keyboard_red.scaled(50,height());
    keyboard_black = keyboard_red;
    keyboard_black.invertPixels();
    mouseOverFlag = false;
    setScaledContents(true);
    setPixmap(QPixmap::fromImage(keyboard_black));
    setGeometry(width()-10,0,50,20);
    startTimer(101);
}

void KeyboardButton::mousePressEvent(QMouseEvent *ev)
{
    mouseOverFlag = true;
    ev->accept();
    emit clicked();
}

void KeyboardButton::timerEvent(QTimerEvent* event)
{
    event->accept();
    qDebug() << "KeyboardButton pos ";
    if( mouseOverFlag )
        setPixmap(QPixmap::fromImage(keyboard_red));

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
    setPixmap(QPixmap::fromImage(keyboard_black));
    mouseOverFlag = false;
    qDebug() << "KeyboardButton::setDisable() ";
}



ComboEdit::ComboEdit(QWidget *parent) :
    QLineEdit(parent)
{
    keyboard_but = new KeyboardButton(0);
    connect(keyboard_but, SIGNAL(clicked()),this, SLOT(slotKeyboardClick()));
    connect(keyboard_but, SIGNAL(updateSequence()),this, SLOT(slotSetSequence()));
    //label->show();
    QHBoxLayout hbox((QWidget*)this->parent());
    hbox.addWidget(this);
    hbox.addWidget(keyboard_but);
    hbox.setStretch(0, 100);
}

void ComboEdit::keyPressEvent(QKeyEvent* event)
{
    event->accept();
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
    setStyleSheet("");
    QLineEdit::keyPressEvent(event);
}


void ComboEdit::slotKeyboardClick()
{
    qDebug("slot clicked slotKeyboardClick");
    setText("press hot key  ");
    setStyleSheet("color: rgb(188, 188, 188);");
}

void ComboEdit::slotSetSequence()
{
    qDebug("slot clicked slotSetSequence");

}


void ComboEdit::resizeEvent(QResizeEvent* event)
{
    keyboard_but->setGeometry(width()-keyboard_but->width()-10,1,50,15);
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
