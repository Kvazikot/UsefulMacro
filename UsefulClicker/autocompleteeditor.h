#ifndef AUTOCOMPLETEEDITOR_H
#define AUTOCOMPLETEEDITOR_H

#include <QLabel>
#include <QVector>
#include <QWidget>
#include <QResizeEvent>
#include <QComboBox>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QLineEdit>

class ComboEdit : public QLineEdit
{
    Q_OBJECT
public:
    QLabel* label;
    explicit ComboEdit(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent* event);
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
