#ifndef AUTOCOMPLETEEDITOR_H
#define AUTOCOMPLETEEDITOR_H

#include <QVector>
#include <QWidget>
#include <QComboBox>
#include <QKeyEvent>

class AutocompleteEditor : public QComboBox
{
    Q_OBJECT
public:
    QVector<QString> completion_list;
    explicit AutocompleteEditor(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent* event);
    ~AutocompleteEditor();
};

#endif // AUTOCOMPLETEEDITOR_H
