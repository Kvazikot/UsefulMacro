#ifndef XMLEDITOR_H
#define XMLEDITOR_H

#include <QWidget>
#include <QTextEdit>

class XmlEditor : public QTextEdit
{
    Q_OBJECT
public:
    explicit XmlEditor(QWidget *parent = nullptr);

signals:

};

#endif // XMLEDITOR_H
