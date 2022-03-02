#include <QImage>
#include <QPainter>
#include <QLabel>
#include <QHBoxLayout>

#include "autocompleteeditor.h"

ComboEdit::ComboEdit(QWidget *parent) :
    QLineEdit(parent)
{
    label = new QLabel(0);
    QImage keyboard_icon(":/keyboard_icon.png");
    keyboard_icon = keyboard_icon.scaled(50,height());
    label->setScaledContents(true);
    label->setPixmap(QPixmap::fromImage(keyboard_icon));
    label->setGeometry(width()-10,0,50,20);
    //label->show();
    QHBoxLayout hbox((QWidget*)this->parent());
    hbox.addWidget(this);
    hbox.addWidget(label);
}

void ComboEdit::resizeEvent(QResizeEvent* event)
{
    label->setGeometry(width()-label->width()-10,1,50,15);
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


    setItemIcon(0, QIcon(":/keyboard_icon.png"));
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

    if( event->key() == Qt::Key_Backspace)  clear();
    if( event->key() == Qt::Key_Delete)  clear();

    QString text = this->currentText();
    for (QString item : completion_list) {
        if(item.contains(text) && text.size() > 2)
            filtered_list.push_back(item);
    }
    if( filtered_list.size() > 0 )
    {
        this->clear();
        insertItems(0, filtered_list);
        setItemIcon(0, QIcon(":/keyboard_icon.png"));
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
