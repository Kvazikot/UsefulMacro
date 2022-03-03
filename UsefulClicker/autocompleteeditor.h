#ifndef AUTOCOMPLETEEDITOR_H
#define AUTOCOMPLETEEDITOR_H

#include <QLabel>
#include <QVector>
#include <QWidget>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QComboBox>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QLineEdit>
#include <QTimerEvent>
#include <QKeyEvent>

class KeyboardButton : public QLabel
{
    Q_OBJECT
public:
    QImage keyboard_red, keyboard_black;
    explicit KeyboardButton(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void timerEvent(QTimerEvent* event) override;
    void setDisable();
    bool mouseOverFlag;
    virtual void paintEvent(QPaintEvent *) override;
signals:
    void clicked();
    void updateSequence();

};

class ComboEdit : public QLineEdit
{
    Q_OBJECT
public:
    QString sequence;
    KeyboardButton* keyboard_but;
    explicit ComboEdit(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent* event);
    void mouseMoveEvent(QMouseEvent *ev) override;
    void keyPressEvent(QKeyEvent* event) override;

public slots:
    void slotKeyboardClick();
    void slotSetSequence();
//    void paintEvent(QPaintEvent *) override;

};

class AutocompleteEditor : public QComboBox
{
    Q_OBJECT
public:
    QVector<QString> completion_list;
    explicit AutocompleteEditor(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent* event);
    //void paintEvent(QPaintEvent* event);
    ~AutocompleteEditor();
};

#endif // AUTOCOMPLETEEDITOR_H
